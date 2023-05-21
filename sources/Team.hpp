#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <string>
#include <array>
//#include "Character.hpp"
#include "Point.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"

using namespace std;

namespace ariel {
    constexpr int MAX_MEMBERS = 10;

    class Team {
    private:
        std::array<Character*, MAX_MEMBERS> members;
        Character* team_leader;

    public:
        Team(Character* leader);
        Team(const Team& other);
        Team& operator=(const Team& other);
        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;
        virtual ~Team();

        virtual void add(Character* warrior);
        std::array<Character*, MAX_MEMBERS>& getMembers();
        void sortByType();
        void attack(Team* enemies);
        size_t findClosestLivingMemberIndex();
        Character* getTeamLeader();
        Character* findClosestLivingMember();
        int didNotAttacked();
        void setAttackedParam();
        Character* findClosestVictim(Team* enemies);
        void killVictim(Team* enemies);
        bool isCowboy(Character* warrior);
        bool isNinja(Character* warrior);
        virtual int stillAlive();
        virtual void print();
    };
}

#endif
