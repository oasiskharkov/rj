#include "menu.h"

int main()
{
   try
   {
      std::unique_ptr<Menu> menu(Menu::getInstance());
      menu->run();
      
      if (menu->check())
      {
         std::cout << "SUCCESS" << std::endl;
      }
      else
      {
         std::cout << "FAILURE" << std::endl;
      }
   }
   catch (std::exception& ex)
   {
      std::cout << ex.what() << std::endl;
   }
   catch (...)
   {
      std::cout << "Something goes wrong!" << std::endl;
   }
   
   return 0;
}