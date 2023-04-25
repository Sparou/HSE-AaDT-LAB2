#pragma once

#include <memory>
#include <vector>
#include "Rectangle.hpp"

struct Node
{
    Node() {}

    Node(const std::shared_ptr<Node> other) : value(other->value), left(other->left), right(other->right) {}

    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    int value = 0;
};

size_t findPositionPST(std::vector<int>& items, long target);

std::pair<std::vector<int>, std::vector<int>> compressCoordinatesPST(const std::vector<Rectangle>& rectangles);

std::shared_ptr<Node> newPersistentConditionOfTree(std::shared_ptr<Node> node, int l, int r, int value, int range_left, int range_right);

int findRectanglesCount(std::shared_ptr<Node> root, int y, int range_left, int range_right);

std::vector<int> persistentSegmentTreeSolution(const std::vector<Rectangle>& rectangles, const std::vector<Point2D>& targets);
