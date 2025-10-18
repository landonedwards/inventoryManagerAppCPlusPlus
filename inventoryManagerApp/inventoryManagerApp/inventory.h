#pragma once

#include <vector>
#include <string>
#include "item.h"

using namespace std;

class Inventory
{
public:
   Inventory(const string& filePath);

   Item* getItem(const string& name);
   
   vector<Item> getAllItems()
   {
      return items;
   }

   vector<Item> getLowStockItems();

   void addItem(const Item& item)
   {
      items.push_back(item);
   }

   bool removeItem(const string& name);

   void updateItemQuantity(const string& name, int quantity);

   bool saveToFile();

   bool loadFromFile();

   vector<Item> searchItems(const string& keyword);

private:
   vector<Item> items;
   string filePath;
};