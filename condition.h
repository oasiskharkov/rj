#pragma once

#include <string>
#include "user.h"

class Condition
{
public:
   enum ConditionType { USER_LEVEL_GREATER, UNIT_LEVEL_EQUALS, UNIT_UPGRADE_STARTED };
public:
   Condition(bool no = false) : m_not{ no } {}
   
   virtual ~Condition() = default;
   
   virtual ConditionType getType() const = 0;

   virtual bool checkCondition(const User& user) = 0;
   
   static Condition* createCondition(ConditionType type);
   
   bool ifNot() const {
      return m_not;
   }

   void setNot(const bool no)
   {
      m_not = no;
   }
private:
   bool m_not;
};

class UserLevelGreater final : public Condition
{
public:
   UserLevelGreater() = default;
   
   UserLevelGreater(const int level) : m_level{ level }
   {
      if (m_level < 1)
      {
         throw std::logic_error("User level must have positive value.");
      }
   }

   ConditionType getType() const override {
      return USER_LEVEL_GREATER; 
   }

   bool checkCondition(const User& user) override;

   int level() const { 
      return m_level; 
   }
   
   void setLevel(const int level) {
      m_level = level; 
   }
private:
   

   int m_level;
};

class UnitLevelEquals final : public Condition
{
public:
   UnitLevelEquals() = default;
   
   UnitLevelEquals(const std::string& type, const int level) : m_type{ type }, m_level{ level }
   {
      if (level < 1)
      {
         throw std::logic_error("Unit level must have positive value.");
      }
   }
   
   ConditionType getType() const override { 
      return UNIT_LEVEL_EQUALS; 
   }
   
   bool checkCondition(const User& user) override;

   std::string type() const { 
      return m_type; 
   }
   
   void setType(const std::string& type) { 
      m_type = type; 
   }
   
   int level() const { 
      return m_level; 
   }
   
   void setLevel(const int level) { 
      m_level = level; 
   }
private:
   std::string m_type;
   int m_level;
};

class UnitUpgradeStarted final : public Condition
{
public:
   UnitUpgradeStarted() = default;
   
   UnitUpgradeStarted(const std::string& type) : m_type{ type } {}
   
   ConditionType getType() const override { 
      return UNIT_UPGRADE_STARTED; 
   }

   bool checkCondition(const User& user) override;
   
   std::string type() const { 
      return m_type; 
   }
   
   void setType(const std::string& type) { 
      m_type = type; 
   }
private:
   std::string m_type;
};