#include <iostream>
#include "menu.h"
#include "inventorymanager.h"

using namespace std;

int main()
{
   cout << "Welcome to the Inventory Management App!\n";
   cout << "Loading inventory...\n";

   // Initialize inventory manager with CSV file path
   InventoryManager manager("inventory.csv");

   // Create and run menu
   Menu menu(manager);
   menu.run();

   // Save inventory before exiting
   if (manager.saveInventory())
   {
      cout << "Inventory saved. Goodbye!\n";
   }

   return 0;
}