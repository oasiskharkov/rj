#include "condition.h"

UserLevelGreater::UserLevelGreater(const int level, bool no) :
   Condition{ no },
   m_level{ level }
{
   if (m_level < 1)
   {
      throw std::logic_error("User level must have positive value.");
   }
}

bool UserLevelGreater::checkCondition(const User& user, std::vector<std::string>& errors)
{
   int userLevel = user.level();
   bool result = isNot() ? !(userLevel > m_level) : userLevel > m_level;
   
   std::string error = "User level " + std::to_string(userLevel) + " is not greater than " + std::to_string(m_level);
   if (!result)
   {
      errors.emplace_back(error);
   }
   
   return result;
}

UnitLevelEquals::UnitLevelEquals(const std::string& type, const int level, bool no) :
   Condition{ no },
   m_type{ type },
   m_level{ level }
{
   if (level < 1)
   {
      throw std::logic_error("Unit level must have positive value.");
   }
}

bool UnitLevelEquals::checkCondition(const User& user, std::vector<std::string>& errors)
{
   auto unit = std::find_if(std::begin(user.units()), std::end(user.units()),
      [this](const Unit& u){ return this->type() == u.type(); });
   if (unit == user.units().end())
   {
      throw std::logic_error("Can't find unit: " + m_type);
   }
   int unitLevel = unit->level();

   bool result = isNot() ? !(unitLevel == m_level) : unitLevel == m_level;
   
   std::string error = "Unit type " + unit->type() + " with level " + std::to_string(unit->level()) + " doesn't equal to " + std::to_string(m_level);
   if (!result)
   {
      errors.emplace_back(error);
   }

   return result;
}

UnitUpgradeStarted::UnitUpgradeStarted(const std::string& type, bool no) :
   Condition{ no },
   m_type{ type } 
{
}

bool UnitUpgradeStarted::checkCondition(const User& user, std::vector<std::string>& errors)
{
   auto process = std::find_if(std::begin(user.processes()), std::end(user.processes()),
      [this](const Process& p) { return this->type() == p.type(); });

   bool result = !(process == user.processes().end());
   std::string error = "Proccess for unit type " + m_type + " is not started";
   result = isNot() ? !result : result;

   if (!result)
   {
      errors.emplace_back(error);
   }

   return result;
}