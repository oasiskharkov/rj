#pragma once

#include <string>

class Process
{
public:
   Process() = default;
   Process(const std::string& type) : m_type{ type } {}

   std::string type() const;
   void setType(const std::string& type);
private:
   std::string m_type;
};

inline std::string Process::type() const
{
   return m_type;
}

inline void Process::setType(const std::string& type)
{
   m_type = type;
}