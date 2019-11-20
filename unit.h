#pragma once

#include <string>

class Unit
{
public:
   Unit() = default;

   Unit(const std::string& type, const int level) : m_type{ type }, m_level{ level }
   {
      if (m_level < 1)
      {
         throw std::logic_error("Unit level must have positive value");
      }
   }
   
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