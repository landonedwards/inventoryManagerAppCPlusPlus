#pragma once

#include <string>

using namespace std;

enum Category {
   INGREDIENT = 1,
   FOOD = 2,                   // ready to eat items
   CLEANING = 3,               // soap, dishwasher pods, laundry pods
   HYGIENE = 4,                // toothpaste, deodarant
   BEVERAGES = 5
};

enum NecessityLevel {
   LOW = 1,
   MEDIUM = 2,
   HIGH = 3,
   CRITICAL = 4
};

/*********************************************
 * ITEM
 *********************************************/
class Item
{
public:

   Item(const string& name, Category category, int currentQty,
      int desiredQty, NecessityLevel necessity, double avgCost);

   // Getters

   string getName() const
   {
      return name;
   }

   Category getCategory() const
   {
      return category;
   }

   int getCurrentQuantity() const
   {
      return currentQuantity;
   }

   int getDesiredQuantity() const
   {
      return desiredQuantity;
   }

   NecessityLevel getNecessityValue() const
   {
      return necessityValue;
   }

   double getAverageCost() const
   {
      return averageCost;
   }

   // Setters

   void setCurrentQuantity(int quantity)
   {
      currentQuantity = quantity;
   }

   void setDesiredQuantity(int quantity)
   {
      desiredQuantity = quantity;
   }

   void setNecessityValue(int value);

   void setAverageCost(double cost)
   {
      averageCost = cost;
   }

   bool needsRestock() const
   {
      return currentQuantity < desiredQuantity;
   }

   int getQuantityNeeded() const
   {
      return desiredQuantity - currentQuantity;
   }

private:

   string name;
   Category category;
   int currentQuantity;
   int desiredQuantity;
   NecessityLevel necessityValue;
   double averageCost;
};
