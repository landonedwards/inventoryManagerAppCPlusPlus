#pragma once

#include <string>
#include "inventorymanager.h"

using namespace std;

class Menu
{
public:
   Menu(InventoryManager& manager);

   void run();

   void displayMainMenu();

   void displayInventoryMenu();

   void displayGroceryMenu();

private:
   InventoryManager& manager;

   int getIntInput(const string& prompt);

   double getDoubleInput(const string& prompt);

   string getStringInput(const string& prompt);
};