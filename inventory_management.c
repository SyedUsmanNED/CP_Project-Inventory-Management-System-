#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
#include "inventory.h"

// typedef struct Items {
//     int id;
//     char name[50];
//     int quantity;
//     float price;
// } Items;

/* Also declared prototype here as well as in another file to know what the program actually does*/
void Add_items(void);
void Search_items(void);
void Update_items(void);
void Delete_items(void);
void Display_items(void);

// int id_exists(int id) {
//     FILE *fp = fopen("inventory.txt", "r");
//     if (fp == NULL) return 0;   /* no file yet, so no duplicates */

//     Items temp;
//     while (fscanf(fp, "%d | %s | %d | %f",
//                   &temp.id, temp.name, &temp.quantity, &temp.price) == 4) {
//         if (temp.id == id) {
//             fclose(fp);
//             return 1;
//         }
//     }
//     fclose(fp);
//     return 0;
// }

/* MAIN ONLY RESEVRED FOR FUNCTION CALLING AND MENU*/
int main() {
    int choice;

    do{
        // ********** INVENTORY MENU  ********** 
        printf("\n<================================= INVENTORY MANAGEMENT SYSTEM =================================>\n");
        printf("\n||                                   Choice #1  Add PRODUCT                                    ||\n");
        printf("\n||                                   Choice #2  Search PRODUCT                                 ||\n");
        printf("\n||                                   Choice #3  UPDATE PRODUCT                                 ||\n");
        printf("\n||                                   Choice #4  DELETE PRODUCT                                 ||\n");
        printf("\n||                                   Choice #5  DISPLAY PRODUCT                                ||\n");
        printf("\n||                                   Choice #6  EXIT                                           ||\n");
        printf("\n<================================= XXXXXXXXX XXXXXXXXXX XXXXXX =================================>\n");
        // Geting choice of user
        printf("\n Which Option Do You Want to Select (Enter Number)?:  ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            Add_items();
            break;
        case 2:
            Search_items();
            break;
        case 3:
           Update_items();
           break;
        case 4:
           Delete_items();
           break;
        case 5:
            Display_items();
            break;
        default:
            break;
        }
        
    }while (choice != 6);

    return 0;
}

// void Add_items(void) {
//     Items item;
//     FILE *fp;

//     printf("Enter Product ID: \n");
//     scanf("%d", &item.id);
//     while (id_exists(item.id)) {
//         printf("ID %d already exists. Enter a different ID: \n", item.id);
//         scanf("%d", &item.id);
//     }

//     printf("Enter Product Name: \n");
//     scanf(" %s", item.name);
//     printf("Enter Product Quantity: \n");
//     scanf("%d", &item.quantity);
//     printf("Enter Product Price: \n");
//     scanf("%f", &item.price);

//     fp = fopen("inventory.txt", "a");
//     fprintf(fp, "%d | %s | %d | %f\n", item.id, item.name, item.quantity, item.price);
//     fclose(fp);
// }

// void Search_items(void){
//     int s_id, found = 0;
//     Items item;
//     FILE *fp = fopen("inventory.txt", "r");

//     if (fp == NULL) {
//         printf("No products found.\n");
//         return;
//     }

//     printf("Enter ID to search: ");
//     scanf("%d", &s_id);

//     while (fscanf(fp, "%d | %s | %d | %f",
//         &item.id, item.name, &item.quantity, &item.price) == 4) {
//         if (item.id == s_id)
//         {
//             printf("\n%-8s %-20s %-12s %-10s\n\n", "ID", "Name", "Quantity", "Price");
//             printf("%-8d %-20s %-12d %-10.2f\n",
//                    item.id, item.name, item.quantity, item.price);
//             found = 1;
//             break;
//         }
        
//     }
//     if (!found){
//         printf("The id you have entered does not exist!\n");
//     }

//     fclose(fp);
//     getchar();
// }

// void Update_items(void){
//     int s_id, found = 0;
//     Items item;
//     FILE *fp = fopen("inventory.txt", "r");
//     FILE *temp;

//     if (fp == NULL) {
//         printf("No products found.\n");
//         return;
//     }

//     temp = fopen("temp.txt", "w");
//     if (temp == NULL) {
//         printf("Could not create temp file.\n");
//         fclose(fp);
//         return;
//     }

//     printf("Enter ID to update: ");
//     scanf("%d", &s_id);

//     while (fscanf(fp, "%d | %s | %d | %f",
//                   &item.id, item.name, &item.quantity, &item.price) == 4) {
//         if (item.id == s_id) {
//             found = 1;
//             printf("Enter new name: ");
//             scanf("%s", item.name);
//             printf("Enter new quantity: ");
//             scanf("%d", &item.quantity);
//             printf("Enter new price: ");
//             scanf("%f", &item.price);
//         }
//         fprintf(temp, "%d | %s | %d | %.2f\n",
//                 item.id, item.name, item.quantity, item.price);
//     }

//     fclose(fp);
//     fclose(temp);

//     if (found) {
//         remove("inventory.txt");
//         rename("temp.txt", "inventory.txt");
//         printf("Item updated successfully!\n");
//     } else {
//         remove("temp.txt");
//         printf("The id you have entered does not exist!\n");
//     }

//     getchar();
//     getchar();
// }

// void Delete_items(void) {
//     FILE *fp, *temp;
//     char line[256], input[64];
//     int d_id = 0, id, found = 0, got_id = 0;

//     fp = fopen("inventory.txt", "r");
//     if (fp == NULL) {
//         printf("No products found.\n");
//         return;
//     }

//     printf("Enter ID to delete: ");
//     while (fgets(input, sizeof(input), stdin) != NULL) {
//         if (sscanf(input, "%d", &d_id) == 1) {
//             got_id = 1;
//             break;
//         }
//         if (strspn(input, " \t\r\n") != strlen(input)) {
//             break;   // real text that isn't a number
//         }
//         // blank line (leftover newline): keep waiting for input
//     }

//     if (!got_id) {
//         printf("Invalid input!\n");
//         fclose(fp);
//         return;
//     }

//     temp = fopen("temp.txt", "w");
//     if (temp == NULL) {
//         printf("Could not create temporary file.\n");
//         fclose(fp);
//         return;
//     }

//     while (fgets(line, sizeof(line), fp) != NULL) {
//         if (sscanf(line, "%d", &id) == 1 && id == d_id) {
//             found = 1;               // skip this line
//         } else {
//             fputs(line, temp);       // copy every other line unchanged
//         }
//     }

//     fclose(fp);
//     fclose(temp);

//     if (found) {
//         remove("inventory.txt");
//         rename("temp.txt", "inventory.txt");
//         printf("Product deleted successfully!\n");
//     } else {
//         remove("temp.txt");          // original stays untouched
//         printf("The id you have entered does not exist!\n");
//     }

//     printf("Press Enter to continue...");
//     getchar();
// }

// void Display_items(void) {
//     Items item;
//     FILE *fp = fopen("inventory.txt", "r");

//     if (fp == NULL) {
//         printf("No products found.\n");
//         return;
//     }

//     printf("\n%-8s %-20s %-12s %-10s\n\n", "ID", "Name", "Quantity", "Price");
//     while (fscanf(fp, "%d | %s | %d | %f",
//                   &item.id, item.name, &item.quantity, &item.price) == 4) {
//         printf("%-8d %-20s %-12d %-10.2f\n",
//                item.id, item.name, item.quantity, item.price);
//     }

//     fclose(fp);
//     getchar();
// }