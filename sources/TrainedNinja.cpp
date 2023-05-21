#include "TrainedNinja.hpp"

namespace ariel {

    TrainedNinja::TrainedNinja(string name, Point location) : Ninja(location, 120, name) {
        setSpeed(12);
    }

} // namespace ariel
