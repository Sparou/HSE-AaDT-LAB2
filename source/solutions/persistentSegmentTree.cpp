#include "persistentSegmentTree.hpp"
#include <algorithm>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

std::pair<std::vector<int>, std::vector<int>> compressCoordinatesPST(const std::vector<Rectangle>& rectangles)
{
    std::vector<int> uniqueCoordsX, uniqueCoordsY;
    for (auto& r : rectangles)
    {
        uniqueCoordsX.push_back(r.getLeftLowerAngle().getX());
        uniqueCoordsX.push_back(r.getRightUpperAngle().getX() + 1);
        uniqueCoordsY.push_back(r.getLeftLowerAngle().getY());
        uniqueCoordsY.push_back(r.getRightUpperAngle().getY() + 1);
    }

    sort(uniqueCoordsX.begin(), uniqueCoordsX.end());
    sort(uniqueCoordsY.begin(), uniqueCoordsY.end());
    uniqueCoordsX.erase(std::unique(uniqueCoordsX.begin(), uniqueCoordsX.end()), uniqueCoordsX.end());
    uniqueCoordsY.erase(std::unique(uniqueCoordsY.begin(), uniqueCoordsY.end()), uniqueCoordsY.end());

    return std::pair<std::vector<int>, std::vector<int>>(uniqueCoordsX, uniqueCoordsY);
}

std::shared_ptr<Node> newPersistentConditionOfTree(std::shared_ptr<Node> node, int l, int r, int value, int range_left, int range_right)
{
    if (std::max(l, range_left) <= std::min(r, range_right))
    {
        std::shared_ptr<Node> root = node ? std::make_shared<Node>(node) : std::make_shared<Node>();

        if (range_left >= l && range_right <= r)
        {
            root->value += value;
            return root;
        }

        int middle = (range_left + range_right) / 2;

        root->left = newPersistentConditionOfTree(node ? node->left : nullptr, l, r, value, range_left, middle);
        root->right = newPersistentConditionOfTree(node ? node->right : nullptr, l, r, value, middle + 1, range_right);
        return root;
    }

    return node;
}

size_t findPositionPST(std::vector<int>& items, long target)
{
    return std::upper_bound(items.begin(), items.end(), target) - items.begin() - 1;
}

int findRectanglesCount(std::shared_ptr<Node> root, int y, int range_left, int range_right)
{
    if (!root)
    {
        return 0;
    }

    if (range_left == range_right)
    {
        return root->value;
    }

    int middle = (range_left + range_right) / 2;
    return root->value + (y <= middle ? findRectanglesCount(root ? root->left : nullptr, y, range_left, middle)
                                      : findRectanglesCount(root ? root->right : nullptr, y, middle + 1, range_right));
}

std::vector<int> persistentSegmentTreeSolution(const std::vector<Rectangle>& rectangles, const std::vector<Point2D>& targets)
{
    auto dataPreparationStartTime = Clock::now();

    auto [uniqueCoordsX, uniqueCoordsY] = compressCoordinatesPST(rectangles);

    std::vector<std::pair<int, Rectangle>> coordinates;

    for (auto& r : rectangles)
    {
        coordinates.push_back(std::make_pair(findPositionPST(uniqueCoordsX, r.getLeftLowerAngle().getX()), r));
        coordinates.push_back(std::make_pair(findPositionPST(uniqueCoordsX, r.getRightUpperAngle().getX() + 1), r));
    }

    sort(coordinates.begin(), coordinates.end(),
        [](std::pair<int, Rectangle> left, std::pair<int, Rectangle> right) { return left.first < right.first; });


    std::vector<std::shared_ptr<Node>> trees(rectangles.size() * 2);
    auto root = std::make_shared<Node>();
    int current_coord = 0;
    for (const auto x : coordinates)
    {
        auto lower = findPositionPST(uniqueCoordsY, x.second.getLeftLowerAngle().getY());
        auto upper = findPositionPST(uniqueCoordsY, x.second.getRightUpperAngle().getY());

        if (x.first != current_coord)
        {
            trees[current_coord] = root;
            current_coord = x.first;
        }

        root = newPersistentConditionOfTree(root,                                    //
            lower,                                                                   //
            upper,                                                                   //
            uniqueCoordsX[x.first] == x.second.getLeftLowerAngle().getX() ? 1 : -1,  //
            0,                                                                       //
            uniqueCoordsY.size() - 1);
    }

    auto dataPreparationEndTime = Clock::now();
    auto startTime = Clock::now();

    std::vector<int> answers;

    for (auto point : targets)
    {

        if (point.getX() < uniqueCoordsX[0] || point.getX() > uniqueCoordsX[uniqueCoordsX.size() - 1] || point.getY() < uniqueCoordsY[0] ||
            point.getY() > uniqueCoordsY[uniqueCoordsY.size() - 1])
        {
            answers.push_back(0);
            continue;
        }

        auto x = findPositionPST(uniqueCoordsX, point.getX());
        auto y = findPositionPST(uniqueCoordsY, point.getY());

        answers.push_back(findRectanglesCount(trees[x], y, 0, uniqueCoordsY.size() - 1));
    }

    auto endTime = Clock::now();
    std::cout << "PST Data preparation time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(dataPreparationEndTime - dataPreparationStartTime).count()
              << std::endl;
    std::cout << "PST time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << std::endl;

    return std::vector<int>(answers);
}
