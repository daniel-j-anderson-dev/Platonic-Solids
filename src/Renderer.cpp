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
	setShapes();
}

void Renderer::setAxes()
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
	axes[0].vertices = xAxisVertices;
	axes[1].vertices = yAxisVertices;
	axes[2].vertices = zAxisVertices;
	axes[0].edges	 = axisEdges;
	axes[1].edges 	 = axisEdges;
	axes[2].edges	 = axisEdges;
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

		
		for (auto &edge : axes[i].edges)
		{
			drawLine(color, axes[i].vertices[edge.first], axes[i].vertices[edge.second]);
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
		drawLine(white, shape.vertices[edge.first], shape.vertices[edge.second]);
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

// TODO: put transformation functions in Transformer class
Point Renderer::rotatePoint(Point point, Point axis, double angle)
{
    Quaternion rotation      = Quaternion(axis, angle);
    Quaternion original 	 = Quaternion(point);
    Quaternion product  	 = rotation.inverse() * original * rotation;
    Point 	   rotatedPoint  = {product.getX(), product.getY(), product.getZ()};
    return rotatedPoint;
}

Point Renderer::rotatePointAboutAnother(Point point, Point centerOfRotation, Point axis, double angle)
{
	Point difference   = {point.x - centerOfRotation.x, point.y - centerOfRotation.y, point.z - centerOfRotation.z};
	Point rotatedPoint = rotatePoint(difference, axis, angle);
	Point sum		   = {rotatedPoint.x + centerOfRotation.x, rotatedPoint.y + centerOfRotation.y, rotatedPoint.z + centerOfRotation.z};
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

void Renderer::translatePoint(Point &point, Point axis, double distance)
{
	if (axis.x == 0 && axis.y == 0 && axis.z ==0)
		return;
	double norm 		  = sqrt(axis.x*axis.x + axis.y*axis.y + axis.z*axis.z);
	Point newAxis  		  = {distance*(axis.x/norm), distance*(axis.y/norm), distance*(axis.z/norm)};
	point = {point.x + newAxis.x, point.y + newAxis.y, point.z + newAxis.z};
}

void Renderer::tanslateShape(Shape3D &shape, Point axis, double distance)
{
	for (auto &vertex : shape.vertices)
	{
		translatePoint(vertex, axis, distance);
	}
	translatePoint(shape.position, axis, distance);
}

template <int size>
void Renderer::translateShapes(Shape3D (&shapes)[size], Point axis, double distance)
{
	for (auto &shape : shapes)
	{
		tanslateShape(shape, axis, distance);
	}
}

// TODO: put handleInput, handlEvent and setShapes in main
void Renderer::handleInput(const Uint8* keys)
{
	axisOfRotation    = {0, 0, 0};
	axisOfTranslation = {0, 0, 0};
	isLocalRotation = true;
	isWorldRotation = false;

	Point xAxis = axes[0].vertices[2];
	Point yAxis = axes[1].vertices[2];
	Point zAxis = axes[2].vertices[2];

	if (keys[SDL_SCANCODE_ESCAPE])
		isRunning = false;
	if (keys[SDL_SCANCODE_LSHIFT])
		isLocalRotation = false;
	if (keys[SDL_SCANCODE_LCTRL])
		isWorldRotation = true;
	if (keys[SDL_SCANCODE_0])
	{
		setShapes();
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
	if (keys[SDL_SCANCODE_E])
		axisOfRotation.z++;
	if (keys[SDL_SCANCODE_Q])
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
	if (keys[SDL_SCANCODE_LEFT])
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
		startTime = SDL_GetPerformanceCounter();
		
		clearScreen();

		drawShapes(shapes);

		handleEvents(event);

		// Rotator.rotateShapes()
		if (isLocalRotation && !isWorldRotation)
		{
			rotateShapesLocal(shapes, axisOfRotation, 0.01);
		}
		else
		{
			rotateShapesAboutPoint(shapes, {0, 0, 0}, axisOfRotation, 0.01);
		}
		if (isWorldRotation)
		{
			rotateShapesAboutPoint(axes,   {0, 0, 0}, axisOfRotation, 0.01);
		}

		translateShapes(shapes, axisOfTranslation, 1);

		update();
	}
	this->~Renderer();
}