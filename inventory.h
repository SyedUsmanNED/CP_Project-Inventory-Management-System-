#ifndef INVI_H
#define INVI_H


typedef struct Items {
    int id;
    char name[50];
    int quantity;
    float price;
} Items;

int id_exists(int id);
void Add_items(void);
void Search_items(void);
void Update_items(void);
void Delete_items(void);
void Display_items(void);

#endif