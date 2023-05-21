#ifndef YOUNTNINJA_HPP
#define YOUNTNINJA_HPP
#include <iostream>
#include <string>
#include "Ninja.hpp"
namespace ariel {
    class YoungNinja : public Ninja {
        public:
            YoungNinja(string name, Point location);
            // YountNinja(const YountNinja &other);
            // YountNinja &operator=(const YountNinja &other);
            // YountNinja(YountNinja &&other) noexcept;
            // YountNinja &operator=(YountNinja &&other) noexcept;
            // ~YountNinja() override; // add virtual keyword and define the destructor later

    };
}

#endif
