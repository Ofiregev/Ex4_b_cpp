#include "Team.hpp"
#include "vector"
#include <algorithm>
#include "typeinfo"
namespace ariel
{

    // Constructor
Team::Team(Character* leader) : team_leader(nullptr) {
    if (leader == nullptr) {
        throw std::invalid_argument("Leader cannot be null");
    }
    team_leader = leader;
    members.fill(nullptr);
    add(leader); // Add the team leader as the first member of the team
    // cout << "finishd constructor" << endl;
    // cout << "team1: " << this << endl;
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
            // cout << "team1: " << this << endl;

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
    //cout << "adding to team " << warrior->print() << endl;

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
// Character* Team::findClosestVictim(Team* enemies)
// {
//     double minimal_dist = std::numeric_limits<double>::infinity();
//     Character* victim = nullptr;
//     for (Character* enemy : enemies->members)
//     {
//         if (enemy && enemy->isAlive())
//         {
//             double dist = enemy->distance(team_leader);
//             if (dist < minimal_dist)
//             {
//                 minimal_dist = dist;
//                 victim = enemy;
//             }
//         }
//     }
//     return victim;
// }


// Character* Team::findClosestLivingMember()
// {
//     double minimal_dist = std::numeric_limits<double>::infinity();
//     Character* closest_member = nullptr;

//     for (Character* member : members)
//     {
//         if (member && member->isAlive())
//         {
//             double distance_to_leader = member->distance(team_leader);
//             if (distance_to_leader < minimal_dist)
//             {
//                 minimal_dist = distance_to_leader;
//                 closest_member = member;
//             }
//         }
//     }

//     return closest_member;
// }
//     void Team::killVictim(Team *enemies)
// {
//     Character *victim = findClosestVictim(enemies);
//     cout << "victim before attack: " << victim->print() << endl;

//     for (Character* attacker : members)
//     {
//         if (attacker && attacker->isAlive())
//         {
//             while (victim && !victim->isAlive())
//             {
//                 victim = findClosestVictim(enemies);
//             }

//             if (!victim)
//             {
//                 cout << "No living victim found!" << endl;
//                 break;
//             }
//             cout << "the attacker is: " << attacker->print() << endl;
//             if (Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker))
//             {
//                 if (cowboy->hasboolets())
//                 {
//                     cowboy->shoot(victim);
//                 }
//                 else
//                 {
//                     cowboy->reload();
//                 }
//             }
//             else if (Ninja *ninja = dynamic_cast<Ninja *>(attacker))
//             {
//                 if (ninja->distance(victim) <= 1 && victim->isAlive())
//                 {
//                     ninja->slash(victim);
//                 }
//                 else
//                 {
//                     ninja->move(victim);
//                 }
//             }
//             else
//             {
//                 cout << "Member is neither Cowboy nor Ninja!" << endl;
//             }
//             cout << "victim after attack: " << victim->print() << endl;
//         }
//     }
// }

// void Team::attack(Team* enemies)
// {
//     if (!enemies)
//     {
//         throw std::invalid_argument("null ptr");
//     }

//     if (enemies->stillAlive() == 0 || stillAlive() == 0)
//     {
//         return;
//     }

//     if (!team_leader->isAlive())
//     {
//         // Find the index of the old team leader
//         size_t leader_index = SIZE_MAX;
//         for (size_t i = 0; i < MAX_MEMBERS; i++)
//         {
//             if (members[i] == team_leader)
//             {
//                 leader_index = i;
//                 break;
//             }
//         }

//         if (leader_index == SIZE_MAX)
//         {
//             // Error: old team leader not found in array
//             throw std::runtime_error("Old team leader not found");
//         }

//         // Find the index of the closest living member to the old team leader
//         Character* closest_member = findClosestLivingMember();
//         size_t closest_index = SIZE_MAX;
//         for (size_t i = 0; i < MAX_MEMBERS; i++)
//         {
//             if (members[i] == closest_member)
//             {
//                 closest_index = i;
//                 break;
//             }
//         }

//         if (closest_index == SIZE_MAX)
//         {
//             // Error: closest living member not found in array
//             throw std::runtime_error("Closest living member not found");
//         }

//         // Set the new team leader pointer to be the closest living member pointer
//         Character* temp = team_leader;
//         team_leader = closest_member;
//         team_leader->setTeam(this);
//         members[leader_index] = temp;
//     }

//     killVictim(enemies);
// }

Character* Team::findClosestVictim(Team* enemies) {
    double minimal_dist = std::numeric_limits<double>::infinity();
    Character* victim = nullptr;
    for (Character* enemy : enemies->members) {
        if (enemy && enemy->isAlive()) {
            double dist = enemy->distance(team_leader);
            if (dist < minimal_dist) {
                minimal_dist = dist;
                victim = enemy;
            }
        }
    }
    return victim;
}

Character* Team::findClosestLivingMember() {
    double minimal_dist = std::numeric_limits<double>::infinity();
    Character* closest_member = nullptr;

    for (Character* member : members) {
        if (member && member->isAlive() && member!=team_leader) {
            double distance_to_leader = member->distance(team_leader);
            if (distance_to_leader < minimal_dist) {
                minimal_dist = distance_to_leader;
                closest_member = member;
            }
        }
    }

    return closest_member;
}

    void Team::killVictim(Team *enemies)
{
    Character *victim = findClosestVictim(enemies);
    
    cout << "victim before attack: " << victim->print() << endl;

    for (Character* attacker : members)
    {
        if (attacker && attacker->isAlive())
        {
            while (victim && !victim->isAlive())
            {
                victim = findClosestVictim(enemies);
            }

            if (!victim)
            {
                cout << "No living victim found!" << endl;
                // throw std::runtime_error("No living victim found!");
                break;
            }
            //cout << "the attacker is: " << attacker->print() << endl;
            if (Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker))
            {
                if (cowboy->hasboolets())
                {
                    cowboy->shoot(victim);
                    cout << attacker->getName() << " shoot " << victim->getName() << " -10 points " << endl;
                }
                else
                {
                    cowboy->reload();
                }
            }
            else if (Ninja *ninja = dynamic_cast<Ninja *>(attacker))
            {
                if (ninja->distance(victim) <= 1)
                {
                    ninja->slash(victim);
                    cout << attacker->getName() << " slashed " << victim->getName() << " -40 points " << endl;
                }
                else
                {
                    //cout << "ninja location1: " << ninja->getLocation().print() << endl;
                    ninja->move(victim);
                    cout << attacker->getName() << " couldn't slash " << victim->getName() << " distance between them: " << std::to_string(ninja->distance(victim)) << endl;
                    // cout << "victim is: " << victim->print() << endl;

                    // cout << "ninja location2: " << ninja->getLocation().print() << endl;
                }
            }
            else
            {
                cout << "Member is neither Cowboy nor Ninja!" << endl;
            }
            //cout << "victim after attack: " << victim->print() << endl;
        }
    }
}

void Team::attack(Team* enemies) {
    if (!enemies) {
        throw std::invalid_argument("null ptr");
    }

    if (enemies->stillAlive() == 0 || stillAlive() == 0) {
            throw std::runtime_error("all members dead"); 
    }
    cout << "team " << team_leader->getName() << " attacking team " << enemies->team_leader->getName() << endl;
    if (!team_leader->isAlive()) {
        // Find the index of the old team leader
        size_t leader_index = SIZE_MAX;
        for (size_t i = 0; i < MAX_MEMBERS; i++) {
            if (members[i] == team_leader) {
                leader_index = i;
                break;
            }
        }

        if (leader_index == SIZE_MAX) {
            // Error: old team leader not found in array
            throw std::runtime_error("Old team leader not found");
        }

        // Find the index of the closest living member to the old team leader
        Character* closest_member = findClosestLivingMember();
        size_t closest_index = SIZE_MAX;
        for (size_t i = 0; i < MAX_MEMBERS; i++) {
            if (members[i] == closest_member) {
                closest_index = i;
                break;
            }
        }

        if (closest_index == SIZE_MAX) {
            // Error: closest living member not found in array
            throw std::runtime_error("Closest living member not found");
        }

        // Set the new team leader pointer to be the closest living member pointer
        Character* temp = team_leader;
        team_leader = closest_member;
        team_leader->setTeam(this);
        members[leader_index] = temp;
    }

    killVictim(enemies);
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

    // int Team::didNotAttacked()
    // {
    //     int count = 0;
    //     for (size_t i = 0; i < 10; i++)
    //     {
    //         if (members[i] && members[i] ->isAlive())
    //         {
    //             count++;
    //         }
    //     }
    //     return count;
    // }
    // void Team::setAttackedParam()
    // {
    //     for (size_t i = 0; i < 10; i++)
    //     {
    //         if (members[i])
    //         {
    //             members[i]->setAttackedParam(false);
    //         }
    //     }
    // }

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
