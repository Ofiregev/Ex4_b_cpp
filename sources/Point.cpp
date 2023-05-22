#include "Point.hpp"
#include <cmath>

namespace ariel {

    Point::Point(double x, double y) : point_x(x), point_y(y) {}

double Point::distance(Point p) {
    double dx = this->point_x - p.point_x;
    double dy = this->point_y - p.point_y;
    return sqrt(dx * dx + dy * dy);
}

    double Point::getX() {
        return point_x;
    }

    double Point::getY() {
        return point_y;
    }

    string Point::print() {
        return "(" + std::to_string(point_x) + "," + std::to_string(point_x)+ ")" ;
    }



    Point Point::moveTowards(Point src, Point dest, double distance) {
    if (distance < 0) {
        throw std::invalid_argument("Distance must be positive!");
    }
    if (distance == 0) {
        return src;
    }

    double distanceToDest = src.distance(dest);

    if (distanceToDest <= distance) {
        return dest;
    }

    double ratio = distance / distanceToDest;
    double new_x = src.getX() + ratio * (dest.getX() - src.getX());
    double new_y = src.getY() + ratio * (dest.getY() - src.getY());

    return Point(new_x, new_y);
}
 
       



bool operator==(const Point& point1, const Point& point2){
    return (point1.point_x == point2.point_x && point1.point_y == point2.point_y);
}

}






