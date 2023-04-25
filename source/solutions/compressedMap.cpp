#include "compressedMap.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

size_t findPosition(std::vector<int>& items, long target)
{
    return std::upper_bound(items.begin(), items.end(), target) - items.begin() - 1;
}

std::pair<std::vector<int>, std::vector<int>> compressCoordinatesCM(const std::vector<Rectangle>& rectangles)
{

    std::vector<int> uniqueCoordsX, uniqueCoordsY;
    for (auto& r : rectangles)
    {
        uniqueCoordsX.push_back(r.getLeftLowerAngle().getX());
        uniqueCoordsX.push_back(r.getRightUpperAngle().getX());
        uniqueCoordsX.push_back(r.getRightUpperAngle().getX() + 1);
        uniqueCoordsY.push_back(r.getLeftLowerAngle().getY());
        uniqueCoordsY.push_back(r.getRightUpperAngle().getY());
        uniqueCoordsY.push_back(r.getRightUpperAngle().getY() + 1);
    }

    sort(uniqueCoordsX.begin(), uniqueCoordsX.end());
    sort(uniqueCoordsY.begin(), uniqueCoordsY.end());
    uniqueCoordsX.erase(std::unique(uniqueCoordsX.begin(), uniqueCoordsX.end()), uniqueCoordsX.end());
    uniqueCoordsY.erase(std::unique(uniqueCoordsY.begin(), uniqueCoordsY.end()), uniqueCoordsY.end());

    return std::pair<std::vector<int>, std::vector<int>>(uniqueCoordsX, uniqueCoordsY);
}

std::vector<int> compressedMapSolution(const std::vector<Rectangle> rectangles, std::vector<Point2D> targets)
{
    auto dataPreparationStartTime = Clock::now();

    auto [uniqueCoordsX, uniqueCoordsY] = compressCoordinatesCM(rectangles);

    std::vector<std::vector<int>> map(uniqueCoordsX.size());

    for (std::size_t i = 0; i < uniqueCoordsX.size(); ++i)
    {
        map[i].resize(uniqueCoordsY.size());
    }

    for (const auto& r : rectangles)
    {
        Point2D compressedRightUpper(
            findPosition(uniqueCoordsX, r.getRightUpperAngle().getX()), findPosition(uniqueCoordsY, r.getRightUpperAngle().getY()));
        Point2D compressedLeftDown(
            findPosition(uniqueCoordsX, r.getLeftLowerAngle().getX()), findPosition(uniqueCoordsY, r.getLeftLowerAngle().getY()));

        for (long xIdx = compressedLeftDown.getX(); xIdx < compressedRightUpper.getX() + 1; xIdx++)
        {
            for (long yIdx = compressedLeftDown.getY(); yIdx < compressedRightUpper.getY() + 1; yIdx++)
            {
                map[xIdx][yIdx]++;
            }
        }
    }
    
    auto dataPreparationEndTime = Clock::now();
    auto startTime = Clock::now();

    std::vector<int> answers;
    answers.reserve(targets.size());

    for (const auto& p : targets)
    {

        size_t compressedX = findPosition(uniqueCoordsX, p.getX());
        size_t compressedY = findPosition(uniqueCoordsY, p.getY());

        answers.emplace_back(map[compressedX][compressedY]);
    }

    auto endTime = Clock::now();
    std::cout << "CM Data preparation time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(dataPreparationEndTime - dataPreparationStartTime).count() << std::endl;
    std::cout << "CM time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << std::endl;

    return answers;
}