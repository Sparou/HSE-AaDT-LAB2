#include "generators.hpp"

std::vector<Rectangle> generateRectangles(const int rectanglesCount)
{
    std::vector<Rectangle> rectangles(rectanglesCount);

    for (size_t i = 0; i < rectanglesCount; ++i)
    {
        Point2D leftLowerAngle(10 * i, 10 * i);
        Point2D rightUpperAngle(10 * (2 * rectanglesCount - i), 10 * (2 * rectanglesCount - i));
        rectangles[i] = {leftLowerAngle, rightUpperAngle};
    }

    return rectangles;
}

std::vector<Point2D> generateTargetPoints(const int targetsCount, const int rectanglesCount)
{
    const int p_x = 10007;  // большое простое число для x
    const int p_y = 10009;  // большое простое число для y

    std::vector<Point2D> targets(targetsCount);
    for (size_t i = 0; i < targetsCount; ++i)
    {

        //int x = std::pow(p_x * i, 5);
        //x = x % (20 * rectanglesCount);

        //int y = std::pow(p_y * i, 5);
        //y = y % (20 * rectanglesCount);

        int x = (p_x * i * 31) % (20 * rectanglesCount);
        int y = (p_y * i * 31) % (20 * rectanglesCount);

        targets[i] = {x, y};
    }

    return targets;
}
