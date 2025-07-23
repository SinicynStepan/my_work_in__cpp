#include "AppForm.h"
#include "DrawingForm.h"

#include "Shape.h"

#include <windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <msclr/marshal_cppstd.h>


using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;


std::vector<Shape> shapes;

void loadShapesFromFile(String ^filename) {
   std::ifstream file;
   std::string path = msclr::interop::marshal_as<std::string>(filename);
   file.open(path);

   if (!file.is_open()) return;

   shapes.clear();
   std::string line;

   while (std::getline(file, line)) {
      std::istringstream iss(line);
      Shape shape;
      bool type;
      iss >> type;
      shape.type = type;

      for (int i = 0; i < pkol; i++) {
         iss >> shape.points[i].x >> shape.points[i].y;
      }

      int r, g, b;
      iss >> r >> g >> b;
      shape.color = RGB(r, g, b);

      shapes.push_back(shape);
   }
}

MyPoint CalculateCenter(Shape shape) {
   MyPoint center = { 0.00, 0.00 };
   double x = 0.00;
   double y = 0.00;
   for (int i = 0; i < pkol; i++)
   {
      center.x += shape.points[i].x;
      center.y += shape.points[i].x;
   }

   center.x /= pkol;
   center.y /= pkol;
   return center;
}

MyPoint RotatePoint(MyPoint point, MyPoint center, System::Double angle) {
   double rad = angle * 3.14159265358979323846 / 180.0;
   double s = sin(rad);
   double c = cos(rad);

   // переносим точку в начало координат
   point.x -= center.x;
   point.y -= center.y;

   // поворачиваем
   double xnew = point.x * c - point.y * s;
   double ynew = point.x * s + point.y * c;

   // возвращаем на место
   MyPoint result;
   result.x = (xnew + center.x);
   result.y = (ynew + center.y);

   return result;
}

Shape ScaleShape(Shape shape, System::Double squeezeValue, System::Double stretchValue)
{
   Shape newshape = shape;

   MyPoint center = CalculateCenter(newshape);

   if (squeezeValue == 1 && stretchValue != 1)
      for (int i = 0; i < pkol; i++) {
         newshape.points[i].x = center.x + ((newshape.points[i].x - center.x) * stretchValue);
         newshape.points[i].y = center.y + ((newshape.points[i].y - center.y) * stretchValue);
      }
   if (squeezeValue != 1 && stretchValue == 1)
      for (int i = 0; i < pkol; i++) {
         newshape.points[i].x = center.x + ((newshape.points[i].x - center.x) * -squeezeValue);
         newshape.points[i].y = center.y + ((newshape.points[i].y - center.y) * -squeezeValue);
      }
   if (squeezeValue != 1 && stretchValue != 1)
      for (int i = 0; i < pkol; i++) {
         newshape.points[i].x = center.x + ((newshape.points[i].x - center.x) * -squeezeValue);
         newshape.points[i].y = center.y + ((newshape.points[i].y - center.y) * -squeezeValue);
         newshape.points[i].x = center.x + ((newshape.points[i].x - center.x) * stretchValue);
         newshape.points[i].y = center.y + ((newshape.points[i].y - center.y) * stretchValue);
      }

   return newshape;
}

Shape RotateShape(Shape shape, System::Double angle)
{
   Shape newshape = shape;

   MyPoint center = CalculateCenter(newshape);

   for (int i = 0; i < pkol; i++)
   {
      MyPoint pt;
      pt.x = newshape.points[i].x;
      pt.y = newshape.points[i].y;

      MyPoint point = RotatePoint(pt, center, angle);

      MyPoint pnt;
      pnt.x = point.x;
      pnt.y = point.y;

      newshape.points[i] = pnt;
   }

   return newshape;
}

void drawingToEMF_axis(Graphics ^graphics, double center_x, double center_y, Pen ^axis_pen, Pen ^grid_pen, System::Drawing::Font ^font)
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

void drawingToEMF_shapes(Graphics ^graphics, Pen ^pen, double center_x, double center_y, ManagedShape ^_shape)
{
   ManagedShape ^myshape = _shape;

   for (int i = 0; i < pkol; i++)
   {
      myshape->Points[i].X = (myshape->Points[i].X);
      myshape->Points[i].Y = (myshape->Points[i].Y);
   }

   if (myshape->Points == nullptr || myshape->Points->Length < 3)
      throw gcnew System::ArgumentException("Некорректный массив точек для DrawPolygon");

   pen->DashStyle = Drawing2D::DashStyle::Solid;
   pen->StartCap = Drawing2D::LineCap::Flat;
   pen->EndCap = Drawing2D::LineCap::Flat;
   graphics->DrawPolygon(pen,
      myshape->Points
   );
}

System::Void winAPI::AppForm::buttonOpenInput_Click(System::Object ^sender, System::EventArgs ^e)
{
   if (openInputFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
      try {
         String ^filePath = openInputFileDialog->FileName;
      }
      catch (Exception ^ex) {
         MessageBox::Show("Ошибка: " + ex->Message);
      }
   }
}

double textBox_input_squeeze_value = -1;
double textBox_input_stretch_value = -1;
double textBox_input_rotate_value = 0;
System::Void winAPI::AppForm::textBox_input_squeeze_validating(Object ^sender, CancelEventArgs ^e)
{
   TextBox ^tb = (TextBox ^)sender;
   String ^text = tb->Text->Trim();
   double result = 1;

   bool success = Double::TryParse(text, System::Globalization::NumberStyles::Number, System::Globalization::CultureInfo::CurrentCulture, result);

   if (!success)
      success = Double::TryParse(text, System::Globalization::NumberStyles::Number, System::Globalization::CultureInfo::InvariantCulture, result);
   if (!success)
   {
      MessageBox::Show("Ошибка: введите число (например: 0.14 или 0,5)");
      tb->Text = "1";
   }
   else
      if (result < 0.01 || result > 1)
      {
         MessageBox::Show("Ошибка: введите число от 0.01 до 1");
         tb->Text = "1";
      }

   textBox_input_squeeze_value = result;
}
System::Void winAPI::AppForm::textBox_input_stretch_validating(Object ^sender, CancelEventArgs ^e)
{
   TextBox ^tb = (TextBox ^)sender;
   String ^text = tb->Text->Trim();
   double result;

   bool success = Double::TryParse(text, System::Globalization::NumberStyles::Number, System::Globalization::CultureInfo::CurrentCulture, result);

   if (!success)
      success = Double::TryParse(text, System::Globalization::NumberStyles::Number, System::Globalization::CultureInfo::InvariantCulture, result);

   if (!success)
   {
      MessageBox::Show("Ошибка: введите число (например: 3.14 или 2,5)");
      tb->Text = "1";
   }
   else
      if (result < 1 || result > 20)
      {
         MessageBox::Show("Ошибка: введите число от 1 до 20");
         tb->Text = "1";
      }

   textBox_input_stretch_value = result;
}
System::Void winAPI::AppForm::textBox_input_rotate_validating(Object ^sender, CancelEventArgs ^e)
{
   TextBox ^tb = (TextBox ^)sender;
   String ^text = tb->Text->Trim();
   double result;

   bool success = Double::TryParse(text, System::Globalization::NumberStyles::Number, System::Globalization::CultureInfo::CurrentCulture, result);

   if (!success)
      success = Double::TryParse(text, System::Globalization::NumberStyles::Number, System::Globalization::CultureInfo::InvariantCulture, result);

   if (!success)
   {
      MessageBox::Show("Ошибка: введите число (например: 3.14 или 2,5)");
      tb->Text = "0";
   }

   textBox_input_rotate_value = result;
}

System::Void winAPI::AppForm::buttonPerform_Click(System::Object ^sender, System::EventArgs ^e)
{
   loadShapesFromFile(openInputFileDialog->FileName);

   if (textBox_input_squeeze_value == -1)
      textBox_input_squeeze_value = System::Double::Parse(textBox_input_squeeze->Text);
   if (textBox_input_stretch_value == -1)
      textBox_input_stretch_value = System::Double::Parse(textBox_input_stretch->Text);
   if (textBox_input_rotate_value == 0)
      textBox_input_rotate_value = System::Double::Parse(textBox_input_rotate->Text);

   auto managedShapes = gcnew System::Collections::Generic::List<ManagedShape ^>();
   unsigned int k = 0;
   for (Shape shape : shapes)
   {
      Shape myshape = shape;

      myshape = ScaleShape(myshape, textBox_input_squeeze_value, textBox_input_stretch_value);
      myshape = RotateShape(myshape, textBox_input_rotate_value);

      managedShapes->Add(gcnew ManagedShape(myshape));
      k++;
   }

   //std::vector<std::string> kost;

   for (unsigned int i = 0; i < k; ++i)
   {
      if (saveOutputFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
      {
         try {
            std::string filename = msclr::interop::marshal_as<std::string>(saveOutputFileDialog->FileName);
         }
         catch (Exception ^ex) {
            MessageBox::Show("Ошибка: " + ex->Message);
         }
      }

      DrawingForm ^drawingForm = gcnew DrawingForm(managedShapes[i], textBox_input_squeeze_value, textBox_input_stretch_value, textBox_input_rotate_value);
      drawingForm->ShowDialog();


      String ^path = saveOutputFileDialog->FileName;
      Graphics ^gr = this->CreateGraphics();
      IntPtr hdc = gr->GetHdc();
      Metafile ^img = gcnew Metafile(path, hdc);
      Graphics ^ig = Graphics::FromImage(img);

      //1184, 1161
      int displayWidth = 1184;
      int displayHeight = 1161;
      double centerX = displayWidth / 2;
      double centerY = displayHeight / 2;


      ig->Clear(Color::White);
      Pen ^axisPen = gcnew Pen(Color::Black, 1.5f);
      Pen ^gridPen = gcnew Pen(Color::LightGray, 0.5f);
      System::Drawing::Font ^fontXY = gcnew System::Drawing::Font("Arial", 10);

      Pen ^pen = gcnew Pen(Color::FromArgb(managedShapes[i]->Color.R, managedShapes[i]->Color.G, managedShapes[i]->Color.B), 2.0f);

      ig->TranslateTransform(centerX, centerY);
      drawingToEMF_axis(ig, centerX, centerY, axisPen, gridPen, fontXY);
      ig->ResetTransform();
      drawingToEMF_shapes(ig, pen, centerX, centerY, managedShapes[i]);

      delete ig;
      delete img;
      gr->ReleaseHdc(hdc);
      delete gr;
   }
}


[STAThreadAttribute]
int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
   Application::SetCompatibleTextRenderingDefault(false);
   Application::EnableVisualStyles();
   Application::Run(gcnew winAPI::AppForm);
   return 0;
}
