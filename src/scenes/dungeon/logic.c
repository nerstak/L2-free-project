#include "logic.h"
#include "../../engine/game/combat.h"
#include "../../engine/save.h"
#include "../../utils/math.h"


static bool moveToNewRoom(Engine* engine, Data* data, Coord newCoord);
static void playStep(Engine* engine, Player* player);
static void playDamage(Engine* engine, Player* player);
static void enterDoor(Engine* engine, Data* data, SDL_Rect* door, SDL_Rect* player, dungeonScene_t* room, int direction);
static void processDeath(Engine* engine, Data* data);
static void processSoundEntities(Engine* engine, Data* data);
static void playDamage_Entities(Engine* engine, Data* data);
static void playAttack_Entities(Engine* engine, Data* data);
static void playDisplacement_Entities(Engine* engine, Data* data);


static bool moveToNewRoom(Engine* engine, Data* data, Coord newCoord) {
    TreeMapNode* node = NULL;
    node = get_TreeMap(data->dungeonScene->dungeon->rooms, &newCoord);

    if (node != NULL) {
        Room* newRoom = node->value;
        bool found = false;

        for (int i = 0; i < (int) data->dungeonScene->currentRoom->childrenLength; i += 1) {
            if (data->dungeonScene->currentRoom->children[i] == newRoom) {
                found = true;
            }
        }

        if (getParent_Room(data->dungeonScene->currentRoom) == newRoom) {
            found = true;
        }

        if (found == true) {
            // Do i need a key ?
            if (getPrecondition_Room(newRoom)->keyLevel - 1 > data->dungeonScene->keyValue) {
                return false;
            }

            // We move to the room
            newRoom->visited = true;
            data->dungeonScene->currentRoom = newRoom;


            if(isBoss_Room(newRoom) && newRoom->cleaned == false) {
                stopMusic();
                playMusic(engine->soundCollector, "dungeon/boss_theme");
            }

            // We place the entities
            if (newRoom->cleaned == false) {
                for (int i = 0; i < newRoom->layout->lines; i += 1) {
                    for (int j = 0; j < newRoom->layout->columns; j += 1) {
                        if (newRoom->layout->map[i][j].type == '0' || newRoom->layout->map[i][j].type == '1' || newRoom->layout->map[i][j].type == '2' || newRoom->layout->map[i][j].type == '3') {
                            switch(newRoom->layout->map[i][j].type) {
                                case '0': {
                                    EntityList* e = init_EntityNode(MOTH);
                                    e->data->movement->position->x = (64 * j) - (e->data->movement->spriteBox->w / 4);
                                    e->data->movement->position->y = (6 + 64 * i) - (e->data->movement->spriteBox->h / 2);

                                    append_EntityNode(e, &(data->entities));

                                    break;
                                }

                                case '1': {
                                    EntityList* e = init_EntityNode(WORM);
                                    e->data->movement->position->x = (64 * j) - (e->data->movement->spriteBox->w / 4);
                                    e->data->movement->position->y = (6 + 64 * i) - (e->data->movement->spriteBox->h / 2);
                                    append_EntityNode(e, &(data->entities));
                                    break;
                                }

                                case '2': {
                                    EntityList* e = init_EntityNode(TREE);
                                    e->data->movement->position->x = (64 * j) - (e->data->movement->spriteBox->w / 4);
                                    e->data->movement->position->y = (6 + 64 * i) - (e->data->movement->spriteBox->h / 2);


                                    append_EntityNode(e, &(data->entities));
                                    break;
                                }

                                /*case '3': {
                                    break;
                                }*/

                                default: {
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            return true;
        }
    }
    return false;
}

static void enterDoor(Engine* engine, Data* data, SDL_Rect* door, SDL_Rect* player, dungeonScene_t* room, int direction) {
    if(BoxCollision(player,door) && data->dungeonScene->currentRoom->cleaned == true) {
        room->moveTo=direction;
    }
}

extern void logicProcess_Scene_dungeon(Engine* engine, Data* data) {
    if (data->dungeonScene->actionProcess == NONE && isPlayerAlive(data->Isaac)) {
        if (data->dungeonScene->moveTo != -1) {
            switch (data->dungeonScene->moveTo) {
                case 0: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x, data->dungeonScene->currentRoom->coord->y - 1};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=608;
                        data->Isaac->movement->position->y=505;
                    }

                    break;
                }

                case 1: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x + 1, data->dungeonScene->currentRoom->coord->y};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=64;
                        data->Isaac->movement->position->y=262;
                    }

                    break;
                }

                case 2: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x, data->dungeonScene->currentRoom->coord->y + 1};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=608;
                        data->Isaac->movement->position->y=6;
                    }
                    break;
                }

                case 3: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x - 1, data->dungeonScene->currentRoom->coord->y};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=1152;
                        data->Isaac->movement->position->y=262;
                    }
                    break;
                }
            }

            data->dungeonScene->moveTo = -1;
        }
        if (data->dungeonScene->askCombat != -1) {
            ProcessCombat(engine, data,&(data->dungeonScene->askCombat));
        } else {
            data->Isaac->combat->weaponHitBox->x=10000; // clean fix
            data->Isaac->combat->weaponHitBox->y=10000;
            data->Isaac->combat->weaponHitBox->h=0;
            data->Isaac->combat->weaponHitBox->w=0;
        }

        process_Entity(&(data->entities), data);
        movePlayer_Movement(data, data->dungeonScene->currentRoom->layout->map);
        playStep(engine, data->Isaac);
        playDamage(engine, data->Isaac);
        processSoundEntities(engine, data);


        // Room clean ?
        if (data->entities == NULL && data->dungeonScene->currentRoom->cleaned == false) {
            // Loot
            if (isStart_Room(data->dungeonScene->currentRoom) == false && isBoss_Room(data->dungeonScene->currentRoom) == false && isGoal_Room(data->dungeonScene->currentRoom) == false) {
                if (probability(0.05)) {
                    // Health Potion
                    add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(10, 1, data->referenceItems), &(data->Isaac->sizeInventory));

                    Notification* notification = init_Notification();
                    notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/items")->surface;
                    strcpy(notification->text, data->referenceItems->table[10].name);
                    notification->sprite.w = 64;
                    notification->sprite.h = 64;
                    notification->sprite.x = (10 % 5) * 64;
                    notification->sprite.y = (10 / 5) * 64;

                    start_Timer(notification->timer);
                    enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                }

                if (probability(0.20)) { // Common
                    add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(18, 1, data->referenceItems), &(data->Isaac->sizeInventory));

                    Notification* notification = init_Notification();
                    notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/items")->surface;
                    strcpy(notification->text, data->referenceItems->table[18].name);
                    notification->sprite.w = 64;
                    notification->sprite.h = 64;
                    notification->sprite.x = (18 % 5) * 64;
                    notification->sprite.y = (18 / 5) * 64;

                    start_Timer(notification->timer);
                    enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                }

                if (probability(0.05)) { // Rare
                    add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(19, 1, data->referenceItems), &(data->Isaac->sizeInventory));

                    Notification* notification = init_Notification();
                    notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/items")->surface;
                    strcpy(notification->text, data->referenceItems->table[19].name);
                    notification->sprite.w = 64;
                    notification->sprite.h = 64;
                    notification->sprite.x = (19 % 5) * 64;
                    notification->sprite.y = (19 / 5) * 64;

                    start_Timer(notification->timer);
                    enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                }

                if (probability(0.02)) { // Ultra rare
                    add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(20, 1, data->referenceItems), &(data->Isaac->sizeInventory));

                    Notification* notification = init_Notification();
                    notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/items")->surface;
                    strcpy(notification->text, data->referenceItems->table[20].name);
                    notification->sprite.w = 64;
                    notification->sprite.h = 64;
                    notification->sprite.x = (20 % 5) * 64;
                    notification->sprite.y = (20 / 5) * 64;

                    start_Timer(notification->timer);
                    enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                }
            }

            // Key to get ?
            if (getItem_Room(data->dungeonScene->currentRoom) != NULL && getItem_Room(data->dungeonScene->currentRoom)->value > -1 && getItem_Room(data->dungeonScene->currentRoom)->value > data->dungeonScene->keyValue) {
                data->dungeonScene->keyValue = getItem_Room(data->dungeonScene->currentRoom)->value;

                // Notification
                Notification* notification = init_Notification();
                notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/uiKeys")->surface;
                notification->sprite.w = 46;
                notification->sprite.h = 23;
                notification->sprite.y = 0;

                switch (data->dungeonScene->keyValue) {
                    case 1: {
                        notification->sprite.x = 0;

                        strcpy(notification->text, "Green key");
                        break;
                    }

                    case 2: {
                        notification->sprite.x = 46;

                        strcpy(notification->text, "Orange key");
                        break;
                    }

                    case 3: {
                        notification->sprite.x = 92;

                        strcpy(notification->text, "Red key");
                        break;
                    }

                    default: {
                        clean_Notification(&(notification));

                        break;
                    }
                }

                if (notification != NULL) {
                    start_Timer(notification->timer);
                    enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                }
            }
            data->dungeonScene->currentRoom->cleaned = true;
            if (isBoss_Room(data->dungeonScene->currentRoom) && data->dungeonScene->sound->bossJustDefeated == 1) {
                data->dungeonScene->sound->bossJustDefeated = 0;
                stopMusic();
                playEffect(engine->soundCollector, "dungeon/victory", 0);
                playMusic(engine->soundCollector, "dungeon/main_theme");
            }
        }

        // Clear notification
        NotificationQueueNode* tempNode = deQueue_Notification(data->dungeonScene->notificationQueue);
        while (tempNode != NULL) {
            NotificationQueueNode* next = tempNode->next;

            if (getTime_Timer(tempNode->data->timer) > 2.5) {
                popQueue_Notification(data->dungeonScene->notificationQueue);
            } else {
                break;
            }

            tempNode = next;
        }

        SDL_Rect door;

        door.h=12;
        door.w=20;
        door.x=630;
        door.y=0;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 0); //UP

        door.y=608;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 2); //DOWN

        door.x=45;
        door.y=342;
        door.h=20;
        door.w=10;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 3); //LEFT

        door.x=1224;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 1); //RIGHT
    } else if (isPlayerAlive(data->Isaac)) {
        //TODO: We have to pause every timer of the dungeon
        if (data->dungeonScene->actionProcess == PAUSE) {
            data->dungeonScene->actionProcess = NONE;
            display_SceneCollector(engine, data, "pauseMenu");
        } else if (data->dungeonScene->actionProcess == INVENTORY) {
            data->dungeonScene->actionProcess = NONE;
            display_SceneCollector(engine, data, "inventory");
        }
    } else {
        processDeath(engine, data);
    }

}

static void playStep(Engine* engine, Player* player) {
    printf("StepChannel before: %d ", player->movement->stepChannel);
    if((player->movement->velocity->x > 10 || player->movement->velocity->x < -10 || player->movement->velocity->y > 10 || player->movement->velocity->y < -10) && player->movement->stepChannel == -1 && player->combat->animationStep == 0) {
        player->movement->stepChannel = playEffect(engine->soundCollector, "player/step_dungeon_run", -1);
    }
    if((!player->movement->velocity->x && !player->movement->velocity->y) || player->combat->animationStep != 0) {
        if(player->movement->stepChannel >= 0) {
            stopEffect(player->movement->stepChannel);
        }
        player->movement->stepChannel = -1;
    }
    printf("Vx: %f Vy: %f StepChannel: %d\n",player->movement->velocity->x,player->movement->velocity->y,player->movement->stepChannel);
}

static void playDamage(Engine* engine, Player* player) {
    if(player->combat->damageJustTaken == 1) {
        playEffect(engine->soundCollector, "player/pain", 0);
        player->combat->damageJustTaken = 0;
    }
}

static void processDeath(Engine* engine, Data* data) {
    if(isStarted_Timer(data->Isaac->invulnerabilityTimer)) {
        playMusic(engine->soundCollector, "dungeon/death_theme");
        playEffect(engine->soundCollector, "player/death_player", 0);
        stop_Timer(data->Isaac->invulnerabilityTimer);
    }
    data->dungeonScene->askCombat = -1;
    if(data->dungeonScene->actionProcess == PAUSE) {
        playEffect(engine->soundCollector, "loading/leave_menu", 0);
        //We free Player and field
        if(data->Isaac) {
            free_Player(&(data->Isaac));
        }
        if(data->field) {
            freeField(&(data->field));
        }

        //We reload the save
        if(initGame("save1.save", data)) {
            display_SceneCollector(engine,data,"lobby");
        } else {
            display_SceneCollector(engine,data, "mainMenu");
        }
    }
}

static void processSoundEntities(Engine* engine, Data* data) {
    if(data->dungeonScene->sound->deathMob) {
        playEffect(engine->soundCollector, "dungeon/death_mobs",0);
        data->dungeonScene->sound->deathMob = 0;
    }
    playDamage_Entities(engine, data);
    playAttack_Entities(engine, data);
    playDisplacement_Entities(engine, data);
}

static void playDamage_Entities(Engine* engine, Data* data) {
    if(data->dungeonScene->sound->mobsDamaged->moth != 0) {
        playEffect(engine->soundCollector, "dungeon/pain_moth", 0);
    }
    if(data->dungeonScene->sound->mobsDamaged->worm != 0) {
        playEffect(engine->soundCollector, "dungeon/pain_worm", 0);
    }
    resetEntitiesBool(data->dungeonScene->sound->mobsDamaged);
}

static void playAttack_Entities(Engine* engine, Data* data) {
    if(data->dungeonScene->sound->mobsAttack->worm != 0) {
        playEffect(engine->soundCollector, "dungeon/attack_worm", 0);
    }
    resetEntitiesBool(data->dungeonScene->sound->mobsAttack);
}

static void playDisplacement_Entities(Engine* engine, Data* data) {
    if(data->dungeonScene->sound->mobsDisplacement->moth != 0) {
        playEffect(engine->soundCollector, "dungeon/move_moth", 0);
    }
    resetEntitiesBool(data->dungeonScene->sound->mobsDisplacement);
}