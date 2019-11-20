#pragma once

#include <vector>
#include "unit.h"
#include "process.h"

class User
{
public:
   explicit User(const int level = 1) : m_level{ level }
   {
      if (m_level < 1)
      {
         throw std::logic_error("User level must have positive value.");
      }
   }

   int level() const { 
      return m_level; 
   }

   void setLevel(const int level) {
      m_level = level;
   }

   const std::vector<Unit>& units() const {
      return m_units;
   }

   void setUnits(const std::vector<Unit> units) {
      m_units = units;
   }

   const std::vector<Process>& processes() const {
      return m_processes;
   }
 
   void setProcesses(const std::vector<Process> processes) {
      m_processes = processes;
   }
private:
   int m_level;
   std::vector<Unit> m_units;
   std::vector<Process> m_processes;
};