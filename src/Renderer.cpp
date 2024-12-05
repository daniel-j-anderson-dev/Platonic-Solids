#include "../include/Renderer.hpp"
#include "Transformer.hpp"
#include <SDL3/SDL.h>
#include <array>
#include <iostream>

Renderer::Renderer(int WINDOW_WIDTH, int WINDOW_HEIGHT) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "failed to initialize SDL: " << SDL_GetError()
                  << std::endl;
        std::exit(-1);
    }

    window = SDL_CreateWindow("Platonic Solids", WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cerr << "failed to create window: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }

    renderer2D = SDL_CreateRenderer(window, "software");
    if (renderer2D == nullptr) {
        std::cerr << "failed to create renderer2D: " << SDL_GetError()
                  << std::endl;
        std::exit(-1);
    }

    background = SDL_CreateTextureFromSurface(renderer2D,
                                              SDL_LoadBMP("../background.bmp"));
    if (background == nullptr) {
        std::cerr << "failed to create background: " << SDL_GetError()
                  << std::endl;
        std::exit(-1);
    }

    ORIGIN =
        Point{.x = (double)WINDOW_WIDTH / 2, .y = (double)WINDOW_HEIGHT / 2, 0};
    axesDefault();
    startTime = SDL_GetPerformanceCounter();
    endTime = 0;
    shapes = platonicSolids();
}

void Renderer::axesDefault() {
    double length = 0;
    if (ORIGIN.x > ORIGIN.y) {
        length = ORIGIN.x * 2;
    } else {
        length = ORIGIN.y * 2;
    }
    std::vector<Point> xAxisVertices = {Point{-length, 0, 0}, Point{0, 0, 0},
                                        Point{length, 0, 0}};
    std::vector<Point> yAxisVertices = {Point{0, -length, 0}, Point{0, 0, 0},
                                        Point{0, length, 0}};
    std::vector<Point> zAxisVertices = {Point{0, 0, -length}, Point{0, 0, 0},
                                        Point{0, 0, length}};
    std::vector<std::pair<int, int>> axisEdges = {{0, 1}, {1, 2}};

    axes = {Shape3D{xAxisVertices, axisEdges, {0, 0, 0}},
            Shape3D{yAxisVertices, axisEdges, {0, 0, 0}},
            Shape3D{zAxisVertices, axisEdges, {0, 0, 0}}};
}

Point Renderer::xAxis() {
    // TODO: use norm in transformer
    Point xAxis = axes.at(0).vertices.at(2);
    xAxis /= norm(xAxis);
    return xAxis;
}

Point Renderer::yAxis() {
    Point yAxis = axes.at(1).vertices.at(2);
    yAxis /= norm(yAxis);
    return yAxis;
}

Point Renderer::zAxis() {
    Point zAxis = axes.at(2).vertices.at(2);
    zAxis /= norm(zAxis);
    return zAxis;
}

std::span<Shape3D, 3> Renderer::getAxes() { return std::span(this->axes); }

std::span<Shape3D, 5> Renderer::getShapes() { return this->shapes; }

void Renderer::setShapes(const std::array<Shape3D, 5> shapes) {
    this->shapes = shapes;
}

void Renderer::drawAxes() {
    for (int i = 0; i < 3; i++) {
        rgbaColor color = {0, 0, 0, 0};
        if (i == 0)
            color = {255, 0, 0, 255};
        else if (i == 2)
            color = {0, 255, 0, 255};
        else if (i == 1)
            color = {0, 0, 255, 255};

        for (auto &edge : axes.at(i).edges) {
            drawLine(color, axes.at(i).vertices.at(edge.first),
                     axes.at(i).vertices.at(edge.second));
            // TODO: draw negative half axes as a dashed line
        }
    }
}

void Renderer::drawLine(rgbaColor color, Point startPoint, Point endPoint) {
    startPoint = {startPoint.x + ORIGIN.x, startPoint.y + ORIGIN.y,
                  startPoint.z + ORIGIN.z};
    endPoint = {endPoint.x + ORIGIN.x, endPoint.y + ORIGIN.y,
                endPoint.z + ORIGIN.z};
    SDL_SetRenderDrawColor(renderer2D, color.red, color.blue, color.green,
                           color.alpha);
    SDL_RenderLine(renderer2D, startPoint.x, startPoint.y, endPoint.x,
                   endPoint.y);
}

void Renderer::drawShape(const Shape3D &shape) {
    rgbaColor white = {255, 255, 255, 255};
    for (auto &edge : shape.edges) {
        drawLine(white, shape.vertices.at(edge.first),
                 shape.vertices.at(edge.second));
    }
}

void Renderer::drawShapes() {
    for (auto &shape : this->shapes) {
        drawShape(shape);
    }
}

void Renderer::clearScreen() {
    SDL_SetRenderDrawColor(renderer2D, 0, 0, 0, 255);
    SDL_RenderClear(renderer2D);
    drawAxes();
}

void Renderer::update() {
    SDL_RenderPresent(renderer2D);
    endTime = SDL_GetPerformanceCounter();
    double elapsedTime = static_cast<double>(endTime - startTime) /
                         (SDL_GetPerformanceFrequency() * 1000);
    SDL_Delay(floor((16.6666666666666666) - elapsedTime));
    startTime = SDL_GetPerformanceCounter();
}

void Renderer::draw() {
    this->clearScreen();

    this->drawShapes();

    this->update();
}

Renderer::~Renderer() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer2D);
    SDL_Quit();
}