#pragma once

#include <iostream>
#include <filesystem>
#include <memory>
#include "tinyxml2.h"
#include "user.h"

using namespace tinyxml2;
using namespace std::experimental::filesystem;

class Menu
{
public:
   static Menu* getInstance();
   void run();
   const User& getUser() const;
private:
   static Menu* instance;
   User user;

   Menu() = default;
   Menu(const Menu&) = delete;
   Menu& operator = (const Menu&) = delete;
   
   void XMLCheckResult(XMLError result);    
   void FillPlayerInfo(XMLDocument* doc);
};

inline const User& Menu::getUser() const
{
   return user;
}