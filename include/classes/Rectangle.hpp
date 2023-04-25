#pragma once
#include "Point2D.hpp"

class Rectangle
{
    Point2D leftLowerAngle;
    Point2D rightUpperAngle;

public:
    Rectangle();

    // Constractors
    Rectangle(Point2D leftLowerAngle, Point2D rightUpperAngle);

public:
    // Methods
    Point2D getLeftLowerAngle() const { return leftLowerAngle; }
    Point2D getRightUpperAngle() const { return rightUpperAngle; }

    void setLeftLowerAngle(Point2D leftLowerAngle) { this->leftLowerAngle = leftLowerAngle; }
    void setRightUpperAngle(Point2D rightUpperAngle) { this->rightUpperAngle = rightUpperAngle; }
};

std::istream& operator>>(std::istream& is, Rectangle& obj);
std::ostream& operator<<(std::ostream& os, const Rectangle& obj);