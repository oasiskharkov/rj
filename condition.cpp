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

bool UserLevelGreater::checkCondition(const User& user)
{
   int userLevel = user.level();
   return isNot() ? !(userLevel > m_level) : userLevel > m_level;
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

bool UnitLevelEquals::checkCondition(const User& user)
{
   auto unit = std::find_if(std::begin(user.units()), std::end(user.units()),
      [this](const Unit& u){ return this->type() == u.type(); });
   if (unit == user.units().end())
   {
      throw std::logic_error("Can't find unit: " + m_type);
   }
   int unitLevel = unit->level();

   return isNot() ? !(unitLevel == m_level) : unitLevel == m_level;
}

UnitUpgradeStarted::UnitUpgradeStarted(const std::string& type, bool no) :
   Condition{ no },
   m_type{ type } 
{
}

bool UnitUpgradeStarted::checkCondition(const User& user)
{
   auto process = std::find_if(std::begin(user.processes()), std::end(user.processes()),
      [this](const Process& p) { return this->type() == p.type(); });

   bool result = process == user.processes().end() ? false : true;
   return isNot() ? !result : result;
}