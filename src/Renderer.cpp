#include "../include/Renderer.h"

Renderer::Renderer(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{    
    SDL_Init(SDL_INIT_VIDEO);
    window            = SDL_CreateWindow("Platonic Solids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer2D        = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	background 		  = SDL_CreateTextureFromSurface(renderer2D, SDL_LoadBMP("background.bmp"));
	ORIGIN            = {(double)WINDOW_WIDTH/2, (double)WINDOW_HEIGHT/2, 0};
	axesDefault();
	startTime = SDL_GetPerformanceCounter();
	endTime   = 0;
	shapes = NULL;
}

void Renderer::axesDefault()
{
	double length = 0;
	if (ORIGIN.x > ORIGIN.y)
	{
		length = ORIGIN.x * 2;
	}
	else
	{
		length = ORIGIN.y * 2;
	}
	std::vector<Point> xAxisVertices = {{-length, 0, 0}, {0, 0, 0}, {length, 0, 0}};
	std::vector<Point> yAxisVertices = {{0, -length, 0}, {0, 0, 0}, {0, length, 0}};
	std::vector<Point> zAxisVertices = {{0, 0, -length}, {0, 0, 0}, {0, 0, length}};
	std::vector<std::pair<int, int>> axisEdges = {{0, 1}, {1, 2}};
	axes = {
		{xAxisVertices, axisEdges, {0, 0, 0}},
		{yAxisVertices, axisEdges, {0, 0, 0}},
		{zAxisVertices, axisEdges, {0, 0, 0}}};
}

Point Renderer::xAxis()
{
	// TODO: use norm in transformer
	Point xAxis = axes.at(0).vertices.at(2);
	xAxis /= norm(xAxis);
	return xAxis;
}

Point Renderer::yAxis()
{
	Point yAxis = axes.at(1).vertices.at(2);
	yAxis /= norm(yAxis);
	return yAxis;
}

Point Renderer::zAxis()
{
	Point zAxis = axes.at(2).vertices.at(2);
	zAxis /= norm(zAxis);
	return zAxis;
}

std::vector<Shape3D> *Renderer::getAxes()
{
	return &(this->axes);
}

std::vector<Shape3D> *Renderer::getShapes()
{
	return this->shapes;
}

void Renderer::setShapes(std::vector<Shape3D> *shapes)
{
	this->shapes = shapes;
}

void Renderer::drawAxes()
{
	for (int i = 0; i < 3; i++)
	{
		rgbaColor color = {0, 0, 0, 0};
		if (i == 0)
			color = {255, 0, 0, 255};
		else if (i == 2)		
			color = {0, 255, 0, 255};
		else if (i == 1)	
			color = {0, 0, 255, 255};

		
		for (auto &edge : axes.at(i).edges)
		{
			drawLine(color, axes.at(i).vertices.at(edge.first), axes.at(i).vertices.at(edge.second));
			// TODO: draw negative half axes as a dashed line
		}
	}
}

void Renderer::drawLine(rgbaColor color, Point startPoint, Point endPoint)
{
	startPoint = {startPoint.x + ORIGIN.x, startPoint.y + ORIGIN.y, startPoint.z + ORIGIN.z};
	endPoint   = {endPoint.x   + ORIGIN.x, endPoint.y   + ORIGIN.y, endPoint.z   + ORIGIN.z};
	SDL_SetRenderDrawColor(renderer2D, color.red, color.blue, color.green, color.alpha);
	SDL_RenderDrawLine(renderer2D, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

void Renderer::drawShape(Shape3D shape)
{
	rgbaColor white = {255, 255, 255, 255};
	for (auto &edge : shape.edges)
	{
		drawLine(white, shape.vertices.at(edge.first), shape.vertices.at(edge.second));
	}
}

void Renderer::drawShapes(std::vector<Shape3D>shapes)
{
	for (auto &shape : shapes)
	{
		drawShape(shape);
	}
}

void Renderer::clearScreen()
{
	SDL_SetRenderDrawColor(renderer2D, 0, 0, 0, 255);
	SDL_RenderClear(renderer2D);
	drawAxes();
}

void Renderer::update()
{
	SDL_RenderPresent(renderer2D);
	endTime = SDL_GetPerformanceCounter();
	double elapsedTime = (endTime - startTime) / (SDL_GetPerformanceFrequency() * 1000);
	SDL_Delay(floor((16.6666666666666666) - elapsedTime));
	startTime = SDL_GetPerformanceCounter();
}

void Renderer::draw()
{
	this->clearScreen();

	this->drawShapes(*(this->shapes));
	
	this->update();
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer2D);
	SDL_Quit();
}