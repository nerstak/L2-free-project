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


static void notificationInventoryFull(Data* data);
static void movePlayer_BossRoom(Data* data);

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
            // We clean previous kill list
            cleanList_Entity(&(data->dyingEntities));

            // We place the entities
            if (newRoom->cleaned == false) {
                if(isBoss_Room(newRoom)) {
                    append_EntityNode(init_EntityNode(BOSSBOD, data->dungeonScene->difficulty), &(data->entities));
                } else {
                    for (int i = 0; i < newRoom->layout->lines; i += 1) {
                        for (int j = 0; j < newRoom->layout->columns; j += 1) {
                            if (newRoom->layout->map[i][j].type == '0' || newRoom->layout->map[i][j].type == '1' ||
                                newRoom->layout->map[i][j].type == '2' || newRoom->layout->map[i][j].type == '3') {

                                bool spawn = false;

                                switch(data->field->currentPlant->idVegetable) {
                                    case 0: {
                                        if (probability(0.5)) {
                                            spawn = true;
                                        }

                                        break;
                                    }

                                    case 1: {
                                        if (probability(0.6)) {
                                            spawn = true;
                                        }

                                        break;
                                    }

                                    case 2: {
                                        if (probability(0.7)) {
                                            spawn = true;
                                        }

                                        break;
                                    }

                                    case 3: {
                                        if (probability(0.8)) {
                                            spawn = true;
                                        }

                                        break;
                                    }

                                    case 4: {
                                        if (probability(1)) {
                                            spawn = true;
                                        }

                                        break;
                                    }
                                }

                                if (spawn) {
                                    switch (newRoom->layout->map[i][j].type) {
                                        case '0': {
                                            EntityList* e = init_EntityNode(MOTH, data->dungeonScene->difficulty);
                                            e->data->movement->position->x =
                                                    (64 * j) - (e->data->movement->spriteBox->w / 4);
                                            e->data->movement->position->y =
                                                    (6 + 64 * i) - (e->data->movement->spriteBox->h / 2);

                                            append_EntityNode(e, &(data->entities));

                                            break;
                                        }

                                        case '1': {
                                            EntityList* e = init_EntityNode(WORM, data->dungeonScene->difficulty);
                                            e->data->movement->position->x =
                                                    (64 * j) - (e->data->movement->spriteBox->w / 4);
                                            e->data->movement->position->y =
                                                    (6 + 64 * i) - (e->data->movement->spriteBox->h / 2);


                                            append_EntityNode(e, &(data->entities));

                                            break;
                                        }

                                        case '2': {
                                            EntityList* e = init_EntityNode(TREE, data->dungeonScene->difficulty);
                                            e->data->movement->position->x =
                                                    (64 * j) - (e->data->movement->spriteBox->w / 4);
                                            e->data->movement->position->y =
                                                    (6 + 64 * i) - (e->data->movement->spriteBox->h / 2);


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
                        movePlayer_BossRoom(data);
                    }

                    break;
                }

                case 1: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x + 1, data->dungeonScene->currentRoom->coord->y};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=64;
                        data->Isaac->movement->position->y=262;
                        movePlayer_BossRoom(data);
                    }

                    break;
                }

                case 2: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x, data->dungeonScene->currentRoom->coord->y + 1};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=608;
                        data->Isaac->movement->position->y=6;
                        movePlayer_BossRoom(data);
                    }
                    break;
                }

                case 3: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x - 1, data->dungeonScene->currentRoom->coord->y};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=1152;
                        data->Isaac->movement->position->y=262;
                        movePlayer_BossRoom(data);
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
                    if(add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(10, 1, data->referenceItems), &(data->Isaac->sizeInventory))) {
                        Notification* notification = init_Notification();
                        notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/items")->surface;
                        strcpy(notification->text, data->referenceItems->table[10].name);
                        notification->sprite.w = 64;
                        notification->sprite.h = 64;
                        notification->sprite.x = (10 % 5) * 64;
                        notification->sprite.y = (10 / 5) * 64;

                        start_Timer(notification->timer);
                        enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                    } else {
                        notificationInventoryFull(data);
                    }
                }

                if (probability(0.20)) { // Common
                    if(add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(min(22, 18 + data->field->currentPlant->idVegetable), 1, data->referenceItems), &(data->Isaac->sizeInventory))) {
                        Notification* notification = init_Notification();
                        notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/items")->surface;
                        strcpy(notification->text, data->referenceItems->table[min(22, 18 + data->field->currentPlant->idVegetable)].name);
                        notification->sprite.w = 64;
                        notification->sprite.h = 64;
                        notification->sprite.x = (min(22, 18 + data->field->currentPlant->idVegetable) % 5) * 64;
                        notification->sprite.y = (min(22, 18 + data->field->currentPlant->idVegetable) / 5) * 64;

                        start_Timer(notification->timer);
                        enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                    } else {
                        notificationInventoryFull(data);
                    }
                }

                if (probability(0.05)) { // Rare
                    if(add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(min(22, 19 + data->field->currentPlant->idVegetable), 1, data->referenceItems), &(data->Isaac->sizeInventory))) {
                        Notification* notification = init_Notification();
                        notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/items")->surface;
                        strcpy(notification->text, data->referenceItems->table[min(22, 19 + data->field->currentPlant->idVegetable)].name);
                        notification->sprite.w = 64;
                        notification->sprite.h = 64;
                        notification->sprite.x = (min(22, 19 + data->field->currentPlant->idVegetable) % 5) * 64;
                        notification->sprite.y = (min(22, 19 + data->field->currentPlant->idVegetable) / 5) * 64;

                        start_Timer(notification->timer);
                        enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                    } else {
                        notificationInventoryFull(data);
                    }
                }

                if (probability(0.02)) { // Ultra rare
                    if(add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(min(22, 20 + data->field->currentPlant->idVegetable), 1, data->referenceItems), &(data->Isaac->sizeInventory))) {
                        Notification* notification = init_Notification();
                        notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/items")->surface;
                        strcpy(notification->text, data->referenceItems->table[min(22, 20 + data->field->currentPlant->idVegetable)].name);
                        notification->sprite.w = 64;
                        notification->sprite.h = 64;
                        notification->sprite.x = (min(22, 20 + data->field->currentPlant->idVegetable) % 5) * 64;
                        notification->sprite.y = (min(22, 20 + data->field->currentPlant->idVegetable) / 5) * 64;

                        start_Timer(notification->timer);
                        enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                    } else {
                        notificationInventoryFull(data);
                    }
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
        door.y=332;
        door.h=40;
        door.w=10;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 3); //LEFT

        door.x=1224;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 1); //RIGHT

        if (isGoal_Room(data->dungeonScene->currentRoom)) {
            SDL_Rect socle;
            socle.x = (1280 / 2) - (64 / 2);
            socle.y = (720 / 2) - (64 / 2) - 15;
            socle.w = 63;
            socle.h = 63;

            if (BoxCollision(data->Isaac->movement->hitBox, &socle)) {
                if(add_SlotInventory(&(data->Isaac->inventory), create_SlotInventory(5 + data->field->currentPlant->idVegetable, 1, data->referenceItems), &(data->Isaac->sizeInventory))) {
                    Notification* notification = init_Notification();
                    notification->icon = get_ImageCollector(engine->imageCollector, "dungeon/items")->surface;
                    strcpy(notification->text, data->referenceItems->table[5 + data->field->currentPlant->idVegetable].name);
                    notification->sprite.w = 64;
                    notification->sprite.h = 64;
                    notification->sprite.x = ((5 + data->field->currentPlant->idVegetable) % 5) * 64;
                    notification->sprite.y = ((5 + data->field->currentPlant->idVegetable) / 5) * 64;

                    start_Timer(notification->timer);
                    enQueue_Notification(data->dungeonScene->notificationQueue, notification);
                } else {
                    notificationInventoryFull(data);
                }

                int plantId = -1;
                assignNumberPlant_Coord(data->field->currentPlant->x, data->field->currentPlant->y, data, &plantId);
                removePlant(plantId, data->field);

                stopVelocity_Movement(data->Isaac->movement);
                playEffect(engine->soundCollector, "loading/entering_dungeon", 0);

                data->Isaac->gameStats->dungeons++;

                display_SceneCollector(engine, data, "lobby");
            }
        }
    } else if (isPlayerAlive(data->Isaac)) {
        pauseTimer_entities(data->entities);
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
    if((player->movement->velocity->x > 10 || player->movement->velocity->x < -10 || player->movement->velocity->y > 10 || player->movement->velocity->y < -10)) {
        if (isStarted_Timer(player->movement->lastStep)) {
            if (getTime_Timer(player->movement->lastStep) > 0.6) {
                start_Timer(player->movement->lastStep);
                playEffect(engine->soundCollector, "player/step_dungeon_run", 0);
            }
        } else if (isPaused_Timer(player->movement->lastStep)) {
            start_Timer(player->movement->lastStep);
            playEffect(engine->soundCollector, "player/step_dungeon_run", 0);
        } else {
            start_Timer(player->movement->lastStep);
            playEffect(engine->soundCollector, "player/step_dungeon_run", 0);
        }
    }

    if((!player->movement->velocity->x && !player->movement->velocity->y)) {
        stop_Timer(player->movement->lastStep);
    }
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
            data->Isaac->gameStats->death++;
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
    if(data->dungeonScene->sound->mobsDamaged->tree != 0) {
        playEffect(engine->soundCollector, "dungeon/pain_tree", 0);
    }
    if(data->dungeonScene->sound->mobsDamaged->arm != 0) {
        playEffect(engine->soundCollector, "dungeon/pain_arm", 0);
    }
    if(data->dungeonScene->sound->mobsDamaged->bossBod != 0) {
        playEffect(engine->soundCollector, "dungeon/pain_bossBod", 0);
    }
    resetEntitiesBool(data->dungeonScene->sound->mobsDamaged);
}

static void playAttack_Entities(Engine* engine, Data* data) {
    if(data->dungeonScene->sound->mobsAttack->worm != 0) {
        playEffect(engine->soundCollector, "dungeon/attack_worm", 0);
    }if(data->dungeonScene->sound->mobsAttack->tree != 0) {
        playEffect(engine->soundCollector, "dungeon/attack_tree", 0);
    }
    if(data->dungeonScene->sound->mobsAttack->arm != 0) {
        printf("oh\n");
        playEffect(engine->soundCollector, "dungeon/attack_arm", 0);
    }if(data->dungeonScene->sound->mobsAttack->bossBod != 0) {
        playEffect(engine->soundCollector, "dungeon/attack_bossBod", 0);
    }
    resetEntitiesBool(data->dungeonScene->sound->mobsAttack);
}

static void playDisplacement_Entities(Engine* engine, Data* data) {
    if (data->dungeonScene->sound->mobsDisplacement->moth != 0) {
        playEffect(engine->soundCollector, "dungeon/move_moth", 0);
    }
    resetEntitiesBool(data->dungeonScene->sound->mobsDisplacement);
}

static void notificationInventoryFull(Data* data) {
    Notification* notification = init_Notification();
    strcpy(notification->text, "Inventory full!");
    notification->sprite.w = 0;
    notification->sprite.h = 0;
    notification->sprite.x = 0;
    notification->sprite.y = 0;

    start_Timer(notification->timer);
    enQueue_Notification(data->dungeonScene->notificationQueue, notification);
}

static void movePlayer_BossRoom(Data* data) {
    if(isBoss_Room(data->dungeonScene->currentRoom) && !data->dungeonScene->currentRoom->cleaned) {
        // We move the player to avoid him to spawn on the boss
        data->Isaac->movement->position->x = 608;
        data->Isaac->movement->position->y = 505;
    }
}