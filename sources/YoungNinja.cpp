#include "YoungNinja.hpp"

namespace ariel
{

    YoungNinja::YoungNinja(string name, Point location) : Ninja(location, 100, name)
    {
        setSpeed(14);
    }
}
