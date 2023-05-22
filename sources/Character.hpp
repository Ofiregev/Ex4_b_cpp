#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include <string>
#include "Point.hpp"

namespace ariel
{
    class Team;
    class Character
    {
    private:
        Point location;
        int score;
        std::string name;
        Team *team = nullptr;

    public:
    //constructors & destructor
        Character(Point loc, int score, std::string name);
        Character(const Character &other);
        Character &operator=(const Character &other);
        virtual Character *createCopy() const = 0; // for copy constructor
        Character(Character &&other) noexcept;
        Character &operator=(Character &&other) noexcept;
        virtual ~Character();

        virtual const std::type_info &getType() const;
        virtual string print();

        void setTeam(Team *newTeam);
        
        bool isAlive();
        double distance(Character *player);
        void hit(int points);

        //getters & setters
        std::string getName();
        Point getLocation();
        Team *getTeam() const ;
        int getScore();
        void setLocation(Point loc);
        void setScore(int score);
        
    };
}

#endif
