
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventory.h"

/* A SEPERATE MODULE TO TEST WHETHER A NEW ADDED ID ALREADLY EXIST OR NOT CALLED IN ADD MODULE LATER*/
int id_exists(int id) {
    FILE *fp = fopen("inventory.txt", "r");
    if (fp == NULL) return 0;   /* no file yet, so no duplicates */

    Items temp;
    while (fscanf(fp, "%d | %s | %d | %f",
                  &temp.id, temp.name, &temp.quantity, &temp.price) == 4) {
        if (temp.id == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
    /* TO ADD PRODUCTS INTO OR MANAGEMENT SYSTEM */
    /* EACH INPUT PRODUCT IS ADDED TO FILE TO PRESERVE DATA*/
void Add_items(void) {
    int cont;
    Items item;
    FILE *fp;
    while(1){
    printf("Enter Product ID: \n");
    scanf("%d", &item.id);
    while (id_exists(item.id)) {   /* Called module to test id */
        printf("ID %d already exists. Enter a different ID: \n", item.id);
        scanf("%d", &item.id);
    }
    
    printf("Enter Product Name: \n");
    scanf(" %s", item.name);
    printf("Enter Product Quantity: \n");
    scanf("%d", &item.quantity);
    printf("Enter Product Price(IN PKR): \n");
    scanf("%f", &item.price);

    fp = fopen("inventory.txt", "a");
    fprintf(fp, "%d | %s | %d | %f\n", item.id, item.name, item.quantity, item.price);

    printf("\n");
    
    /* A FUCTION TO KEEP ASKING OPERATOR TO WHETHER HE WANT TO ADD ANOTHER PRODUCT OR NOT BASED ON HIS RESPONSE */
    printf("DO YOU WANT TO ADD MORE PRODUCTS?(1 FOR YES AND 0 FOR NO): ");
        scanf("%d",&cont);
        if(cont == 1)
        continue;
        if(cont == 0)
        break;
        else if (cont != 0 && cont != 1){
        printf("\n<------Input Correct Option------>\n\n");
        continue;
        }
    
    }
    printf("\n");
    fclose(fp);  /* A MUST TO CLOSE A FILE AFTER OPENING IT */

}

/* A MODULE TO SEARCH ANY INPUT ID IN FILES WHETHER EXIST OR NOT AND IF EXIST THEN DEATILS OF THE PRODUCT UNDER THAT ID*/

void Search_items(void){
    int s_id, found = 0;
    Items item;
    FILE *fp = fopen("inventory.txt", "r");

    if (fp == NULL) {   /* TO GRACEFULLY ENCOUNTER THE SITUATION IF THERE IS NO DATA IN FILE */
        printf("No products found.\n");
        return;
    }

    printf("Enter ID to search: ");
    scanf("%d", &s_id);

    while (fscanf(fp, "%d | %s | %d | %f",
        &item.id, item.name, &item.quantity, &item.price) == 4) {
        if (item.id == s_id)
        {
            printf("\n%-8s %-20s %-12s %-10s\n\n", "ID", "Name", "Quantity", "Price");
            printf("%-8d %-20s %-12d Rs. %-10.2f\n",
                   item.id, item.name, item.quantity, item.price);
            found = 1;
            break;
        }
        
    }
    if (!found){   /* TO GRACEFULLY ENCOUNTER THE SINARIO IN CASE ID DONT EXIST*/
        printf("The id you have entered does not exist!\n");
    }

    fclose(fp);
    getchar();
}

 /* TO UPDATE A DETAILS OF A PRODUCT IN CASE THERE IS ANY CHANGE IN A PRODUCT*/
void Update_items(void){
    int s_id, found = 0;
    Items item;
    FILE *fp = fopen("inventory.txt", "r");
    FILE *temp;

    if (fp == NULL) {
        printf("No products found.\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Could not create temp file.\n");
        fclose(fp);
        return;
    }

    printf("Enter ID to update: ");
    scanf("%d", &s_id);

    while (fscanf(fp, "%d | %s | %d | %f",
                  &item.id, item.name, &item.quantity, &item.price) == 4) {
        if (item.id == s_id) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", item.name);
            printf("Enter new quantity: ");
            scanf("%d", &item.quantity);
            printf("Enter new price(IN PKR): ");
            scanf("%f", &item.price);
        }
        fprintf(temp, "%d | %s | %d | %.2f\n",
                item.id, item.name, item.quantity, item.price);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        printf("Item updated successfully!\n");
    } else {
        remove("temp.txt");
        printf("The id you have entered does not exist!\n");
    }

    getchar();
    getchar();
}
/* TO DELETE AN ALREADY EXISTING PRODUCT USING ITS ID */
void Delete_items(void) {
    FILE *fp, *temp;
    char line[256], input[64];
    int d_id = 0, id, found = 0, got_id = 0;

    fp = fopen("inventory.txt", "r");
    if (fp == NULL) {
        printf("No products found.\n");
        return;
    }

    printf("Enter ID to delete: ");
    while (fgets(input, sizeof(input), stdin) != NULL) {
        if (sscanf(input, "%d", &d_id) == 1) {
            got_id = 1;
            break;
        }
        if (strspn(input, " \t\r\n") != strlen(input)) {
            break;   // real text that isn't a number
        }
        // blank line (leftover newline): keep waiting for input
    }

    if (!got_id) {
        printf("Invalid input!\n");
        fclose(fp);
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Could not create temporary file.\n");
        fclose(fp);
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "%d", &id) == 1 && id == d_id) {
            found = 1;               // skip this line
        } else {
            fputs(line, temp);       // copy every other line unchanged
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        printf("Product deleted successfully!\n");
    } else {
        remove("temp.txt");          // original stays untouched
        printf("The id you have entered does not exist!\n");
    }

    printf("Press Enter to continue...");
    getchar();
}

/* TO DISPLAY THE ENTIRE PRODUCT LIST WITH ALL DETAILS*/
void Display_items(void) {
    Items item;
    FILE *fp = fopen("inventory.txt", "r");

    if (fp == NULL) {
        printf("No products found.\n");
        return;
    }

    printf("\n%-8s %-20s %-12s %-10s\n\n", "ID", "Name", "Quantity", "Price");
    while (fscanf(fp, "%d | %s | %d | %f",
                  &item.id, item.name, &item.quantity, &item.price) == 4) {
        printf("%-8d %-20s %-12d Rs. %-10.2f\n",
               item.id, item.name, item.quantity, item.price);
    }

    fclose(fp);
    getchar();
}



