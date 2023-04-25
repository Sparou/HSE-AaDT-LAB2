#pragma once

#include <iostream>

class Point2D
{

    int x;
    int y;

public:
    Point2D();

    explicit Point2D(int n);

    Point2D(int x, int y);

    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

std::istream& operator>>(std::istream& is, Point2D& obj);
std::ostream& operator<<(std::ostream& os, const Point2D& obj);
bool operator>=(const Point2D& lhs, const Point2D& rhs);
