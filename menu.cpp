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
   std::unique_ptr<XMLDocument> playerStruct{ new XMLDocument };
   std::unique_ptr<XMLDocument> conditions{ new XMLDocument };
   
   inputFileName(playerStruct.get(), "Input XML file name with player structure: ");
   inputFileName(conditions.get(), "Input XML file name with conditions: ");

   fillPlayerInfo(playerStruct.get());
   fillConditions(conditions.get());
}

void Menu::inputFileName(XMLDocument* xmlDoc, const std::string& invitation)
{
   XMLError eResult;
   do
   {
      std::string fileName;
      std::cout << invitation;
      std::cin >> fileName;
      auto p = current_path();
      std::string resources_path = p.string() + "\\resources\\" + fileName;
      eResult = xmlDoc->LoadFile(resources_path.c_str());
      xmlCheckResult(eResult);
   } while (eResult != XML_SUCCESS);
}

void Menu::xmlCheckResult(XMLError result)
{
   if (result != XML_SUCCESS)
   {
      std::cout << "XML error code: " << result << std::endl;
   }
}

void Menu::fillPlayerInfo(XMLDocument* doc)
{
   XMLNode * xml_user = doc->FirstChild();
   int lvl;
   if (xml_user == nullptr) return;
   XMLError eResult = xml_user->ToElement()->QueryIntAttribute("level", &lvl);
   xmlCheckResult(eResult);

   XMLElement* xml_units = xml_user->FirstChildElement("units");
   if (xml_units == nullptr) return;
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
   if (xml_processes == nullptr) return;
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

void Menu::fillConditions(XMLDocument * doc)
{

}

bool Menu::check() const
{
   return false;
}