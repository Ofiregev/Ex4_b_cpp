#include "Character.hpp"

namespace ariel {

    // Constructor: Initializes the character with the given location, score, and name.
    Character::Character(Point loc, int score, string name) : location(loc), score(score), name(name) {}

    // Copy assignment operator: Assigns the values from another character to this character.
    Character& Character::operator=(const Character &other) {
        if (this != &other) {
            location = other.location;
            score = other.score;
            name = other.name;
        }
        return *this;
    }

    // Sets the team for the character.
    void Character::setTeam(Team* newTeam) {
        team = newTeam;
    }

    // Gets the team of the character.
    Team* Character::getTeam() const {
        return team;
    }

    // Copy constructor: Creates a copy of another character.
    Character::Character(const Character& other) : location(other.location), score(other.score), name(other.name) {}

    // Move constructor: Moves the resources from another character to this character.
    Character::Character(Character &&other) noexcept : location(std::move(other.location)), score(std::move(other.score)), name(std::move(other.name)) {}

    // Move assignment operator: Moves the resources from another character to this character.
    Character& Character::operator=(Character &&other) noexcept {
        if (this != &other) {
            location = std::move(other.location);
            score = std::move(other.score);
            name = std::move(other.name);
        }
        return *this;
    }

    // Checks if the character is alive based on its score.
    bool Character::isAlive() {
        return score > 0;
    }

    // Calculates the distance between this character and another player.
    double Character::distance(Character *player) {
        Point p = player->getLocation();
        return location.distance(p);
    }

    // Reduces the character's score by the given number of points.
    void Character::hit(int points) {
        if (points < 0) {
            throw std::invalid_argument("error");
        }
        score = score - points;
    }

    // Gets the name of the character.
    string Character::getName() {
        return name;
    }

    // Gets the location of the character.
    Point Character::getLocation() {
        return location;
    }

    // Sets the location of the character to the given location.
    void Character::setLocation(Point loc) {
        location = loc;
    }

    // Prints the character's information as a string.
    string Character::print() {
        if (!isAlive()) {
            return "Name: (" + name + ")";
        }
        return "Name: " + name + ", Score: " + std::to_string(score) + ", Location: " + location.print();
    }

    // Gets the score of the character.
    int Character::getScore() {
        return score;
    }

    // Sets the score of the character to the given score.
    void Character::setScore(int s) {
        this->score = s;
    }

    // Gets the type information of the character.
    const std::type_info& Character::getType() const {
        return typeid(Character);
    }

    // Destructor: Frees any resources associated with the character.
    Character::~Character() = default;

} 
