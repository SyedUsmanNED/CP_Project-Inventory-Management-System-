INVENTORY MANAGEMENT SYSTEM - CS-115 C PROJECT
================================================

FILES
-----
1. inventory_management.c  - Complete C source code.
2. inventory.txt            - Sample inventory records. The program reads and
                               updates this file automatically.
3. README.txt               - This instruction file.

REQUIREMENTS COVERED
--------------------
- Add new records with validation.
- Display all records in a formatted table.
- Search by item ID or full item name.
- Update existing records.
- Delete records after confirmation.
- Save and load records through file handling.
- Low-stock report.
- Inventory summary showing total units and stock value.

HOW TO COMPILE
--------------
Windows (MinGW GCC):
    gcc -std=c11 -Wall -Wextra inventory_management.c -o inventory.exe
    inventory.exe

Linux:
    gcc -std=c11 -Wall -Wextra inventory_management.c -o inventory
    ./inventory

IMPORTANT
---------
Keep inventory_management.c and inventory.txt in the same folder when running
the program. On startup, the program loads inventory.txt. Changes are saved
automatically after add, update, and delete operations. Choose "Save and exit"
before closing the program.

DATA FILE FORMAT
----------------
Each record is stored on one line:
ID|Name|Category|Quantity|UnitPrice|Supplier

The vertical bar character (|) is reserved as a separator and cannot be used
inside an entered field. Sample data uses example products and prices in PKR.
