#pragma once

#include <iostream>
#include <filesystem>
#include <memory>
#include "tinyxml2.h"
#include "user.h"
#include "condition.h"
#include <conio.h>

using namespace tinyxml2;
using namespace std::experimental::filesystem;

class Menu
{
public:
   enum NodeType { AND, OR };
public:
   Menu() = default;
   void run();  
private:
   User user;
   std::vector<std::unique_ptr<Condition>> conditions;
   NodeType type;
      
   Menu(const Menu&) = delete;
   Menu& operator = (const Menu&) = delete;
      
   bool xmlCheckResult(XMLError result);    
   void fillPlayerInfo(XMLDocument* doc);
   void fillConditions(XMLDocument* doc);
   void inputFileName(XMLDocument* doc, const std::string& invitation);
   void addCondition(XMLNode* node, bool isNot = false);
   bool check() const;
};