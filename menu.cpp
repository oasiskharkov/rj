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
      xmlCheckResult(eResult);
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

void Menu::addCondition(XMLNode* node, Condition::NodeType nodeType, bool isNot)
{
   XMLElement* elem;
   XMLError eResult;

   if ((elem = node->FirstChildElement("user_level_gt")) != nullptr)
   {
      int level;
      eResult = elem->QueryIntAttribute("level", &level);
      xmlCheckResult(eResult);
      auto ptr = Condition::createCondition(Condition::ConditionType::USER_LEVEL_GREATER);
      auto ulg = dynamic_cast<UserLevelGreater*>(ptr);
      if(ulg != nullptr)
      {
         ulg->setNot(isNot);
         ulg->setLevel(level);
      }
      conditions.push(std::make_pair(nodeType, std::unique_ptr<Condition>{ ulg }));
   }
   else if((elem = node->FirstChildElement("unit_level_eq")) != nullptr)
   {
      std::string type(elem->Attribute("type"));
      int level;
      eResult = elem->QueryIntAttribute("level", &level);
      xmlCheckResult(eResult);
      auto ptr = Condition::createCondition(Condition::ConditionType::UNIT_LEVEL_EQUALS);
      auto ule = dynamic_cast<UnitLevelEquals*>(ptr);
      if (ule != nullptr)
      {
         ule->setNot(isNot);
         ule->setType(type);
         ule->setLevel(level);
      }
      conditions.push(std::make_pair(nodeType, std::unique_ptr<Condition>{ ule }));
   }
   else if((elem = node->FirstChildElement("unit_upgrade_started")) != nullptr)
   {
      std::string type(elem->Attribute("type"));
      auto ptr = Condition::createCondition(Condition::ConditionType::UNIT_UPGRADE_STARTED);
      auto uus = dynamic_cast<UnitUpgradeStarted*>(ptr);
      if (uus != nullptr)
      {
         uus->setNot(isNot);
         uus->setType(type);
      }
      conditions.push(std::make_pair(nodeType, std::unique_ptr<Condition>{ uus }));
   }
}

void Menu::fillConditions(XMLDocument * doc)
{

}

bool Menu::check() const
{
   return false;
}