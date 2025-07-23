#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>

struct Point
{
   double x, y;
};

std::pair<Point, Point> findBestLine(const std::vector<Point> &points)
{
   if (points.size() < 2)      // Недостаточно точек
      return {{0, 0}, {0, 0}}; // Или выбросить исключение

   double minDiff = std::numeric_limits<double>::max();
   std::pair<Point, Point> bestPair;

   for (unsigned int i = 0; i < points.size(); i++)
      for (unsigned int j = i + 1; j < points.size(); j++)
      {
         Point p1 = points[i];
         Point p2 = points[j];

         // Уравнение прямой: A*x + B*y + C = 0
         double A = p2.y - p1.y;
         double B = p1.x - p2.x;
         double C = -A * p1.x - B * p1.y;

         int side1Count = 0;
         int side2Count = 0;

         for (unsigned int k = 0; k < points.size(); k++)
         {
            if (k == i || k == j)
               continue; // Пропускаем точки, образующие прямую

            Point p = points[k];
            double result = A * p.x + B * p.y + C;

            if (result > 0) // R
               side1Count++;
            else if (result < 0) // L
               side2Count++;
            // Если result == 0, точка лежит на прямой, можно игнорировать
         }

         double diff = std::abs(static_cast<double>(side1Count - side2Count));

         if (diff < minDiff)
         {
            minDiff = diff;
            bestPair = {p1, p2};
         }
      }

   return bestPair;
}

int main()
{
   std::vector<Point> points = {
       {1, 1},
       {2, 3}};

   std::pair<Point, Point> result = findBestLine(points);

   std::cout << "Best pair of points: (" << result.first.x << ", " << result.first.y << ") and ("
             << result.second.x << ", " << result.second.y << ")" << std::endl;

   return 0;
}
