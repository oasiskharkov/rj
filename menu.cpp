#include "menu.h"

Menu* Menu::instance = nullptr;

Menu * Menu::getInstance()
{
   if (instance == nullptr)
   {
      instance = new Menu;
   }
   return instance;
}

void Menu::run()
{
   std::unique_ptr<XMLDocument> xmlDoc{ new XMLDocument };
   XMLError eResult;
   do
   {
      std::string fileName;
      std::cout << "Input xml file name: ";
      std::cin >> fileName;
      auto p = current_path();
      std::string resources_path = p.string() + "\\resources\\" + fileName;
      eResult = xmlDoc->LoadFile(resources_path.c_str());
      XMLCheckResult(eResult);
   } while (eResult != XML_SUCCESS);

   FillPlayerInfo(xmlDoc.get());
}

void Menu::XMLCheckResult(XMLError result)
{
   if (result != XML_SUCCESS)
   {
      std::cout << "XML error code: " << result << std::endl;
   }
}

void Menu::FillPlayerInfo(XMLDocument* doc)
{
   XMLNode * xml_user = doc->FirstChild();
   int lvl;
   XMLError eResult = xml_user->ToElement()->QueryIntAttribute("level", &lvl);
   XMLCheckResult(eResult);

   XMLElement* xml_units = xml_user->FirstChildElement("units");
   XMLElement* xml_unit = xml_units->FirstChildElement("unit");

   std::vector<Unit> units;

   while(xml_unit != nullptr)
   {
      std::string type(xml_unit->Attribute("type"));
      int level;
      eResult = xml_unit->QueryIntAttribute("level", &level);
      xml_unit = xml_unit->NextSiblingElement();
           
      units.emplace_back(Unit{ type, level });
   }

   XMLElement* xml_processes = xml_user->FirstChildElement("processes");
   XMLElement* xml_upgrade_unit = xml_processes->FirstChildElement("upgrade_unit");

   std::vector<Process> processes;

   while (xml_upgrade_unit != nullptr)
   {
      std::string type(xml_upgrade_unit->Attribute("type"));
      xml_upgrade_unit = xml_upgrade_unit->NextSiblingElement();

      processes.emplace_back(Process{ type });
   }

   user.setLevel(lvl);
   user.setUnits(units);
   user.setProcesses(processes);
}