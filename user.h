#pragma once

#include <vector>
#include "unit.h"

class User
{
public:
   User() = default;
   explicit User(const int level = 1) : m_level{ level } {}

   int level() const;
   void setLevel(const int level);
private:
   int m_level;
   std::vector<Unit> units;
};

int User::level() const
{
   return m_level;
}

void User::setLevel(const int level)
{
   m_level = level;
}