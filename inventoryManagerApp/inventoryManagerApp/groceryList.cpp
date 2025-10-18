#include "grocerylist.h"
#include "filehandler.h"
#include <iostream>
#include <iomanip>
#include <sstream>

/******************************************
 * GROCERY LIST : CONSTRUCTOR
 * Initialize grocery list with necessity
 * threshold and set generated date
 *****************************************/
GroceryList::GroceryList(NecessityLevel threshold)
   : necessityThreshold(threshold), totalCost(0.0)
{
   generatedDate = "2025-10-17";
}

/******************************************
 * GROCERY LIST : REMOVE ITEM
 * Remove an item from the grocery list by name
 * Returns true if removed, false if not found
 *****************************************/
bool GroceryList::removeItem(const string& name)
{
   for (auto it = neededItems.begin(); it != neededItems.end(); it++)
   {
      if (it->getName() == name)
      {
         neededItems.erase(it);
         return true;
      }
   }
   return false;
}

/******************************************
 * GROCERY LIST : CALCULATE TOTAL COST
 * Calculate and return the total cost of
 * all items on the grocery list
 *****************************************/
double GroceryList::calculateTotalCost()
{
   totalCost = 0.0;
   for (const Item& item : neededItems)
   {
      totalCost += item.getQuantityNeeded() * item.getAverageCost();
   }
   return totalCost;
}

/******************************************
 * GROCERY LIST : PRINT FORMATTED LIST
 * Display the grocery list in a formatted
 * way to the terminal
 *****************************************/
void GroceryList::printFormattedList() const
{
   cout << "\n========================================\n";
   cout << "GROCERY LIST - Generated: " << generatedDate << "\n";
   cout << "========================================\n\n";

   for (const Item& item : neededItems)
   {
      cout << item.getName() << " x" << item.getQuantityNeeded()
         << " - $" << fixed << setprecision(2)
         << (item.getQuantityNeeded() * item.getAverageCost()) << "\n";
   }

   cout << "----------------------------------------\n";
   cout << "TOTAL COST: $" << fixed << setprecision(2) << totalCost << "\n";
   cout << "========================================\n\n";
}

/******************************************
 * GROCERY LIST : SAVE TO FILE
 * Save the formatted grocery list to a
 * text file. Returns true if successful
 *****************************************/
bool GroceryList::saveToFile(const string& filename)
{
   stringstream ss;
   ss << "\n========================================\n";
   ss << "GROCERY LIST - Generated: " << generatedDate << "\n";
   ss << "========================================\n\n";

   for (const Item& item : neededItems)
   {
      ss << item.getName() << " x" << item.getQuantityNeeded()
         << " - $" << fixed << setprecision(2)
         << (item.getQuantityNeeded() * item.getAverageCost()) << "\n";
   }

   ss << "----------------------------------------\n";
   ss << "TOTAL COST: $" << fixed << setprecision(2) << totalCost << "\n";
   ss << "========================================\n\n";

   return FileHandler::saveTextFile(filename, ss.str());
}

/******************************************
 * GROCERY LIST : FILTER BY NECESSITY
 * Filter items based on necessity threshold
 * and restock needs. Returns filtered vector
 *****************************************/
vector<Item> GroceryList::filterByNecessity(const vector<Item>& items)
{
   vector<Item> filtered;
   for (const Item& item : items)
   {
      if (item.needsRestock() &&
         item.getNecessityValue() >= necessityThreshold)
      {
         filtered.push_back(item);
      }
   }
   return filtered;
}