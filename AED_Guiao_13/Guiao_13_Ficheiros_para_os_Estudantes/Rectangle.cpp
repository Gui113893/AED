//
// Algoritmos e Estruturas de Dados - 2023/2024
//
// COMPLETE the code, according to Rectangle.h
//

#include "Rectangle.h"

#include <cassert>
#include <iostream>
#include <string>

#include "Point.h"

// Rectangle of width=1 and height=1 and centered at (0,0)
Rectangle::Rectangle(void) : Figure(), width_(1.0), height_(1.0)  {}

Rectangle::Rectangle(Point center, const std::string& color, double width,
                     double height) {
  // Ensure that the width and height are larger than 0.0
  // COMPLETE
  Figure::SetCenter(center);
  Figure::SetColor(color);
  Rectangle::SetWidth(width);
  Rectangle::SetHeight(height);
}

Rectangle::Rectangle(double x, double y, const std::string& color, double width,
                     double height) {
  // Ensure that the width and height are larger than 0.0
  // COMPLETE
  Figure::SetCenter(Point(x, y));
  Figure::SetColor(color);
  Rectangle::SetWidth(width);
  Rectangle::SetHeight(height);
}

double Rectangle::GetHeight(void) const { return height_; }
void Rectangle::SetHeight(double length) {
  // Ensure that the height is larger than 0.0
  // COMPLETE
  if (length <= 0.0) {
    std::cerr << "ERROR: Rectangle::SetHeight: Invalid height." << std::endl;
    exit(EXIT_FAILURE);
  }
  height_ = length;
}

double Rectangle::GetWidth(void) const { return width_; }
void Rectangle::SetWidth(double length) {
  // Ensure that the width is larger than 0.0
  // COMPLETE
  if (length <= 0.0) {
    std::cerr << "ERROR: Rectangle::SetWidth: Invalid width." << std::endl;
    exit(EXIT_FAILURE);
  }
  width_ = length;
}

std::string Rectangle::GetClassName(void) const { return "Rectangle"; }

double Rectangle::Area(void) const {
  // COMPLETE
  return Rectangle::GetWidth() * Rectangle::GetHeight();
}

double Rectangle::Perimeter(void) const {
  // COMPLETE
  return 2 * Rectangle::GetWidth() + 2 * Rectangle::GetHeight();
}

std::ostream& operator<<(std::ostream& os, const Rectangle& obj) {
  // COMPLETE
  os << "Center: " << obj.GetCenter() << std::endl;
  os << "Color: " << obj.GetColor() << std::endl;
  os << "Width = " << obj.width_ << std::endl;
  os << "Height = " << obj.height_ << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Rectangle& obj) {
  // COMPLETE
  double x, y;
  std::string color;

  std::cout << "x = ";
  is >> x;
  std::cout << "y = ";
  is >> y;
  obj.SetCenter(Point(x, y));

  std::cout << "color = ";
  is >> color;
  obj.SetColor(color);

  std::cout << "width = ";
  is >> obj.width_;
  std::cout << "height = ";
  is >> obj.height_;

  return is;
}