#include "filehandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

/******************************************
 * FILE HANDLER : SAVE TEXT FILE
 * Save a string content to a text file
 * Returns true if successful, false otherwise
 *****************************************/
bool FileHandler::saveTextFile(const string& filename, const string& content)
{
   ofstream fout;
   fout.open(filename);

   if (fout.fail())
   {
      return false;
   }

   fout << content;
   fout.close();
   return true;
}

/******************************************
 * FILE HANDLER : SAVE INVENTORY TO CSV
 * Save all inventory items to a CSV file
 * Returns true if successful, false otherwise
 *****************************************/
bool FileHandler::saveInventoryToCsv(const string& filename, const vector<Item>& items)
{
   ofstream fout;
   fout.open(filename);

   if (fout.fail())
   {
      return false;
   }

   // Write header row
   fout << "name,category,currentQty,desiredQty,necessity,avgCost\n";

   // Write each item
   for (const Item& item : items)
   {
      fout << item.getName() << ","
           << int(item.getCategory()) << ","
           << item.getCurrentQuantity() << ","
           << item.getDesiredQuantity() << ","
           << int(item.getNecessityValue()) << ","
           << item.getAverageCost() << "\n";
   }

   fout.close();
   return true;
}

/******************************************
 * FILE HANDLER : LOAD INVENTORY FROM CSV
 * Load inventory items from a CSV file
 * Returns vector of items read from file
 *****************************************/
vector<Item> FileHandler::loadInventoryFromCsv(const string& filename)
{
   vector<Item> items;
   ifstream fin;
   fin.open(filename);

   if (fin.fail())
   {
      return items;
   }

   string line;
   // Skip header row
   getline(fin, line);

   // Read each line
   while (getline(fin, line))
   {
      stringstream ss(line);
      string name;
      int categoryInt, currentQty, desiredQty, necessityInt;
      double avgCost;

      // Parse CSV line
      getline(ss, name, ',');

      string temp;
      getline(ss, temp, ',');
      categoryInt = stoi(temp);

      getline(ss, temp, ',');
      currentQty = stoi(temp);

      getline(ss, temp, ',');
      desiredQty = stoi(temp);

      getline(ss, temp, ',');
      necessityInt = stoi(temp);

      getline(ss, temp, ',');
      avgCost = stod(temp);

      // Convert integers back to enums
      Category category = Category(categoryInt);
      NecessityLevel necessity = NecessityLevel(necessityInt);

      // Create item and add to vector
      Item item(name, category, currentQty, desiredQty, necessity, avgCost);
      items.push_back(item);
   }

   file.close();
   return items;
}