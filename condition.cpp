#include "condition.h"

Condition * Condition::createCondition(ConditionType type)
{
   switch (type)
   {
   case USER_LEVEL_GREATER:
      return new UserLevelGreater;
   case UNIT_LEVEL_EQUALS:
      return new UnitLevelEquals;
   case UNIT_UPGRADE_STARTED:
      return new UnitUpgradeStarted;
   }
   return nullptr;
}