#ifndef SMARTTEAM_HPP
#define SMARTTEAM_HPP
#include <iostream>
#include <string>
#include "Team.hpp"
using namespace std;
     
namespace ariel {
    class SmartTeam : public Team {
        public:
            SmartTeam(Character* leader);
            void add(Character *warrior) override;
            void sortByScore() ;
            void attack(Team *enemies) override;
            void killVictim(Team *enemies) override;
            Character * findVictim(Team *enemies);
            


    };
}

    


#endif