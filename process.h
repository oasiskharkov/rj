#pragma once

#include <string>

class Process
{
public:
   Process() = default;

   Process(const std::string& type) : m_type{ type } {}

   std::string type() const {
      return m_type;
   }
   void setType(const std::string& type) {
      m_type = type;
   }
private:
   std::string m_type;
};