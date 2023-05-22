#include "Team2.hpp"

namespace ariel
{

    Team2::Team2(Character *leader) : Team(leader){}

    void Team2::add(Character *warrior)
    {
        if (warrior == nullptr)
        {
            return;
        }
        if (warrior->getTeam() != nullptr)
        {
            throw std::runtime_error("Warrior is already in a team");
        }
        warrior->setTeam(this);
        // Add character to next available slot
        size_t i = 0;
        while (i < MAX_MEMBERS && getMembers()[i] != nullptr)
        {
            i++;
        }
        if (i < MAX_MEMBERS)
        {
            getMembers()[i] = warrior;
        }
        else
        {
            throw std::runtime_error("Team is full. Cannot add more characters.");
        }
    }

}
