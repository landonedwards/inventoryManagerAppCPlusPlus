#include "item.h"

/******************************************
 * ITEM : CONSTRUCTOR
 * Initialize item with all properties
 *****************************************/
Item::Item(const string& name, Category category, int currentQty,
           int desiredQty, NecessityLevel necessity, double avgCost)
   : name(name), category(category), currentQuantity(currentQty),
     desiredQuantity(desiredQty), necessityValue(necessity), averageCost(avgCost)
{
}

/******************************************
 * ITEM : SET NECESSITY VALUE
 * Set the necessity value of an item with
 * the integer provided by the user
 *****************************************/
void Item::setNecessityValue(int value)
{
   if (value >= 1 && value <= 4)
   {
      necessityValue = NecessityLevel(value);
   }
   else
   {
      necessityValue = NecessityLevel::LOW;
   }
}
