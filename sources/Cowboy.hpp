#ifndef COWBOY_HPP
#define COWBOY_HPP
#include "Character.hpp"
#include <iostream>
#include <string>
#include "Point.hpp"
using namespace std;
     
namespace ariel {
    class Cowboy : public Character {
        private:
            int num_of_bullets;
            
        public:
            Cowboy(string name, Point location);
            Character* createCopy() const override {
            return new Cowboy(*this);
        }
            int getNumOfBullets();
            void setBullets(int bul);   
            void shoot(Character * enemy);
            bool hasboolets();
            void reload();
            string print() override;
            const std::type_info& getType() const override;

    };
}

    


#endif