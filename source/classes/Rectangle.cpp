#include "Point2D.hpp"
#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle()
{
    leftLowerAngle = Point2D(0);
    rightUpperAngle = Point2D(0);
}

Rectangle::Rectangle(Point2D leftLowerAngle, Point2D rightUpperAngle)
{
    this->leftLowerAngle = leftLowerAngle;
    this->rightUpperAngle = rightUpperAngle;
}

std::istream& operator>>(std::istream& is, Rectangle& obj)
{
    Point2D leftLowerAngle, rightUpperAngel;
    is >> leftLowerAngle >> rightUpperAngel;
    obj.setLeftLowerAngle(leftLowerAngle);
    obj.setRightUpperAngle(rightUpperAngel);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& obj)
{
    return os << "{" << obj.getLeftLowerAngle() << ", " << obj.getRightUpperAngle() << "}";
}
