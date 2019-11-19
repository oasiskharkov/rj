#include "menu.h"

int main()
{
   Menu* menu = Menu::getInstance();
   menu->run();
   const User user = menu->getUser();

   delete menu;
   return 0;
}