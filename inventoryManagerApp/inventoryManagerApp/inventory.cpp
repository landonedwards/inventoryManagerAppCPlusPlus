#include "inventory.h"
#include "fileHandler.h"

/******************************************
 * INVENTORY : CONSTRUCTOR
 * Initialize inventory with file path
 *****************************************/
Inventory::Inventory(const string& filePath) : filePath(filePath)
{
}

/******************************************
 * INVENTORY : GET ITEM
 * Get a specific item by name. Returns
 * pointer to item if found, nullptr if not
 *****************************************/
Item* Inventory::getItem(const string& name)
{
   for (int i = 0; i < items.size(); i++)
   {
      if (items[i].getName() == name)
      {
         return &items[i];
      }
   }
   return nullptr;
}

/******************************************
 * INVENTORY : GET LOW STOCK ITEMS
 * Returns a vector of items that need
 * restocking based on needsRestock()
 *****************************************/
vector<Item> Inventory::getLowStockItems()
{
   vector<Item> lowStockItems;
   for (int i = 0; i < items.size(); i++)
   {
      if (items[i].needsRestock())
      {
         lowStockItems.push_back(items[i]);
      }
   }
   return lowStockItems;
}

/******************************************
 * INVENTORY : REMOVE ITEM
 * Remove an item by name. Returns true
 * if item was found and removed, false
 * if item was not found
 *****************************************/
bool Inventory::removeItem(const string& name)
{
   for (auto it = items.begin(); it != items.end(); it++)
   {
      if (it->getName() == name)
      {
         items.erase(it);
         return true;
      }
   }
   return false;
}

/******************************************
 * INVENTORY : UPDATE ITEM QUANTITY
 * Update the desired quantity of an item
 * by name
 *****************************************/
void Inventory::updateItemQuantity(const string& name, int quantity)
{
   Item* item = getItem(name);
   if (item != nullptr)
   {
      item->setCurrentQuantity(quantity);
   }
}

/******************************************
 * INVENTORY : SAVE TO FILE
 * Save all inventory items to a CSV file
 * Returns true if successful, false otherwise
 *****************************************/
bool Inventory::saveToFile()
{
   return FileHandler::saveInventoryToCsv(filePath, items);
}

/******************************************
 * INVENTORY : LOAD FROM FILE
 * Load inventory items from a CSV file
 * Returns true if successful, false otherwise
 *****************************************/
bool Inventory::loadFromFile()
{
   items = FileHandler::loadInventoryFromCsv(filePath);
   return !items.empty();
}

/******************************************
 * INVENTORY : SEARCH ITEMS
 * Search for items by keyword in name
 * Returns vector of matching items
 *****************************************/
vector<Item> Inventory::searchItems(const string& keyword)
{
   vector<Item> searchResults;
   for (int i = 0; i < items.size(); i++)
   {
      if (items[i].getName().find(keyword) != string::npos)
      {
         searchResults.push_back(items[i]);
      }
   }
   return searchResults;
}