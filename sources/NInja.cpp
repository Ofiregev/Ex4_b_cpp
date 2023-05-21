#include "Ninja.hpp"

namespace ariel {
    Ninja::Ninja(Point loc, int score, string name) : Character(loc, score, name), speed(0) {}

    void Ninja::setSpeed(int s) {
        speed = s;
    }
    const std::type_info& Ninja::getType() const {
        return typeid(Ninja);
    }

    void Ninja::move(Character* enemy) {
        Point enemy_loc = enemy->getLocation();
        double dist = distance(enemy);
        double dx = (enemy_loc.getX() - getLocation().getX()) / dist;
        double dy = (enemy_loc.getY() - getLocation().getY()) / dist;
        Point new_loc(getLocation().getX() + speed * dx, getLocation().getY() + speed * dy);
        setLocation(new_loc);
    }

    void Ninja::slash(Character* enemy) {
         if(this == enemy)
        {
            throw std::runtime_error("cannot kill himself");
        }
        if(isAlive() && distance(enemy) <= 1 && enemy->isAlive()){
            enemy->hit(40);
        }else if(!isAlive() || !enemy->isAlive()){
            cout << this->print() << endl;
            cout << enemy->print() << endl;
            throw std::runtime_error("cannot slash");
        }
    }
    int Ninja::getSpeed()
    {
        return speed;
    }

    string Ninja::print() {
         if(!isAlive())
        {
            return "N: (" + getName() + ")" ;
        }else{
        return "N: " + getName() + ", Location: " + getLocation().print()+ ", Score: " + std::to_string(getScore()) + ", Speed: " + std::to_string(speed) ;

        // cout << "N: " << getName() << " at location ";
        // getLocation().print();
        // cout << ", with speed " << speed << " and score " << getScore() << endl;
    }
    }
}
