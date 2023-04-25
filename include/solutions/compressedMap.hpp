#pragma once
#include "vector"
#include "Point2D.hpp"
#include "Rectangle.hpp"

size_t findPosition(std::vector<long>& items, long target);

std::pair<std::vector<int>, std::vector<int>> compressCoordinatesCM(const std::vector<Rectangle>& rectangles);

std::vector<int> compressedMapSolution(const std::vector<Rectangle> rectangles, std::vector<Point2D> targets);