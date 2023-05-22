#include "Ninja.hpp"

namespace ariel {
    Ninja::Ninja(Point loc, int score, string name) : Character(loc, score, name), speed(0) {}

    void Ninja::setSpeed(int s) {
        speed = s;
    }
    
    // Override function to get the type information of the Ninja class.
    const std::type_info& Ninja::getType() const {
        return typeid(Ninja);
    }

    void Ninja::move(Character* enemy) {
        Point enemy_loc = enemy->getLocation();
        double dist = this->getLocation().distance(enemy_loc);
        
        // Calculate the new location based on the speed and direction towards the enemy.
        Point new_loc = Point::moveTowards(this->getLocation(), enemy->getLocation(), this->speed);
        setLocation(new_loc);
    }

    void Ninja::slash(Character* enemy) {
        if (this == enemy) {
            throw std::runtime_error("Cannot kill oneself");
        }
        if (isAlive() && distance(enemy) <= 1 && enemy->isAlive()) {
            enemy->hit(40);
        } else if (!isAlive() || !enemy->isAlive()) {
            cout << this->print() << endl;
            cout << enemy->print() << endl;
            throw std::runtime_error("Cannot slash");
        }
    }
    
    int Ninja::getSpeed() {
        return speed;
    }

    string Ninja::print() {
        if (!isAlive()) {
            return "N: (" + getName() + ")";
        } else {
            return "N: " + getName() + ", Location: " + getLocation().print() + ", Score: " + std::to_string(getScore()) + ", Speed: " + std::to_string(speed);
        }
    }
}
