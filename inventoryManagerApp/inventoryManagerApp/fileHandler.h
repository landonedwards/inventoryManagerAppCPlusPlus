#pragma once

#include <string>
#include <vector>
#include "item.h"

using namespace std;

class FileHandler
{
public:
   static bool saveTextFile(const string& filename, const string& content);

   static bool saveInventoryToCsv(const string& filename, const vector<Item>& items);

   static vector<Item> loadInventoryFromCsv(const string& filename);
};