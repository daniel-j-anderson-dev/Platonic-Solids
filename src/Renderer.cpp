#include "../include/Renderer.h"	

Renderer::Renderer(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{    
    SDL_Init(SDL_INIT_VIDEO);
    window     = SDL_CreateWindow("Platonic Solids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer2D = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	background = SDL_CreateTextureFromSurface(renderer2D, SDL_LoadBMP("background.bmp"));
	ORIGIN          = {(double)WINDOW_WIDTH/2, (double)WINDOW_HEIGHT/2, 0};
	isLocalRotation = true;
	axisOfRotation    = {0, 0, 0};
	axisOfTranslation = {0, 0, 0};
	setAxes();

	// TODO: remove these members
    isRunning     = true;
	shapes = platonicSolids();
}

void Renderer::setAxes()
{
	std::vector<Shape3D> temp;
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
	temp.push_back({xAxisVertices, axisEdges, {0, 0, 0}});
	temp.push_back({yAxisVertices, axisEdges, {0, 0, 0}});
	temp.push_back({zAxisVertices, axisEdges, {0, 0, 0}});
	axes = temp;
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
	SDL_RenderCopy(renderer2D, background, NULL, NULL);
	drawAxes();
}

void Renderer::update()
{
	SDL_RenderPresent(renderer2D);
	endTime = SDL_GetPerformanceCounter();
	double elapsedTime = (endTime - startTime) / (SDL_GetPerformanceFrequency() * 1000);
	SDL_Delay(floor((16.6666666666666666) - elapsedTime));
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer2D);
	SDL_Quit();
}

// TODO: put handleInput, handlEvent and setShapes in main
void Renderer::handleInput(const Uint8* keys)
{
	axisOfRotation    = {0, 0, 0};
	axisOfTranslation = {0, 0, 0};
	isLocalRotation = true;
	isWorldRotation = false;

	Point xAxis = axes.at(0).vertices.at(2);
	Point yAxis = axes.at(1).vertices.at(2);
	Point zAxis = axes.at(2).vertices.at(2);

	if (keys[SDL_SCANCODE_ESCAPE])
		isRunning = false;
	if (keys[SDL_SCANCODE_LSHIFT])
		isLocalRotation = false;
	if (keys[SDL_SCANCODE_LCTRL])
		isWorldRotation = true;
	if (keys[SDL_SCANCODE_0])
	{
		shapes = platonicSolids();
		setAxes();
	}

	if (keys[SDL_SCANCODE_S])
		axisOfRotation.x++;
	if (keys[SDL_SCANCODE_W])
		axisOfRotation.x--;
	if (keys[SDL_SCANCODE_D])
		axisOfRotation.y++;
	if (keys[SDL_SCANCODE_A])
		axisOfRotation.y--;
	if (keys[SDL_SCANCODE_Q])
		axisOfRotation.z++;
	if (keys[SDL_SCANCODE_E])
		axisOfRotation.z--;
	if (keys[SDL_SCANCODE_SPACE])
	{
		axisOfRotation.x++;
		axisOfRotation.y++;
		axisOfRotation.z++;
	}

	if (keys[SDL_SCANCODE_RIGHT])
	{
		axisOfTranslation.x += xAxis.x;
		axisOfTranslation.y += xAxis.y;
		axisOfTranslation.z += xAxis.z;
	}
	if (keys[SDL_SCANCODE_LEFT]) // WHY DOESNT THIS WORK?!?!!?@!?!?
	{
		axisOfTranslation.x -= xAxis.x;
		axisOfTranslation.x -= xAxis.y;
		axisOfTranslation.x -= xAxis.z;
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		axisOfTranslation.x += yAxis.x;
		axisOfTranslation.y += yAxis.y;
		axisOfTranslation.z += yAxis.z;
	}
	if (keys[SDL_SCANCODE_UP])
	{
		axisOfTranslation.x -= yAxis.x;
		axisOfTranslation.y -= yAxis.y;
		axisOfTranslation.z -= yAxis.z;
	}
	if (keys[SDL_SCANCODE_PAGEUP])
	{
		axisOfTranslation.x += zAxis.x;
		axisOfTranslation.y += zAxis.y;
		axisOfTranslation.z += zAxis.z;
	}
	if (keys[SDL_SCANCODE_PAGEDOWN])
	{
		axisOfTranslation.x -= zAxis.x;
		axisOfTranslation.y -= zAxis.y;
		axisOfTranslation.z -= zAxis.z;
	}
}

void Renderer::handleEvents(SDL_Event event)
{	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				handleInput(SDL_GetKeyboardState(NULL));
				break;

			case SDL_KEYUP:
				handleInput(SDL_GetKeyboardState(NULL));
				break;
			// other events
		}
	}
}

void Renderer::run()
{
    while (isRunning)
	{
		startTime = SDL_GetPerformanceCounter();
		
		clearScreen();

		drawShapes(shapes);

		handleEvents(event);

		// Rotator.rotateShapes()
		if (isWorldRotation)
		{
			rotateShapesAboutPoint(axes,   {0, 0, 0}, axisOfRotation, 0.01);
			rotateShapesAboutPoint(shapes, {0, 0, 0}, axisOfRotation, 0.01);

		}
		else if (isLocalRotation)
		{
			rotateShapesLocal(shapes, axisOfRotation, 0.01);
		}
		else
		{
			rotateShapesAboutPoint(shapes, {0, 0, 0}, axisOfRotation, 0.01);
		}

		translateShapes(shapes, axisOfTranslation, 1);

		update();
	}
	this->~Renderer();
}