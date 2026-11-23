
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventory.h"

/* A SEPERATE MODULE TO TEST WHETHER A NEW ADDED ID ALREADLY EXIST OR NOT CALLED IN ADD MODULE LATER*/
/* This function checks if a product ID is already saved in the file.
   It returns 1 if the ID is found, and 0 if it is not found. */
int id_exists(int id) {
    /* Open the file "inventory.txt" in read mode ("r") */
    FILE *fp = fopen("inventory.txt", "r");

    /* If the file could not be opened (fp is NULL), the file does not exist yet */
    if (fp == NULL) return 0;   /* no file yet, so no duplicates */

    /* Make a temporary variable to hold one product's data at a time */
    Items temp;

    /* Read the file line by line.
       fscanf reads the 4 values: id, name, quantity and price.
       It returns 4 when all 4 values were read properly.
       When the file ends (or the line is wrong), it returns something else and the loop stops. */
    while (fscanf(fp, "%d | %s | %d | %f",
                  &temp.id, temp.name, &temp.quantity, &temp.price) == 4) {

        /* Compare the ID from the file with the ID we are searching for */
        if (temp.id == id) {
            fclose(fp);   /* close the file before leaving the function */
            return 1;     /* ID found, so it already exists */
        }
    }

    /* We checked every line and found no match, so close the file */
    fclose(fp);
    return 0;   /* ID not found, so it does not exist */
}
 /* TO ADD PRODUCTS INTO OR MANAGEMENT SYSTEM */
    /* EACH INPUT PRODUCT IS ADDED TO FILE TO PRESERVE DATA*/
/* This function takes product details from the user and saves them in the file. */
void Add_items(void) {
    int cont;      /* stores the user's answer: 1 = add more, 0 = stop */
    Items item;    /* a variable to hold one product's details */
    FILE *fp;      /* a pointer used to work with the file */

    /* This loop keeps running so the user can add many products one after another */
    while(1){
    /* Ask the user for the product ID and store it in item.id */
    printf("Enter Product ID: \n");
    scanf("%d", &item.id);

    /* If the ID is already in the file, keep asking until the user enters a new one */
    while (id_exists(item.id)) {   /* Called module to test id */
        printf("ID %d already exists. Enter a different ID: \n", item.id);
        scanf("%d", &item.id);
    }
    
    /* Ask for the product name (the space before %s skips any leftover Enter key) */
    printf("Enter Product Name: \n");
    scanf(" %s", item.name);

    /* Ask for how many pieces of the product we have */
    printf("Enter Product Quantity: \n");
    scanf("%d", &item.quantity);

    /* Ask for the price of one piece */
    printf("Enter Product Price(IN PKR): \n");
    scanf("%f", &item.price);

    /* Open the file in append mode ("a"), which adds new data at the end
       and does not delete the old data */
    fp = fopen("inventory.txt", "a");

    /* Write the product in the file as one line, with | between the values */
    fprintf(fp, "%d | %s | %d | %f\n", item.id, item.name, item.quantity, item.price);

    printf("\n");
    
    /* A FUCTION TO KEEP ASKING OPERATOR TO WHETHER HE WANT TO ADD ANOTHER PRODUCT OR NOT BASED ON HIS RESPONSE */
    printf("DO YOU WANT TO ADD MORE PRODUCTS?(1 FOR YES AND 0 FOR NO): ");
        scanf("%d",&cont);

        /* If the user typed 1, go back to the start of the loop and add another product */
        if(cont == 1)
        continue;

        /* If the user typed 0, leave the loop because we are finished */
        if(cont == 0)
        break;

        /* If the user typed anything else, show a message and ask again */
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
    char line[256];
    int d_id, id, found = 0;

    fp = fopen("inventory.txt", "r");
    if (fp == NULL) {
        printf("No products found.\n");
        return;
    }

    printf("Enter ID to delete: ");
    if (scanf("%d", &d_id) != 1) {
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
            found = 1; // skip matching item
        } else {
            fputs(line, temp); // keep all other lines
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        printf("Product deleted successfully!\n");
    } else {
        remove("temp.txt");
        printf("ID not found!\n");
    }
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



