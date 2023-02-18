#include "../include/Renderer.h"

Renderer::Renderer(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{    
    SDL_Init(SDL_INIT_VIDEO);
    window        = SDL_CreateWindow("Platonic Solids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer2D    = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	ORIGIN        = Point(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0);
	isLocalRotation = true;
	setAxes();

	// TODO: remove these members
    isRunning     = true;
	setShapes();
}

void Renderer::setAxes()
{
	double length = 0;
	if (ORIGIN.getX() > ORIGIN.getY())
	{
		length = ORIGIN.getX() * 2;
	}
	else
	{
		length = ORIGIN.getY() * 2;
	}
	std::vector<Point> xAxisVertices = {Point(-length, 0, 0), Point(0, 0, 0), Point(length, 0, 0)};
	std::vector<Point> yAxisVertices = {Point(0, -length, 0), Point(0, 0, 0), Point(0, length, 0)};
	std::vector<Point> zAxisVertices = {Point(0, 0, -length), Point(0, 0, 0), Point(0, 0, length)};
	std::vector<std::pair<int, int>> axisEdges = {{0, 1}, {1, 2}};
	axes[0].vertices = xAxisVertices;
	axes[1].vertices = yAxisVertices;
	axes[2].vertices = zAxisVertices;
	axes[0].edges	 = axisEdges;
	axes[1].edges 	 = axisEdges;
	axes[2].edges	 = axisEdges;
}

void Renderer::drawLine(Point startPoint, Point endPoint)
{
	startPoint = startPoint + ORIGIN;
	endPoint   = endPoint   + ORIGIN;
	SDL_SetRenderDrawColor(renderer2D, 0, 0, 0, 255); // red, green, blue, alpha
	SDL_RenderDrawLine(renderer2D, startPoint.getX(), startPoint.getY(), endPoint.getX(), endPoint.getY());
	SDL_RenderPresent(renderer2D);
}

void Renderer::drawShape(Shape3D shape)
{
	for (auto &edge : shape.edges)
	{
		drawLine(shape.vertices[edge.first], shape.vertices[edge.second]);
	}
}

template <int size>
void Renderer::drawShapes(Shape3D (&shapes)[size])
{
	for (auto &shape : shapes)
	{
		drawShape(shape);
	}
}

void Renderer::clearScreen()
{
	SDL_SetRenderDrawColor(renderer2D, 255, 255, 255, 255);
	SDL_RenderClear(renderer2D);
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer2D);
	SDL_Quit();
}

// TODO: put roation functions in Rotator class
Point Renderer::rotatePoint(Point point, Point axis, double angle)
{
    Quaternion rotation      = Quaternion(/*new*/axis, angle);
    Quaternion original 	 = Quaternion(point);
    Quaternion product  	 = rotation.inverse() * original * rotation;
    Point 	   rotatedPoint  = Point(product.getX(), product.getY(), product.getZ());
    return rotatedPoint;
}

Point Renderer::rotatePointAboutAnother(Point point, Point centerOfRotation, Point axis, double angle)
{
	Point difference   = point - centerOfRotation;
	Point rotatedPoint = rotatePoint(difference, axis, angle);
	Point sum		   = rotatedPoint + centerOfRotation;
	return sum;
}

void Renderer::rotateShapeLocal(Shape3D &shape, Point axis, double angle)
{
	std::vector<Point> rotatedVertices;
	for (auto &vertex : shape.vertices)
	{
		Point rotatedVertex = rotatePointAboutAnother(vertex, shape.position, axis, angle);
		rotatedVertices.push_back(rotatedVertex);
	}
	shape.vertices = rotatedVertices;
}

void Renderer::rotateShapeAboutPoint(Shape3D &shape, Point centerOfRotation, Point axis, double angle)
{
	std::vector<Point> rotatedVertices;
	for (auto &vertex : shape.vertices)
	{
		Point rotatedVertex = rotatePointAboutAnother(vertex, centerOfRotation, axis, angle);
		rotatedVertices.push_back(rotatedVertex);
	}
	shape.position = rotatePointAboutAnother(shape.position, centerOfRotation, axis, angle);
	shape.vertices = rotatedVertices;
}

template <int size>
void Renderer::rotateShapesLocal(Shape3D (&shapes)[size], Point axis, double angle)
{
	for (auto& shape : shapes)
	{
		rotateShapeLocal(shape, axis, angle);
	}
}

template <int size>
void Renderer::rotateShapesAboutPoint(Shape3D (&shapes)[size], Point centerOfRotation, Point axis, double angle)
{
	for (auto& shape : shapes)
	{
		rotateShapeAboutPoint(shape, centerOfRotation, axis, angle);
	}
}

// TODO: put handleInput, handlEvent and setShapes in main
void Renderer::handleInput(const Uint8* keys)
{
	axisOfRotation  = Point(0, 0, 0);
	isLocalRotation = true;
	if (keys[SDL_SCANCODE_ESCAPE])
		isRunning = false;
	if (keys[SDL_SCANCODE_0])
		setShapes();
	if (keys[SDL_SCANCODE_LSHIFT])
		isLocalRotation = false;

	if (keys[SDL_SCANCODE_A])
		axisOfRotation.incX();
	if (keys[SDL_SCANCODE_D])
		axisOfRotation.decX();
	if (keys[SDL_SCANCODE_W])
		axisOfRotation.incY();
	if (keys[SDL_SCANCODE_S])
		axisOfRotation.decY();
	if (keys[SDL_SCANCODE_E])
		axisOfRotation.incZ();
	if (keys[SDL_SCANCODE_Q])
		axisOfRotation.decZ();
	if (keys[SDL_SCANCODE_SPACE])
		axisOfRotation.incXYZ();
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
		}
	}
}

// TODO: put vertex and edge data for each shape here
void Renderer::setShapes() // sets shapes to the platonic solids
{
	shapes[0] = Shape3D(0); // Cube
	shapes[1] = Shape3D(1); // Tetrahedron
	shapes[2] = Shape3D(2); // Octahedron
	shapes[3] = Shape3D(3); // Dodecahedron
	shapes[4] = Shape3D(4); // Icosahedron
}

void Renderer::run()
{
    while (isRunning)
	{
		Uint64 startTime = SDL_GetPerformanceCounter();

		clearScreen();

		drawShapes(shapes);

		handleEvents(event);

		if (isLocalRotation)
		{
			rotateShapesLocal(shapes, axisOfRotation, 0.1);
		}
		else
		{
			rotateShapesAboutPoint(shapes, Point(0, 0, 0), axisOfRotation, 0.1);
			rotateShapesAboutPoint(axes,   Point(0, 0, 0), axisOfRotation, 0.1);
		}


		Uint64 endTime = SDL_GetPerformanceCounter();
		double elapsedTime = (endTime - startTime) / (SDL_GetPerformanceFrequency() * 1000);
		SDL_Delay(floor((16.6666666666666666) - elapsedTime));
	}
	this->~Renderer();
}