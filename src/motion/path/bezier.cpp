#include "main.h"
#include "motion/path/bezier.hpp"
#include <vector>

namespace path
{
Bezier::Bezier(std::initializer_list<std::reference_wrapper<Point>> points, int resolution, int lookahead) : Path::Path(resolution, lookahead),
                                                                                                             points(points) {}

std::vector<int> getPascalCoeff(int rowIndex)
{
    std::vector<int> row;
    row.push_back(1);
    if (rowIndex == 0)
        return row;
    row.push_back(1);
    if (rowIndex == 1)
        return row;

    std::vector<int> result;
    for (int j = 2; j <= rowIndex; j++)
    {
        result.clear();
        result.push_back(1);
        for (int i = 1; i <= j - 1; i++)
        {
            result.push_back(row[i - 1] + row[i]);
        }
        result.push_back(1);
        row = result;
    }
    return row;
}

/**
 * x = (1-t)((1-t)((1-t) * x0 + tx1) + t((1-t)x1 + tx2)) + t((1-t)((1-t)x1 + tx2) + t((1-t)((1-t)x2 + tx3)))
 */

Point Bezier::pointAt(int T)
{

    int rowIndex = points.size() - 1;
    std::vector<int> row;
    row.push_back(1);
    if (!(rowIndex == 0))
        row.push_back(1);

    std::vector<int> result;
    for (int j = 2; j <= rowIndex; j++)
    {
        result.clear();
        result.push_back(1);
        for (int i = 1; i <= j - 1; i++)
        {
            result.push_back(row[i - 1] + row[i]);
        }
        result.push_back(1);
        row = result;
    }

    std::vector<int> coefficients = row; // store them in here when done, hardcoded for now

    Point point = {0_in, 0_in};

    double sT = (double)T / (double)resolution; // scaled t

    sT = (sT > 1.0) ? 1.0 : sT;

    double sumX = 0.0;
    double sumY = 0.0;

    for (int i = 0; i < points.size(); i++)
    {
        Point currPoint = points[i];
        for (int j = points.size() - 1; j >= 0; j--)
        {
            double oneTFactor = pow((1 - sT), j);
            double tFactor = pow(sT, points.size() - 1 - j);

            sumX += coefficients[i] * oneTFactor * tFactor * currPoint.x.convert(okapi::inch);
            sumY += coefficients[i] * oneTFactor * tFactor * currPoint.y.convert(okapi::inch);
        }
    }

    point.x = sumX * okapi::inch;
    point.y = sumX * okapi::inch;
    point.t = T;

    return point;
}
} // namespace path
