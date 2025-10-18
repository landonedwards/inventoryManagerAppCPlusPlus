#pragma once

#include <vector>
#include <string>
#include "item.h"

using namespace std;

class GroceryList
{
public:
   GroceryList(NecessityLevel threshold);

   void addItem(const Item& item)
   {
      neededItems.push_back(item);
   }

   bool removeItem(const string& name);

   double calculateTotalCost();

   double getTotalCost() const
   {
      return totalCost;
   }

   vector<Item> getItems() const
   {
      return neededItems;
   }

   void printFormattedList() const;

   bool saveToFile(const string& filename);

   void clear()
   {
      neededItems.clear();
      totalCost = 0.0;
   }

   vector<Item> filterByNecessity(const vector<Item>& items);

private:
   vector<Item> neededItems;
   double totalCost;
   string generatedDate;
   NecessityLevel necessityThreshold;
};