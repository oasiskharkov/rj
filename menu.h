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
   static Menu* getInstance();
   void run();
   const User& getUser() const;
   bool check() const;
private:
   static Menu* instance;
   User user;
   std::queue<std::pair<bool, std::unique_ptr<Condition>>> conditions;


   Menu() = default;
   Menu(const Menu&) = delete;
   Menu& operator = (const Menu&) = delete;
   
   void xmlCheckResult(XMLError result);    
   void fillPlayerInfo(XMLDocument* doc);
   void fillConditions(XMLDocument* doc);
   void inputFileName(XMLDocument* doc, const std::string& invitation);

};

inline const User& Menu::getUser() const
{
   return user;
}