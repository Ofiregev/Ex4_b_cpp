#include "Team.hpp"
#include "vector"
#include <algorithm>
#include "typeinfo"
namespace ariel
{

    // Constructor
//    Team::Team(Character* leader) : team_leader(leader) {
//     if (leader == nullptr) {
//         throw std::invalid_argument("Leader cannot be null");
//     }
//     if (leader->getTeam() != nullptr) {
//         throw std::runtime_error("Leader is already in a team");
//     }
//     leader->setTeam(this);
//     members.fill(nullptr);
//     add(leader); // Add the team leader as the first member of the team
// }
Team::Team(Character* leader) : team_leader(nullptr) {
    if (leader == nullptr) {
        throw std::invalid_argument("Leader cannot be null");
    }
    // if (leader->getTeam() != nullptr) {
    //     throw std::runtime_error("Leader is already in a team");
    // }
    team_leader = leader;
    //leader->setTeam(this);
    members.fill(nullptr);
    add(leader); // Add the team leader as the first member of the team
    cout << "finishd constructor" << endl;
    cout << "team1: " << this << endl;
}




    // Copy constructor
    Team::Team(const Team &other) : team_leader(other.team_leader)
    {
        for (size_t i = 0; i < members.size(); i++)
        {
            if (other.members[i] != nullptr)
            {
                members[i] = other.members[i]->createCopy();
            }
        }
    }

    // Copy assignment operator
    Team &Team::operator=(const Team &other)
    {
        if (this != &other)
        {
            // Delete current members
            for (size_t i = 0; i < members.size(); i++)
            {
                if (members[i] != nullptr)
                {
                    delete members[i];
                    members[i] = nullptr;
                }
            }

            // Copy other team leader
            team_leader = other.team_leader;

            // Copy other team members
            for (size_t i = 0; i < members.size(); i++)
            {
                if (other.members[i] != nullptr)
                {
                    members[i] = other.members[i]->createCopy();
                }
            }
        }
        return *this;
    }

    // Move constructor
    Team::Team(Team &&other) noexcept : team_leader(other.team_leader)
    {
        members = std::move(other.members);
        other.members.fill(nullptr);
    }

    // Move assignment operator
    Team &Team::operator=(Team &&other) noexcept
    {
        if (this != &other)
        {
            // Delete current members
            for (size_t i = 0; i < members.size(); i++)
            {
                if (members[i] != nullptr)
                {
                    delete members[i];
                    members[i] = nullptr;
                }
            }

            // Move other team members
            members = std::move(other.members);
            other.members.fill(nullptr);

            // Move other team leader
            team_leader = std::move(other.team_leader);
        }
        return *this;
    }

    Character *Team::getTeamLeader()
    {
        return team_leader;
    }

     std::array<Character*, MAX_MEMBERS> &Team::getMembers() 
    {
        return members;
    }

    void Team::add(Character *warrior)
{
    if (warrior == nullptr)
    {
        return;
    }
    if (warrior->getTeam() != nullptr)
    {
             cout << "team1: " << this << endl;

        throw std::runtime_error("Warrior is already in a team");
    }
    warrior->setTeam(this);
    // Add character to next available slot
    size_t i = 0;
    while (i < MAX_MEMBERS && members[i] != nullptr)
    {
        i++;
    }
    if (i < MAX_MEMBERS)
    {
        members[i] = warrior;
    }
    else
    {
        throw std::runtime_error("Team is full. Cannot add more characters.");
    }
    this->sortByType();
}


    void Team::sortByType()
{
    //cout << "sort func" << endl;
    vector<Cowboy*> cowboys;
    vector<Ninja*> ninjas;

    // Separate cowboys and ninjas into different vectors
    for (Character* member : members)
    {
        if (member == nullptr)
        {
            continue;
        }
        if (isCowboy(member))
        {
            cowboys.push_back(static_cast<Cowboy*>(member));
        }
        else if (isNinja(member))
        {
            ninjas.push_back(static_cast<Ninja*>(member));
        }
    }

    // Sort cowboys by score in descending order
    sort(cowboys.begin(), cowboys.end(), [](Cowboy* c1, Cowboy* c2) {
        return c1->getScore() > c2->getScore();
    });

    // Sort ninjas by speed in ascending order
    sort(ninjas.begin(), ninjas.end(), [](Ninja* n1, Ninja* n2) {
        return n1->getSpeed() < n2->getSpeed();
    });

    // Combine the sorted vectors back into the team array
    size_t i = 0;
    for (Cowboy* cowboy : cowboys)
    {
        members[i++] = cowboy;
    }
    for (Ninja* ninja : ninjas)
    {
        members[i++] = ninja;
    }
}


    bool Team::isCowboy(Character *warrior)
    {
        return dynamic_cast<Cowboy *>(warrior) != nullptr;
    }

    bool Team::isNinja(Character *warrior)
    {
        return dynamic_cast<Ninja *>(warrior) != nullptr;
    }

    Character *Team::findClosestVictim(Team *enemies)
    {
        cout << "closet victim function" << endl;
        double minimal_dist = 100000;
        Character *victim = nullptr;
        for (size_t i = 0; i < MAX_MEMBERS; i++)
        {
            if (enemies->members[i] && enemies->members[i]->isAlive()&& (!enemies->members[i]->getAttackedParam()))
            {
                double dist = enemies->members[i]->distance(team_leader);

                if (dist < minimal_dist)
                {
                    minimal_dist = dist;
                    victim = enemies->members[i];
                    cout << "victim is :" << endl;
                    victim->print();
                }
            }
        }
        cout << "chose victim :";
        victim->print();
        return victim;
    }

    void Team::killVictim(Team *enemies)
    {
        Character *victim = findClosestVictim(enemies);
        cout << "victim before attack:";
        victim->print();
        for (size_t i = 0; i < MAX_MEMBERS; i++)
        {
            if (members[i] && members[i]->isAlive())
            {
                if (Cowboy *cowboy = dynamic_cast<Cowboy *>(members[i]))
                {
                    if (cowboy->hasboolets())
                    {
                        cowboy->shoot(victim);
                    }
                    else
                    {
                        cowboy->reload();
                    }
                }
                else if (Ninja *ninja = dynamic_cast<Ninja *>(members[i]))
                {
                    if (ninja->distance(victim) <= 1 && victim->isAlive())
                    {
                        ninja->slash(victim);
                    }
                    else
                    {
                        ninja->move(victim);
                    }
                }
                else
                {
                    cout << "Member is neither Cowboy nor Ninja!" << endl;
                }
            }
        }
        cout << "victim after attack:";
        victim->print();
        
        
        // if (!victim->isAlive())
        // {
        //     //cout << "victim dead, got attackes ?:";
        //     victim->setAttackedParam(true);
        //     //cout <<victim->getAttackedParam() << endl;
        // }
        // else
        // {
        //     //cout << "victim didnt dead, attacked ?:";
        //     victim->setAttackedParam(true);
        //     //cout << victim->getAttackedParam() << endl;
        // }
    }
    void Team::attack(Team *enemies)
    {
        if(!enemies)
        {
            throw std::invalid_argument("null ptr");
        }
        if (enemies->stillAlive() == 0)
        {
            return;
        }
        //cout << "started the attack funtion: "<< endl;
        // && enemies->didNotAttacked() > 0
        // while (stillAlive() > 0 && enemies->stillAlive() > 0)
        // {
            if(stillAlive() > 0 && enemies->stillAlive() > 0 && enemies->didNotAttacked() > 0){
            // cout << "didnt attacked enemies:";
            // cout << enemies->didNotAttacked() << endl;
            if (!team_leader->isAlive())
            {
                // Find the index of the old team leader
                size_t leader_index = 0;
                for (size_t i = 0; i < MAX_MEMBERS; i++)
                {
                    if (members[i] == team_leader)
                    {
                        leader_index = i;
                        break;
                    }
                }
                if (leader_index == SIZE_MAX)
                {
                    // Error: old team leader not found in array
                    throw("exception");
                }
                // Find the index of the closest living member to the old team leader
                Character *closest_member = findClosestLivingMember();
                size_t closest_index = 11;
                for (size_t i = 0; i < MAX_MEMBERS; i++)
                {
                    if (members[i] == closest_member)
                    {
                        closest_index = i;
                        break;
                    }
                }
                if (closest_index == SIZE_MAX)
                {
                    // Error: closest living member not found in array
                    throw("exception");
                }

                // Set the new team leader pointer to be the closest living member pointer

                Character *temp = team_leader;
                team_leader = closest_member;
                team_leader->setTeam(this);
                members[leader_index] = temp;
            }
            killVictim(enemies);
            cout << "team status: " << endl;
            enemies->print();
            cout << "finished " << endl;
        }
        enemies->setAttackedParam();
    }

    Character *Team::findClosestLivingMember()
    {
        double minimal_dist = 100000;
        Character *closest_member = nullptr;
        bool found_living_member = false;
        for (size_t i = 0; i < MAX_MEMBERS; i++)
        {
            if (members[i] && members[i]->isAlive())
            {
                double distance_to_leader = members[i]->distance(team_leader);
                if (distance_to_leader < minimal_dist)
                {
                    minimal_dist = distance_to_leader;
                    closest_member = members[i];
                }
                found_living_member = true;
            }
        }
        if (!found_living_member)
        {
            return nullptr;
        }
        return closest_member;
    }

    int Team::stillAlive()
    {
        
        int count = 0;
        for (size_t i = 0; i < 10; i++)
        {
            if (members[i] && members[i]->isAlive())
            {
                count++;
            }
        }
        return count;
    }

    int Team::didNotAttacked()
    {
        int count = 0;
        for (size_t i = 0; i < 10; i++)
        {
            if (members[i] && members[i] ->isAlive()&& !(members[i]->getAttackedParam()))
            {
                count++;
            }
        }
        return count;
    }
    void Team::setAttackedParam()
    {
        for (size_t i = 0; i < 10; i++)
        {
            if (members[i])
            {
                members[i]->setAttackedParam(false);
            }
        }
    }

    void Team::print()
    {
        cout << "The team leader is " << team_leader->getName() << "." << endl;
        cout << "The members of the team are:" << endl;
        for (size_t i = 0; i < 10; i++)
        {
            if (members[i])
            {
                cout << members[i]->print() << endl;
            }
        }
    }

    Team::~Team()
    {
        for (size_t i = 0; i < 10; i++)
        {
            if (members[i])
            {
                delete members[i];
            }
        }
    }
}
