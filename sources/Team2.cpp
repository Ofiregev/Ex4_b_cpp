#include "Team2.hpp"

namespace ariel {

    Team2::Team2(Character* leader) : Team(leader) {
    }
    

   void Team2::add(Character* warrior) {
     cout << "add func team2" << endl;
    if (warrior == nullptr) {
        return;
    }
    if (warrior->getTeam() != nullptr) {
        throw std::runtime_error("Warrior is already in a team");
    }
    warrior->setTeam(this);
    // Add character to next available slot
    size_t i = 0;
    while (i < MAX_MEMBERS && getMembers()[i] != nullptr) {
        i++;
    }
    if (i < MAX_MEMBERS) {
        getMembers()[i] = warrior;
    } else {
        throw std::runtime_error("Team is full. Cannot add more characters.");
    }
    cout << "adding to team2 " << warrior->print() << endl;
}

   
    //  void Team2::print()
    // {
    //     cout << "The team leader is " << team_leader->getName() << "." << endl;
    //     cout << "The members of the team are:" << endl;
    //     for (size_t i = 0; i < 10; i++)
    //     {
    //         if (members[i])
    //         {
    //             cout << members[i]->print() << endl;
    //         }
    //     }
    // }
    // const std::array<Character*, MAX_MEMBERS> Team2::getMembers() const 
    // {
    //     return members;
    // }
    // int Team2::stillAlive()
    // {
        
    //     int count = 0;
    //     for (size_t i = 0; i < 10; i++)
    //     {
    //         if (members[i] && members[i]->isAlive())
    //         {
    //             count++;
    //         }
    //     }
    //     return count;
    // }



}
