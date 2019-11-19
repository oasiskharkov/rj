#pragma once

#include <vector>
#include "unit.h"
#include "process.h"

class User
{
public:
   explicit User(const int level = 1) : m_level{ level } {}

   int level() const;
   void setLevel(const int level);

   const std::vector<Unit>& units() const;
   void setUnits(const std::vector<Unit>);

   const std::vector<Process>& processes() const;
   void setProcesses(const std::vector<Process>);
private:
   int m_level;
   std::vector<Unit> m_units;
   std::vector<Process> m_processes;
};

inline int User::level() const
{
   return m_level;
}

inline void User::setLevel(const int level)
{
   m_level = level;
}

inline const std::vector<Unit>& User::units() const
{
   return m_units;
}

inline void User::setUnits(const std::vector<Unit> units)
{
   m_units = units;
}

inline const std::vector<Process>& User::processes() const
{
   return m_processes;
}

inline void User::setProcesses(const std::vector<Process> processes)
{
   m_processes = processes;
}