#ifndef NINJA_HPP
#define NINJA_HPP
#include <iostream>
#include <string>
#include "Character.hpp"
using namespace std;
     
namespace ariel {
    class Ninja : public Character {
        private:
            int speed;
            
        public:
            Ninja(Point loc,int score,string name);
            Character* createCopy() const override {
            return new Ninja(*this);
        }
            void setSpeed(int speed);
            int getSpeed();
            void move(Character* enemy);
            void slash(Character* enemy);
            string print() override;
            const std::type_info& getType() const override;
            //void destructor() override;


    };
}

    


#endif