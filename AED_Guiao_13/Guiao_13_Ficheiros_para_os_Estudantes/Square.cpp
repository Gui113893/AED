//
// Algoritmos e Estruturas de Dados - 2023/2024
//
// COMPLETE the code, according to Square.h
//

#include "Square.h"

#include <cassert>
#include <iostream>
#include <string>

#include "Point.h"
#include "Rectangle.h"

// Rectangle of edge=1 and centered at (0,0)
Square::Square(void) : Rectangle() {}

// WRITE THE MISSING CONSTRUTORS, METHODS AND FRIEND FUNCTIONS
Square::Square(Point center, const std::string& color, double length) : Rectangle(center, color, length, length) {}

Square::Square(double x, double y, const std::string& color, double length) : Rectangle(x, y, color, length, length) {}

double Square::GetEdgeLength(void) const { return Rectangle::GetWidth(); }

void Square::SetEdgeLength(double length) {
  // Ensure that the edge is larger than 0.0
  // COMPLETE
  if (length <= 0.0) {
    std::cerr << "ERROR: Square::SetEdgeLength: Invalid edge length."
              << std::endl;
    exit(EXIT_FAILURE);
  }
  Rectangle::SetWidth(length);
  Rectangle::SetHeight(length);
}

std::string Square::GetClassName(void) const { return "Square"; }

std::ostream& operator<<(std::ostream& os, const Square& obj) {
  os << "Center: " << obj.GetCenter() << std::endl;
  os << "Color: " << obj.GetColor() << std::endl;
  os << "Edge = " << obj.GetEdgeLength() << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Square& obj) {
  // COMPLETE
  double x, y, length;
  std::string color;

  std::cout << "x = ";
  is >> x;
  std::cout << "y = ";
  is >> y;
  obj.SetCenter(Point(x, y));

  std::cout << "color = ";
  is >> color;
  obj.SetColor(color);

  std::cout << "edge length = ";
  is >> length;
  obj.SetEdgeLength(length);
 
  return is;
}