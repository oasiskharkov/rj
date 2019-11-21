#pragma once

#include <iostream>
#include <filesystem>
#include <memory>
#include <queue>
#include "tinyxml2.h"
#include "user.h"
#include "condition.h"

using namespace tinyxml2;
using namespace std::experimental::filesystem;

class Menu
{
public:
   enum NodeType { AND, OR };
public:
   static Menu* getInstance();
   void run();
   const User& getUser() const;
   bool check() const;
private:
   static Menu* instance;
   User user;
   std::vector<std::unique_ptr<Condition>> conditions;
   NodeType type;
   
   Menu() = default;
   Menu(const Menu&) = delete;
   Menu& operator = (const Menu&) = delete;
      
   void xmlCheckResult(XMLError result);    
   void fillPlayerInfo(XMLDocument* doc);
   void fillConditions(XMLDocument* doc);
   void inputFileName(XMLDocument* doc, const std::string& invitation);
   void addCondition(XMLNode* node, bool isNot = false);
};

inline const User& Menu::getUser() const
{
   return user;
}