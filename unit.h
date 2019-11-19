#pragma once

#include <string>

class Unit
{
public:
   Unit() = default;
   Unit(const std::string& type, const int level) : m_type{ type }, m_level{ level } {}

   std::string type() const;
   void setType(const std::string& type);
   int level() const;
   void setLevel(const int level);
private:
   std::string m_type;
   int m_level;
};

inline std::string Unit::type() const
{
   return m_type;
}

void Unit::setType(const std::string& type)
{
   m_type = type;
}

int Unit::level() const
{
   return m_level;
}

void Unit::setLevel(const int level)
{
   m_level = level;
}