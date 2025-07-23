#pragma once
#include <vector>
#include <windows.h>

const int pkol = 8;
//1 0 0 4 4 4 6.5 2 8 0 6.5 -2 8 -4 6.5 -4 4 245 2 188
//const int pkol = 4;
//0 3 3 6 3 6 6 3 6 252 186 3
//1 5 5 15 5 16 12 6 12 255 94 0

struct MyPoint {
   double x;
   double y;
};

struct Shape {
   bool type; // 0 - квадрат. 1 - параллелипипед
   MyPoint points[pkol];
   COLORREF color;
};


public ref class ManagedShape {
public:
   property bool Type;
   property array<System::Drawing::PointF> ^Points;
   property System::Drawing::Color Color;

   ManagedShape(const Shape &shape) {
      Type = shape.type;
      Points = gcnew array<System::Drawing::PointF>(pkol);
      for (int i = 0; i < pkol; i++)
         Points[i] = System::Drawing::PointF(shape.points[i].x, shape.points[i].y);
      Color = System::Drawing::Color::FromArgb(
         GetRValue(shape.color),
         GetGValue(shape.color),
         GetBValue(shape.color));
   }

   Shape ToNative() {
      Shape shape;
      shape.type = Type;
      for (int i = 0; i < pkol; i++) {
         shape.points[i].x = Points[i].X;
         shape.points[i].y = Points[i].Y;
      }
      shape.color = RGB(Color.R, Color.G, Color.B);
      return shape;
   }
};