#ifndef FREE_PROJECT_DATAS_H
#define FREE_PROJECT_DATAS_H

typedef struct mainMenu_t {
    int position;
} mainMenu_t;

typedef struct Data {
    struct mainMenu_t* mainMenu;
} Data;

extern Data* init_Data();
extern void clean_Data(Data** myData);

#endif //FREE_PROJECT_DATAS_H
