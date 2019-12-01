#pragma once

#include <string>
#include <algorithm>
#include "user.h"

class Condition
{
public:
   Condition(bool no = false) : m_not{ no } {}
   virtual ~Condition() = default;
   
   virtual bool checkCondition(const User& user, std::vector<std::string>& errors) = 0;
   
   bool isNot() const {
      return m_not;
   }

   void setNot(const bool no) {
      m_not = no;
   }
private:
   bool m_not;
};

class UserLevelGreater final : public Condition
{
public:
   UserLevelGreater() = default;
   UserLevelGreater(const int level, bool no);
   
   bool checkCondition(const User& user, std::vector<std::string>& errors) override;
   
   int level() const {
      return m_level;
   }

   inline void setLevel(const int level) {
      m_level = level;
   }
private:
   int m_level;
};

class UnitLevelEquals final : public Condition
{
public:
   UnitLevelEquals() = default;
   UnitLevelEquals(const std::string& type, const int level, bool no);
   
   bool checkCondition(const User& user, std::vector<std::string>& errors) override;

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
   UnitUpgradeStarted(const std::string& type, bool no);
   
   bool checkCondition(const User& user, std::vector<std::string>& errors) override;
   
   std::string type() const { 
      return m_type; 
   }
   
   void setType(const std::string& type) { 
      m_type = type; 
   }
private:
   std::string m_type;
};