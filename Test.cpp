#include "doctest.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include "sources/Team.hpp"
#include "sources/Team2.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Test 1 - Initialization - Point")
{
    Point p1(1, 2), p2(2,2), p3(3,2);
    CHECK(p1.getX() == 1);
    CHECK(p1.getY() == 2);
    CHECK(p1.distance(p2) == p2.distance(p1));
    Point res = p1.moveTowards(p3,1);
    CHECK(res == p2);
    res = p2.moveTowards(p3,0);
    CHECK(res == p2); 
    CHECK_THROWS(p2.moveTowards(p3,-2));
}
TEST_CASE("Test 2 - Initialization - Characters")
{
    Point p1(1, 2), p2(2,2), p3(15,20);
    Cowboy c("c", p1);
    Cowboy c1("martin", p1);
    OldNinja n1("sushi", p2);
    YoungNinja n2("sushika", p3);

    CHECK(n1.getScore() == 150);
    c.setScore(0); // make him dead
    CHECK_THROWS(c.hasboolets());
    CHECK(c1.getLocation() == p1);
    CHECK(c1.getScore() == 110);
    CHECK(c1.getNumOfBullets() == 6);
    CHECK(c1.getName() == "martin");
    c1.hit(10);
    CHECK(c1.getScore() == 100);
    c1.shoot(&n1);
    CHECK(n1.getScore() == 140);
    CHECK(c1.getNumOfBullets() == 5);
    c1.reload();
    CHECK(c1.getNumOfBullets() == 6);
    n1.slash(&c1); 
    n1.slash(&c1);
    n1.slash(&c1);// killed c1
    CHECK_FALSE(c1.isAlive());
    CHECK_THROWS(c1.getNumOfBullets());
    CHECK_THROWS(c1.shoot(&n2));
    n1.slash(&n2);
    CHECK(n2.getScore() == 100); // the ninja is too far
}
TEST_CASE("Test 3- create and add members to a new team")
{
    Point p1(1, 2), p2(2,2), p3(15,20), p4(32,5);
    Cowboy *tom = new Cowboy("Tom", p1);
    OldNinja *sushi = new OldNinja("sushi", p2);
    YoungNinja *sashimi = new YoungNinja("sashimi", p3);
    Cowboy *sam = new Cowboy("sam", p4);

    Team team_test(tom);
    CHECK(team_test.stillAlive() == 1); // added only the team
    team_test.add(sushi);
    team_test.add(sashimi);
    team_test.add(sam);
    CHECK(team_test.stillAlive() == 4);
    CHECK(team_test.getTeamLeader()->getName() == tom->getName());
    CHECK((team_test.getMembers()[3])->getType().name() == typeid(Ninja).name()); // ninja are after cowboys
}
TEST_CASE("Test 4 - attack")
{
    Point p1(1, 2), p2(2,2), p3(15,20), p4(32,5), p5(37,97);
    Cowboy *tom = new Cowboy("Tom", p1);
    OldNinja *sushi = new OldNinja("sushi", p2);
    YoungNinja *sashimi = new YoungNinja("sashimi", p3);
    Cowboy *ben = new Cowboy("ben", p1);

    Cowboy *sam = new Cowboy("sam", p4);
    TrainedNinja *Ryu = new TrainedNinja("Ryu", p2);
    YoungNinja *Hanzo = new YoungNinja("Hanzo", p3);
    Cowboy *Erl = new Cowboy("Erl", p1);
    Cowboy *Arnold = new Cowboy("Arnold", p5);

    Team team_a(tom);
    team_a.add(sushi);
    team_a.add(sashimi);
    team_a.add(ben);

    Team team_b(sam);
    team_b.add(Hanzo);
    team_b.add(Erl);
    team_b.add(Ryu);
    team_b.add(Arnold);

    Character *victim = team_a.findClosestVictim(&team_b);
    CHECK(victim->getName() == "Erl");
    CHECK(team_b.stillAlive() == 5);

    while(team_a.stillAlive() > 0 && team_b.stillAlive() > 0){
    team_b.attack(&team_a);
    team_a.attack(&team_b);
    }
    CHECK(team_b.stillAlive() > 0);  

    Cowboy *Usher = new Cowboy("Usher", p1);
    Cowboy *Casi = new Cowboy("Casi", p4);
    OldNinja *Don = new OldNinja("Don", p2);
    Team team_c(Usher);
    team_c.add(Casi);
    team_c.add(Don);

    team_a.attack(&team_c);
    tom->setScore(0);
    ben->setLocation(Point(2,16));
    sushi->setLocation(Point(1,3));
    team_a.attack(&team_c);
    CHECK(team_a.getTeamLeader()->getName() == "ben"); // changed team leader in the attack



}
TEST_CASE("Test 5 - Team vs Team2 ")
{
  Point p1(1, 2), p2(2,2), p3(15,20), p4(32,5), p5(37,97);
    Cowboy *tom = new Cowboy("Tom", p1);
    OldNinja *sushi = new OldNinja("sushi", p2);
    YoungNinja *sashimi = new YoungNinja("sashimi", p3);
    Cowboy *ben = new Cowboy("ben", p1);

    Cowboy *sam = new Cowboy("sam", p4);
    TrainedNinja *Ryu = new TrainedNinja("Ryu", p2);
    YoungNinja *Hanzo = new YoungNinja("Hanzo", p3);
    Cowboy *Erl = new Cowboy("Erl", p1);
    Cowboy *Arnold = new Cowboy("Arnold", p5);

    Team team_a(tom);
    team_a.add(sushi);
    team_a.add(sashimi);
    team_a.add(ben);

    Team2 team_b(sam);
    team_b.add(Ryu);
    team_b.add(Arnold);
    team_b.add(Hanzo);
    team_b.add(Erl);
     
    CHECK(team_b.stillAlive() == 5);
    CHECK((team_a.getMembers()[3])->getType().name() == typeid(Ninja).name()); // ninja are after cowboys
    CHECK((team_b.getMembers()[4])->getType().name() == typeid(Cowboy).name()); // in team 2 add by order    
}
