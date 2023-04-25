#include "enumeration.hpp"
#include "compressedMap.hpp"
#include "persistentSegmentTree.hpp"
#include "generators.hpp"

int main()
{

    int rectanglesCount;
    int targetsCount;

    std::cout << "Enter the number of rectangles to test -> ";
    std::cin >> rectanglesCount;

    std::cout << "Enter the number of target points to test -> ";
    std::cin >> targetsCount;

    auto rectangels = generateRectangles(rectanglesCount);
    auto targets = generateTargetPoints(targetsCount, rectanglesCount);

    const auto a1 = enumerationSolution(rectangels, targets);
    const auto a2 = compressedMapSolution(rectangels, targets);
    const auto a3 = persistentSegmentTreeSolution(rectangels, targets);


    //std::cout << "a1: ";
    //for (auto a : a1)
    //    std::cout << a << " ";
    //std::cout << std::endl;

    //std::cout << "a2: ";
    //for (auto a : a2)
    //    std::cout << a << " ";
    //std::cout << std::endl;

    //std::cout << "a3: ";
    //for (auto a : a3)
    //    std::cout << a << " ";
    //std::cout << std::endl;
}