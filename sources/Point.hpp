#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include <string>
using namespace std;

namespace ariel
{
    class Point
    {
    private:
        double point_x;
        double point_y;

    public:
        Point(double point_x, double point_y);
        double distance(Point point);
        double getX();
        double getY();
        static Point moveTowards(Point src, Point dest, double distance);
        string print();
        friend bool operator==(const Point &point1, const Point &point2);
    };
}

#endif