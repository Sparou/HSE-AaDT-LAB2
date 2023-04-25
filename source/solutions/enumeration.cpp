#include "enumeration.hpp"

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

std::vector<int> enumerationSolution(const std::vector<Rectangle>& rectangles, const std::vector<Point2D>& targets)
{
    auto startTime = Clock::now();

    std::vector<int> answers(targets.size(), 0);

    for (size_t i = 0; i < targets.size(); ++i)
    {
        int result = 0;

        for (const auto r : rectangles)
        {
            result += (targets[i].getX() >= r.getLeftLowerAngle().getX() &&   //
                       targets[i].getX() <= r.getRightUpperAngle().getX() &&  //
                       targets[i].getY() >= r.getLeftLowerAngle().getY() &&   //
                       targets[i].getY() <= r.getRightUpperAngle().getY());
        }

        answers[i] = result;
    }

    auto endTime = Clock::now();
    std::cout << "Enumeration time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << std::endl;

    return answers;
}