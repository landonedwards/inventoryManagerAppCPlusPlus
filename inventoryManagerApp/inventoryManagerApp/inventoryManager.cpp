#include "inventorymanager.h"
#include "filehandler.h"
#include <iostream>
#include <iomanip>

using namespace std;

/******************************************
 * INVENTORY MANAGER : CONSTRUCTOR
 * Initialize inventory manager with file path
 *****************************************/
InventoryManager::InventoryManager(const string& filePath)
   : inventory(filePath)
{
   loadInventory();
}

/******************************************
 * INVENTORY MANAGER : ADD NEW ITEM
 * Prompt user for item details and add to inventory
 *****************************************/
void InventoryManager::addNewItem()
{
   string name;
   int categoryInt, currentQty, desiredQty, necessityInt;
   double avgCost;

   cout << "\n--- Add New Item ---\n";
   cout << "Name: ";
   getline(cin, name);

   cout << "Category (1=Ingredient, 2=Food, 3=Cleaning, 4=Hygiene, 5=Beverages): ";
   cin >> categoryInt;

   cout << "Current Quantity: ";
   cin >> currentQty;

   cout << "Desired Quantity: ";
   cin >> desiredQty;

   cout << "Necessity (1=Low, 2=Medium, 3=High, 4=Critical): ";
   cin >> necessityInt;

   cout << "Average Cost: $";
   cin >> avgCost;

   Category category = Category(categoryInt);
   NecessityLevel necessity = NecessityLevel(necessityInt);

   Item newItem(name, category, currentQty, desiredQty, necessity, avgCost);
   inventory.addItem(newItem);

   cout << "Item added successfully!\n";
}

/******************************************
 * INVENTORY MANAGER : UPDATE ITEM
 * Update an existing item's quantity
 *****************************************/
void InventoryManager::updateItem()
{
   string name;
   int newQty;

   cout << "\n--- Update Item ---\n";
   cout << "Item name: ";
   getline(cin, name);

   Item* item = inventory.getItem(name);
   if (item == nullptr)
   {
      cout << "Item not found.\n";
      return;
   }

   cout << "Current quantity: " << item->getCurrentQuantity() << "\n";
   cout << "New quantity: ";
   cin >> newQty;

   inventory.updateItemQuantity(name, newQty);
   cout << "Item updated successfully!\n";
}

/******************************************
 * INVENTORY MANAGER : REMOVE ITEM
 * Remove an item from inventory
 *****************************************/
void InventoryManager::removeItem()
{
   string name;

   cout << "\n--- Remove Item ---\n";
   cout << "Item name: ";
   getline(cin, name);

   if (inventory.removeItem(name))
   {
      cout << "Item removed successfully!\n";
   }
   else
   {
      cout << "Item not found.\n";
   }
}

/******************************************
 * INVENTORY MANAGER : VIEW ALL ITEMS
 * Display all items in inventory
 *****************************************/
void InventoryManager::viewAllItems()
{
   vector<Item> items = inventory.getAllItems();

   if (items.empty())
   {
      cout << "\nNo items in inventory.\n";
      return;
   }

   cout << "\n========================================\n";
   cout << "           ALL INVENTORY ITEMS\n";
   cout << "========================================\n";

   for (const Item& item : items)
   {
      cout << "\nName: " << item.getName() << "\n";
      cout << "Category: " << int(item.getCategory()) << "\n";
      cout << "Current Qty: " << item.getCurrentQuantity() << "\n";
      cout << "Desired Qty: " << item.getDesiredQuantity() << "\n";
      cout << "Necessity: " << int(item.getNecessityValue()) << "\n";
      cout << "Avg Cost: $" << fixed << setprecision(2) << item.getAverageCost() << "\n";
      cout << "----------------------------------------\n";
   }
}

/******************************************
 * INVENTORY MANAGER : SEARCH ITEMS
 * Search and display matching items
 *****************************************/
void InventoryManager::searchItems(const string& keyword)
{
   vector<Item> results = inventory.searchItems(keyword);

   if (results.empty())
   {
      cout << "\nNo items found matching '" << keyword << "'.\n";
      return;
   }

   cout << "\n--- Search Results for '" << keyword << "' ---\n";
   for (const Item& item : results)
   {
      cout << item.getName() << " - Qty: " << item.getCurrentQuantity() << "\n";
   }
}

/******************************************
 * INVENTORY MANAGER : GENERATE GROCERY LIST
 * Create grocery list based on necessity threshold
 *****************************************/
GroceryList InventoryManager::generateGroceryList(NecessityLevel threshold)
{
   GroceryList list(threshold);
   vector<Item> allItems = inventory.getAllItems();
   vector<Item> filteredItems = list.filterByNecessity(allItems);

   for (const Item& item : filteredItems)
   {
      list.addItem(item);
   }

   list.calculateTotalCost();
   return list;
}

/******************************************
 * INVENTORY MANAGER : PROMPT AND SAVE GROCERY LIST
 * Ask user if they want to save the grocery list
 *****************************************/
void InventoryManager::promptAndSaveGroceryList(GroceryList& list)
{
   string filename;
   cout << "Enter filename (e.g., grocerylist.txt): ";
   cin.ignore();
   getline(cin, filename);

   if (list.saveToFile(filename))
   {
      cout << "Grocery list saved to " << filename << "!\n";
   }
   else
   {
      cout << "Error saving grocery list.\n";
   }
}

/******************************************
 * INVENTORY MANAGER : SAVE INVENTORY
 * Save inventory to CSV file
 *****************************************/
bool InventoryManager::saveInventory()
{
   return inventory.saveToFile();
}

/******************************************
 * INVENTORY MANAGER : LOAD INVENTORY
 * Load inventory from CSV file
 *****************************************/
bool InventoryManager::loadInventory()
{
   return inventory.loadFromFile();
}