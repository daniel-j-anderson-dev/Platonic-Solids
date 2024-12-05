#ifndef Renderer_HPP
#define Renderer_HPP
#include <array>
#include <span>
#pragma once
#include "../include/Shape3D.hpp"
#include <SDL3/SDL.h>

struct rgbaColor {
  int red;
  int green;
  int blue;
  int alpha;
};

class Renderer {
public:
  Renderer(int WINDOW_WIDTH, int WINDOW_HEIGHT);
  ~Renderer();

  // assessors
  Point xAxis();
  Point yAxis();
  Point zAxis();
  std::span<Shape3D, 3> getAxes();
  std::span<Shape3D, 5> getShapes();
  std::vector<Point> allAxes();
  std::pair<Point, double> getWorldOrientation();

  // mutators
  void axesDefault();
  void setShapes(const std::array<Shape3D, 5> shapes);

  // actions
  void drawLine(rgbaColor color, Point startPoint, Point endPoint);
  void drawShape(const Shape3D &shape);
  void drawShapes();
  void drawAxes();

  void clearScreen();
  void update();
  void draw();

private:
  SDL_Window *window;
  SDL_Renderer *renderer2D;
  SDL_Texture *background;
  Point ORIGIN;
  std::array<Shape3D, 5> shapes;
  std::array<Shape3D, 3> axes;
  Uint64 startTime;
  Uint64 endTime;
};

#endif