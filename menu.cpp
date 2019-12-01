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
      if (!xmlCheckResult(eResult))
      {
         std::cout << "Fail to load: " << fileName << "\nTry again" << std::endl;
      }
   } while (eResult != XML_SUCCESS);
}

bool Menu::xmlCheckResult(XMLError result)
{
   if (result != XML_SUCCESS)
   {
      std::cout << "XML error code: " << result << std::endl;
      return false;
   }
   return true;
}

void Menu::fillPlayerInfo(XMLDocument* doc)
{
   if (doc == nullptr)
   {
      throw std::exception("Unccorect XML document for player structure");
   }
   XMLNode * xml_user = doc->FirstChild();
   int lvl;
   if (xml_user == nullptr)
   {
      throw std::exception("Unccorect XML node");
   }
   XMLError eResult = xml_user->ToElement()->QueryIntAttribute("level", &lvl);
   if (!xmlCheckResult(eResult))
   {
      throw std::logic_error("Fail to read user level");
   }

   XMLElement* xml_units = xml_user->FirstChildElement("units");
   if (xml_units == nullptr)
   {
      throw std::exception("Unccorect XML element");
   }
   XMLElement* xml_unit = xml_units->FirstChildElement("unit");

   std::vector<Unit> units;

   while(xml_unit != nullptr)
   {
      std::string type(xml_unit->Attribute("type"));
      int level;
      eResult = xml_unit->QueryIntAttribute("level", &level);
      if (!xmlCheckResult(eResult))
      {
         throw std::logic_error("Fail to read unit level");
      }
      xml_unit = xml_unit->NextSiblingElement();
           
      units.emplace_back(Unit{ type, level });
   }

   XMLElement* xml_processes = xml_user->FirstChildElement("processes");
   if (xml_processes == nullptr)
   {
      throw std::exception("Unccorect XML element");
   }
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

void Menu::addCondition(XMLNode* node, bool isNot)
{
   XMLElement* elem = node->ToElement();
   if (elem == nullptr)
   {
      throw std::exception("Uncorrect XML element");
   }
   XMLError eResult;

   if (std::string(elem->Value()) == "user_level_gt")
   {
      int level;
      eResult = elem->QueryIntAttribute("level", &level);
      if (!xmlCheckResult(eResult))
      {
         throw std::logic_error("Fail to read user level");
      }
      auto ulg = new UserLevelGreater{level, isNot};
      conditions.emplace_back(std::unique_ptr<Condition>{ ulg });   
   }
   else if(std::string(elem->Value()) == "unit_level_eq")
   {
      std::string type(elem->Attribute("type"));
      int level;
      eResult = elem->QueryIntAttribute("level", &level);
      if (!xmlCheckResult(eResult))
      {
         throw std::logic_error("Fail to read unit level");
      }
      auto ule = new UnitLevelEquals{ type, level, isNot };
      conditions.emplace_back(std::unique_ptr<Condition>{ ule });

   }
   else if(std::string(elem->Value()) == "unit_upgrade_started")
   {
      std::string type(elem->Attribute("type"));
      auto uus = new UnitUpgradeStarted{ type, isNot }; 
      conditions.emplace_back(std::unique_ptr<Condition>{ uus });
   }
   else if (std::string(elem->Value()) == "not")
   {
      addCondition(elem->FirstChild(), true);
   }
   else
   {
      throw std::exception("Unknown condition");
   }
}

void Menu::fillConditions(XMLDocument * doc)
{
   if (doc == nullptr) 
   {
      throw std::exception("Uncorrect XML document for conditions");
   }

   auto conditions = doc->FirstChild();
   if (conditions == nullptr)
   {
      throw std::exception("There are no conditions");
   }
   std::string root = conditions->Value();
   if(root == "and" || root == "or")
   {
      type = root == "and" ? NodeType::AND : NodeType::OR;
      auto condition = conditions->FirstChild();
      while (condition != nullptr)
      {
         addCondition(condition);
         condition = condition->NextSibling();
      }
   }
   else
   {
      throw std::exception("Uncorrect root element for XML file with conditions");
   }
}

bool Menu::check() const
{
   bool result = false;
   std::vector<std::string> errors;
   
   if (!conditions.empty())
   {
      result = conditions[0].get()->checkCondition(user, errors);
   }

   for (size_t i = 1; i < conditions.size(); ++i)
   {
      if ((!result && type == NodeType::AND) || (result && type == NodeType::OR))
      {
         break;
      }

      bool newResult = conditions[i].get()->checkCondition(user, errors);
      type == NodeType::AND ? result = result && newResult : result = result || newResult;
   }

   if (!result)
   {
      for (const auto& error : errors)
      {
         std::cout << error << std::endl;
      }
   }

   return result;
}