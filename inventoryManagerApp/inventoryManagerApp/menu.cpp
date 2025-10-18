#include "menu.h"
#include <iostream>
#include <limits>

using namespace std;

/******************************************
 * MENU : CONSTRUCTOR
 * Initialize menu with inventory manager
 *****************************************/
Menu::Menu(InventoryManager& manager) : manager(manager)
{
}

/******************************************
 * MENU : RUN
 * Main menu loop - runs until user exits
 *****************************************/
void Menu::run()
{
   int choice = 0;

   while (choice != 5)
   {
      displayMainMenu();
      choice = getIntInput("Enter your choice: ");

      switch (choice)
      {
      case 1:
         displayInventoryMenu();
         break;
      case 2:
         displayGroceryMenu();
         break;
      case 3:
         manager.viewAllItems();
         break;
      case 4:
         if (manager.saveInventory())
         {
            cout << "Inventory saved successfully!\n";
         }
         else
         {
            cout << "Error saving inventory.\n";
         }
         break;
      case 5:
         cout << "Exiting... Goodbye!\n";
         break;
      default:
         cout << "Invalid choice. Please try again.\n";
      }
   }
}

/******************************************
 * MENU : DISPLAY MAIN MENU
 * Show the main menu options
 *****************************************/
void Menu::displayMainMenu()
{
   cout << "\n========================================\n";
   cout << "    INVENTORY MANAGEMENT SYSTEM\n";
   cout << "========================================\n";
   cout << "1. Manage Inventory\n";
   cout << "2. Generate Grocery List\n";
   cout << "3. View All Items\n";
   cout << "4. Save Inventory\n";
   cout << "5. Exit\n";
   cout << "========================================\n";
}

/******************************************
 * MENU : DISPLAY INVENTORY MENU
 * Show inventory management submenu
 *****************************************/
void Menu::displayInventoryMenu()
{
   int choice = 0;

   while (choice != 5)
   {
      cout << "\n========================================\n";
      cout << "       INVENTORY MANAGEMENT\n";
      cout << "========================================\n";
      cout << "1. Add New Item\n";
      cout << "2. Update Item\n";
      cout << "3. Remove Item\n";
      cout << "4. Search Items\n";
      cout << "5. Back to Main Menu\n";
      cout << "========================================\n";

      choice = getIntInput("Enter your choice: ");

      switch (choice)
      {
      case 1:
         manager.addNewItem();
         break;
      case 2:
         manager.updateItem();
         break;
      case 3:
         manager.removeItem();
         break;
      case 4:
      {
         string keyword = getStringInput("Enter search keyword: ");
         manager.searchItems(keyword);
         break;
      }
      case 5:
         cout << "Returning to main menu...\n";
         break;
      default:
         cout << "Invalid choice. Please try again.\n";
      }
   }
}

/******************************************
 * MENU : DISPLAY GROCERY MENU
 * Show grocery list generation options
 *****************************************/
void Menu::displayGroceryMenu()
{
   cout << "\n========================================\n";
   cout << "      GENERATE GROCERY LIST\n";
   cout << "========================================\n";
   cout << "Select minimum necessity level:\n";
   cout << "1. LOW - Include all items\n";
   cout << "2. MEDIUM - Include medium priority and above\n";
   cout << "3. HIGH - Include high priority only\n";
   cout << "4. CRITICAL - Include critical items only\n";
   cout << "5. Back to Main Menu\n";
   cout << "========================================\n";

   int choice = getIntInput("Enter your choice: ");

   if (choice >= 1 && choice <= 4)
   {
      NecessityLevel threshold = static_cast<NecessityLevel>(choice);
      GroceryList list = manager.generateGroceryList(threshold);

      list.printFormattedList();

      string save = getStringInput("Would you like to save this list? (y/n): ");
      if (save == "y" || save == "Y")
      {
         manager.promptAndSaveGroceryList(list);
      }
   }
   else if (choice != 5)
   {
      cout << "Invalid choice.\n";
   }
}

/******************************************
 * MENU : GET INT INPUT
 * Prompt user and get integer input with
 * validation
 *****************************************/
int Menu::getIntInput(const string& prompt)
{
   int value;
   cout << prompt;

   while (!(cin >> value))
   {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a number: ";
   }

   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   return value;
}

/******************************************
 * MENU : GET DOUBLE INPUT
 * Prompt user and get double input with
 * validation
 *****************************************/
double Menu::getDoubleInput(const string& prompt)
{
   double value;
   cout << prompt;

   while (!(cin >> value))
   {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a number: ";
   }

   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   return value;
}

/******************************************
 * MENU : GET STRING INPUT
 * Prompt user and get string input
 *****************************************/
string Menu::getStringInput(const string& prompt)
{
   string value;
   cout << prompt;
   getline(cin, value);
   return value;
}