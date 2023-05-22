#include "Character.hpp"


namespace ariel
{
    Character::Character(Point loc, int score, string name) : location(loc), score(score), name(name) {}
    
    Character& Character::operator=(const Character &other) {
        if (this != &other) {
            location = other.location;
            score = other.score;
            name = other.name;
        }
        return *this;
    }
    void Character::setTeam(Team* newTeam) {
        team = newTeam;
    }

    Team* Character::getTeam() const {
        return team;
    }

    Character::Character(const Character& other) : location(other.location), score(other.score), name(other.name) {}

    Character::Character(Character &&other) noexcept : location(std::move(other.location)), score(std::move(other.score)), name(std::move(other.name)) {}

    Character& Character::operator=(Character &&other) noexcept {
        if (this != &other) {
            location = std::move(other.location);
            score = std::move(other.score);
            name = std::move(other.name);
        }
        return *this;
    }
    
    bool Character::isAlive()
    {
        return score > 0;
    }

 double Character::distance(Character *player) {
    Point p = player->getLocation();
    return location.distance(p);
}

    void Character::hit(int points)
    {
        if(points < 0)
        {
            throw std::invalid_argument("error");
        }
        score = score - points;
    }

    string Character::getName()
    {
        return name;
    }

    Point Character::getLocation()
    {
        return location;
    }
    void Character::setLocation(Point loc)
    {
        location = loc;
    }

    string Character::print()
    {
        if(!isAlive())
        {
            return "Name: (" + name + ")";
        }
        return "Name: " + name + ", Score: " + std::to_string(score) + ", Location: "+ location.print() ;
    }
    // bool Character::getAttackedParam()
    // {
    //     if(attacked == false)
    //     {
    //         return false;
    //     }else{
    //         return true;
    //     }
    // }
    // void Character::setAttackedParam(bool attacked)
    // {
    //     this->attacked = attacked;
    // }
  

    int Character::getScore()
    {
        return score;
    }
    void Character::setScore(int s)
    {
        this->score = s;   
     }
    const std::type_info& Character::getType() const {
        return typeid(Character);
    }
    // void Character::gotAttacked()
    // {
    //     attacked = true;
    // }

     Character::~Character() = default;

    //Character::Character(const Character&) = default;

    //Character& Character::operator=(const Character&) = default;

    //Character::Character(Character&&) noexcept = default;

    //Character& Character::operator=(Character&&) noexcept = default;


} // namespace ariel

