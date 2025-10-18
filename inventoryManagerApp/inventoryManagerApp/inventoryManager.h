#pragma once

#include <string>
#include "inventory.h"
#include "grocerylist.h"

using namespace std;

class InventoryManager
{
public:
   InventoryManager(const string& filePath);

   void addNewItem();

   void updateItem();

   void removeItem();

   void viewAllItems();

   void searchItems(const string& keyword);

   GroceryList generateGroceryList(NecessityLevel threshold);

   void promptAndSaveGroceryList(GroceryList& list);

   bool saveInventory();

   bool loadInventory();

private:
   Inventory inventory;
};