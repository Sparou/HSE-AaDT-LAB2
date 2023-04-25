
#pragma once

#include <vector>
#include <random>
#include "Rectangle.hpp"

std::vector<Rectangle> generateRectangles(const int rectanglesCount);

std::vector<Point2D> generateTargetPoints(const int targetsCount, const int rectanglesCount);