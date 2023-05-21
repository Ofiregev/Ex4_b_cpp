#include "OldNinja.hpp"

namespace ariel {
    OldNinja::OldNinja(string name, Point location) : Ninja(location, 150, name) {
        setSpeed(8);
    }
}
