#include "menu.h"

int main()
{
   try
   {
      char key;
      do
      {
         std::unique_ptr<Menu> menu{ new Menu };
         menu->run();

         std::cout << "\nDo you want to try again? Press any key to continue or 'n' to exit." << std::endl;
         key = _getch();
      } while (key != 'n');
   }
   catch (std::exception& ex)
   {
      std::cout << ex.what() << std::endl;
   }
   catch (...)
   {
      std::cout << "Something goes wrong!" << std::endl;
   }
   
   system("pause");
   return 0;
}