#include "Cowboy.hpp"

namespace ariel {

    // Constructor for the Cowboy class.
    Cowboy::Cowboy(string name, Point location) : Character(location, 110, name), num_of_bullets(6) {}

    // Setter for the number of bullets.
    void Cowboy::setBullets(int bul) {
        if (!isAlive()) {
            throw("the cowboy is dead");
        }
        num_of_bullets = bul;
    }

    // Getter for the number of bullets.
    int Cowboy::getNumOfBullets() {
        if (!isAlive()) {
            throw("the cowboy is dead");
        }
        return num_of_bullets;
    }
   

    // Method to shoot at an enemy.
    void Cowboy::shoot(Character *enemy) {
        if (this == enemy) {
            throw std::runtime_error("cannot kill himself");
        }
        if (hasboolets() && isAlive() && enemy->isAlive()) {
            double dist = distance(enemy);
            enemy->hit(10);
            num_of_bullets--;
        } else if (!isAlive() || !enemy->isAlive()) {
            throw std::runtime_error("the cowboy is dead");
        }
    }

    // Check if the cowboy has bullets.
    bool Cowboy::hasboolets() {
        if (!isAlive()) {
            throw std::runtime_error("the cowboy is dead");
        }
        return num_of_bullets > 0;
    }

    // Method to reload the bullets.
    void Cowboy::reload() {
        if (!isAlive()) {
            throw std::runtime_error("the cowboy is dead");
        }
        num_of_bullets = 6;
    }

    // Method to print the Cowboy's information.
    string Cowboy::print() {
        if (!isAlive()) {
            return "C: (" + getName() + ")";
        } else {
            return "C: " + getName() + ", Location: " + getLocation().print() + ", Score: " + std::to_string(getScore()) + ", Bullets: " + std::to_string(num_of_bullets);
        }
    }

    // Get the type information of the Cowboy class.
    const std::type_info& Cowboy::getType() const {
        return typeid(Cowboy);
    }

} 
