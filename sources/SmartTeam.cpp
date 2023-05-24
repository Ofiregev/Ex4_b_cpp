#include "SmartTeam.hpp"
#include "vector"
#include <algorithm>
#include "typeinfo"

namespace ariel {
    SmartTeam::SmartTeam(Character *leader) : Team(leader){}

    // Add new warrior to the team
    void SmartTeam::add(Character *warrior)
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
        this->sortByType(); // Cowboys first, ninjas next
    }

    // Sort the warriors in the team by score in descending order
    void SmartTeam::sortByScore()
    {
        vector<Character *> warriors;

        // Separate warriors into a single vector
        for (Character *member : getMembers())
        {
            if (member != nullptr)
            {
                warriors.push_back(member);
            }
        }

        // Sort warriors by score in descending order
        sort(warriors.begin(), warriors.end(), [](Character *w1, Character *w2) {
            return w1->getScore() > w2->getScore();
        });

        // Assign the sorted warriors back to the team array
        size_t i = 0;
        for (Character *warrior : warriors)
        {
            getMembers()[i++] = warrior;
        }
    }

    // This function chooses the victim based on their score
    Character * SmartTeam::findVictim(Team *enemies)
    {
        double minimal_score = std::numeric_limits<double>::infinity();
        Character *victim = nullptr;
        for (Character *enemy : enemies->getMembers())
        {
            if (enemy && enemy->isAlive())
            {
                double score = enemy->getScore();
                if (score < minimal_score)
                {
                    minimal_score = score;
                    victim = enemy;
                }
            }
        }
        return victim;
    }

    // Kill the victim by attacking with team members
    void SmartTeam::killVictim(Team *enemies)
    {
        Character *victim = findVictim(enemies);

        for (Character *attacker : getMembers())
        {
            if (attacker && attacker->isAlive())
            {
                while (victim && !victim->isAlive())
                {
                    victim = findVictim(enemies);
                }

                if (!victim)
                {
                    break;
                }

                // Check if the attacker is a Cowboy
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
                // Check if the attacker is a Ninja
                else if (Ninja *ninja = dynamic_cast<Ninja *>(attacker))
                {
                    if (ninja->distance(victim) <= 1)
                    {
                        ninja->slash(victim);
                        cout << attacker->getName() << " slashed " << victim->getName() << " -40 points " << endl;
                    }
                    else
                    {
                        ninja->move(victim);
                        cout << attacker->getName() << " couldn't slash " << victim->getName() << " distance between them: " << std::to_string(ninja->distance(victim)) << endl;
                    }
                }
                else
                {
                    cout << "Member is neither Cowboy nor Ninja!" << endl;
                }
            }
        }
    }

    // Attack the enemy team
    void SmartTeam::attack(Team *enemies)
    {
        if (!enemies)
        {
            throw std::invalid_argument("null ptr");
        }

        if (enemies->stillAlive() == 0 || stillAlive() == 0)
        {
            throw std::runtime_error("all members dead");
        }

        cout << "team " << getTeamLeader()->getName() << " attacking team " << enemies->getTeamLeader()->getName() << endl;

        if (!getTeamLeader()->isAlive())
        {
            // Find the index of the old team leader
            size_t leader_index = SIZE_MAX;
            for (size_t i = 0; i < MAX_MEMBERS; i++)
            {
                if (getMembers()[i] == getTeamLeader())
                {
                    leader_index = i;
                    break;
                }
            }

            if (leader_index == SIZE_MAX)
            {
                // Error: old team leader not found in array
                throw std::runtime_error("Old team leader not found");
            }

            // Find the index of the closest living member to the old team leader
            Character *closest_member = findClosestLivingMember();
            size_t closest_index = SIZE_MAX;
            for (size_t i = 0; i < MAX_MEMBERS; i++)
            {
                if (getMembers()[i] == closest_member)
                {
                    closest_index = i;
                    break;
                }
            }

            if (closest_index == SIZE_MAX)
            {
                // Error: closest living member not found in array
                throw std::runtime_error("Closest living member not found");
            }

            // Set the new team leader pointer to be the closest living member pointer
            Character *team_leader = getTeamLeader();
            Character *temp = team_leader;
            team_leader = closest_member;
            team_leader->setTeam(this);
            getMembers()[leader_index] = temp;
        }

        killVictim(enemies);
    }
}
