#include "DrawingForm.h"

#include <windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <msclr/marshal_cppstd.h>
#include <cmath>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;


void drawingAxis(Graphics ^graphics, double center_x, double center_y, Pen ^axis_pen, Pen ^grid_pen, System::Drawing::Font ^font)
{
   // Ось X
   graphics->DrawLine(axis_pen, -center_x, 0, center_x, 0);
   // Ось Y
   graphics->DrawLine(axis_pen, 0, -center_y, 0, center_y);

   // Рисуем стрелки осей
   int arrowSize = 7;
   // Стрелка оси X
   graphics->DrawLine(axis_pen, center_x - arrowSize, -arrowSize, center_x, 0);
   graphics->DrawLine(axis_pen, center_x - arrowSize, arrowSize, center_x, 0);
   // Стрелка оси Y
   graphics->DrawLine(axis_pen, -arrowSize, -center_y + arrowSize, 0, -center_y);
   graphics->DrawLine(axis_pen, arrowSize, -center_y + arrowSize, 0, -center_y);

   graphics->DrawString("x", font, Brushes::Black, center_x - 25, -25);
   graphics->DrawString("y", font, Brushes::Black, 25, -center_y + 25);

   // Сетка
   int gridStep = 20;
   for (int x = -center_x + 10; x < center_x; x += gridStep)
      if (x != 0) graphics->DrawLine(grid_pen, x, -center_y, x, center_y);
   for (int y = -center_y; y < center_y; y += gridStep)
      if (y != 0) graphics->DrawLine(grid_pen, -center_x, y, center_x, y);
}

void drawingShapes(Graphics ^graphics, Pen ^pen, double center_x, double center_y, ManagedShape ^_shape, System::Double _rotate, System::Double _squeeze, System::Double _stretch)
{
   ManagedShape ^myshape = _shape;

   for (int i = 0; i < pkol; i++)
   {
      myshape->Points[i].X = (myshape->Points[i].X * 20.0f) + center_x;
      myshape->Points[i].Y = (myshape->Points[i].Y * -20.0f) + center_y;
   }

   if (myshape->Points == nullptr || myshape->Points->Length < 3)
      throw gcnew System::ArgumentException("Некорректный массив точек для DrawPolygon");

   pen->DashStyle = Drawing2D::DashStyle::Solid;
   pen->StartCap = Drawing2D::LineCap::Flat;
   pen->EndCap = Drawing2D::LineCap::Flat;
   graphics->DrawPolygon(pen,
      myshape->Points
   );

   if (pen != nullptr)
   {
      delete pen;
      pen = nullptr;
   }
}

System::Void winAPI::DrawingForm::drawing(System::Object ^sender, System::Windows::Forms::PaintEventArgs ^e)
{
   Graphics ^g = e->Graphics;

   double centerX = pictureBox->Width / 2;
   double centerY = pictureBox->Height / 2;

   System::Double rotate = *rotate_value;
   System::Double squeeze = *squeeze_value;
   System::Double stretch = *stretch_value;

   Pen ^axisPen = gcnew Pen(Color::Black, 1.5f);
   Pen ^gridPen = gcnew Pen(Color::LightGray, 0.5f);
   System::Drawing::Font ^fontXY = gcnew System::Drawing::Font("Arial", 10);

   Pen ^pen = gcnew Pen(Color::FromArgb(shape->Color.R, shape->Color.G, shape->Color.B), 2.0f);

   g->TranslateTransform(centerX, centerY);
   drawingAxis(g, centerX, centerY, axisPen, gridPen, fontXY);
   g->ResetTransform();
   drawingShapes(g, pen, centerX, centerY, shape, rotate, squeeze, stretch);
}
