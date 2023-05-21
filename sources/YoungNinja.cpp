#include "YoungNinja.hpp"

namespace ariel {

    YoungNinja::YoungNinja(string name, Point location) : Ninja(location, 100, name) {
        setSpeed(14);
    }
    // YountNinja::~YountNinja(){}
    
    // YountNinja::YountNinja(const YountNinja&) = delete;

    // // Delete copy assignment operator
    // YountNinja& YountNinja::operator=(const YountNinja&) = delete;

    // // Delete move constructor
    // YountNinja::YountNinja(YountNinja&&) = delete;

    // // Delete move assignment operator
    // YountNinja& YountNinja::operator=(YountNinja&&) = delete;

}
