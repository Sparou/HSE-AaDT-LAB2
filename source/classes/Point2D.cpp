#include "Point2D.hpp"
#include <iostream>

Point2D::Point2D()
{
    this->x = 0;
    this->y = 0;
}

Point2D::Point2D(int n)
{
    this->x = n;
    this->y = n;
}

Point2D::Point2D(int x, int y)
{
    this->x = x;
    this->y = y;
}

std::istream& operator>>(std::istream& is, Point2D& obj)
{
    int x, y;
    is >> x >> y;
    obj.setX(x);
    obj.setY(y);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point2D& obj)
{
    return os << "(" << obj.getX() << "," << obj.getY() << ")";
}

bool operator>=(const Point2D& lhs, const Point2D& rhs)
{
    return (lhs.getX() >= rhs.getX() && lhs.getY() >= rhs.getY());
}