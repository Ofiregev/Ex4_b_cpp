#include "Point.hpp"
#include <cmath>

namespace ariel {

    Point::Point(double x, double y) : point_x(x), point_y(y) {}

    double Point::distance(Point p) {
    double dx = point_x - p.point_x;
    double dy = point_y - p.point_y;
    return sqrt(dx*dx + dy*dy);
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



Point moveTowards(Point src, Point dest, double distance) {
    if(distance < 0)
    {
        throw std::invalid_argument("distance must be positive !");
    }
    if (distance ==0)
    {
        return Point(src.point_x, src.point_y);
    }
    double calculated_distance = sqrt(pow(dest.getX() - src.point_x, 2) + pow(dest.getY() - src.point_y, 2));
    if (calculated_distance <= distance) {
        return dest;
    }
    double ratio = calculated_distance / distance;
    double dx = dest.getX() - src.point_x;
    double dy = dest.getY() - src.point_y;
    double new_dx = dx / ratio;
    double new_dy = dy / ratio;
    double new_x = src.point_x + new_dx;
    double new_y = src.point_y + new_dy;
    return Point(new_x, new_y);
}

bool operator==(const Point& point1, const Point& point2){
    return (point1.point_x == point2.point_x && point1.point_y == point2.point_y);
}

}






