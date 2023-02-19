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

// TODO: put vertex and edge data for each shape here
void Renderer::setShapes() // sets shapes to the platonic solids
{
	double scale = 50;
    const double PHI   = 1.61803398874989484820;
	std::vector<Point> cubeVertices = {
		{ scale, scale, scale}, { scale, scale, -scale}, { scale, -scale, scale}, { scale, -scale, -scale},
        {-scale, scale, scale}, {-scale, scale, -scale}, {-scale, -scale, scale}, {-scale, -scale, -scale}};
	std::vector<std::pair<int, int>> cubeEdges = {
		{0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3},
        {2, 6}, {3, 7}, {4, 5}, {4, 6}, {5, 7}, {6, 7}};
	Point cubePosition = {0, 0, 100};
	for (auto& vertex : cubeVertices)
	{
		vertex.x += cubePosition.x;
		vertex.y += cubePosition.y;
		vertex.z += cubePosition.z;
	}

	std::vector<Point> tetrahedronVertices = {
		{scale, scale, scale}, {-scale, -scale, scale}, {-scale, scale, -scale}, {scale, -scale, -scale}};
	std::vector<std::pair<int, int>> tetrahedronEdges = {
		{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
	Point tetrahedronPosition = {200, 200, 100};
	for (auto& vertex : tetrahedronVertices)
	{
		vertex.x += tetrahedronPosition.x;
		vertex.y += tetrahedronPosition.y;
		vertex.z += tetrahedronPosition.z;
	};

	scale *= 1.25; // make the octahedron similar size
	std::vector<Point> octahedronVertices = {
		{scale, 0, 0},  {-scale, 0, 0}, {0, scale, 0},
        {0, -scale, 0}, {0, 0, scale},  {0, 0, -scale}};
	std::vector<std::pair<int, int>> octahedronEdges = {
		{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3},
        {1, 4}, {1, 5}, {2, 4}, {2, 5}, {3, 4}, {3, 5}};;
	Point octahedronPosition = {200, -200, 100};
	for (auto& vertex : octahedronVertices)
	{
		vertex.x += octahedronPosition.x;
		vertex.y += octahedronPosition.y;
		vertex.z += octahedronPosition.z;
	};

	scale *=.6; // make the dodecah and icosah .75 times scale
	std::vector<Point> dodecahedronVertices = {
		{scale, scale, scale},     {scale, scale, -scale},     {scale, -scale, scale},      {scale, -scale, -scale},
        {-scale, scale, scale},    {-scale, scale, -scale},    {-scale, -scale, scale},     {-scale, -scale, -scale},
        {0, scale/PHI, scale*PHI}, {0, scale/PHI, -scale*PHI}, {0, -scale /PHI, scale*PHI}, {0, -scale/PHI, -scale*PHI},
        {scale/PHI, scale*PHI, 0}, {scale/PHI, -scale*PHI, 0}, {-scale/PHI, scale*PHI, 0},  {-scale/PHI, -scale*PHI, 0},
        {scale*PHI, 0, scale/PHI}, {scale*PHI, 0, -scale/PHI}, {-scale*PHI, 0, scale/PHI},  {-scale*PHI, 0, -scale/PHI}};;
	std::vector<std::pair<int, int>> dodecahedronEdges = {
		{ 0,  8}, { 0, 12}, { 0, 16}, { 1,  9}, { 1, 12}, { 1, 17},
        { 2, 10}, { 2, 13}, { 2, 16}, { 3, 11}, { 3, 13}, { 3, 17},
        { 4,  8}, { 4, 14}, { 4, 18}, { 5,  9}, { 5, 14}, { 5, 19},
        { 6, 10}, { 6, 15}, { 6, 18}, { 7, 11}, { 7, 15}, { 7, 19},
        { 8, 10}, { 9, 11}, {12, 14}, {13, 15}, {16, 17}, {18, 19}};
	Point dodecahedronPosition = {-200, 200, 100};
	for (auto& vertex : dodecahedronVertices)
	{
		vertex.x += dodecahedronPosition.x;
		vertex.y += dodecahedronPosition.y;
		vertex.z += dodecahedronPosition.z;
	};

	std::vector<Point> icosahedronVertices = {
		{0, scale, scale*PHI}, {0, scale, -scale*PHI}, {0, -scale, scale*PHI}, {0, -scale, -scale*PHI},
		{scale, scale*PHI, 0}, {scale, -scale*PHI, 0}, {-scale, scale*PHI, 0}, {-scale, -scale*PHI, 0},
		{scale*PHI, 0, scale}, {scale*PHI, 0, -scale}, {-scale*PHI, 0, scale}, {-scale*PHI, 0, -scale}};
	std::vector<std::pair<int, int>> icosahedronEdges = {
		{ 0,  2}, { 0,  4}, { 0,  6}, { 0,  8}, { 0, 10}, { 1,  3},
        { 1,  4}, { 1,  6}, { 1,  9}, { 1, 11}, { 2,  5}, { 2,  7},
        { 2,  8}, { 2, 10}, { 3,  5}, { 3,  7}, { 3,  9}, { 3, 11},
        { 4,  6}, { 4,  8}, { 4,  9}, { 5,  7}, { 5,  8}, { 5,  9},
        { 6, 10}, { 6, 11}, { 7, 10}, { 7, 11}, { 8,  9}, {10, 11}};
	Point icosahedronPosition = {-200, -200, 100};
	for (auto& vertex : icosahedronVertices)
	{
		vertex.x += icosahedronPosition.x;
		vertex.y += icosahedronPosition.y;
		vertex.z += icosahedronPosition.z;
	};

	shapes[0] = {cubeVertices,         cubeEdges,         cubePosition};
	shapes[1] = {tetrahedronVertices,  tetrahedronEdges,  tetrahedronPosition};
	shapes[2] = {octahedronVertices,   octahedronEdges,   octahedronPosition};
	shapes[3] = {dodecahedronVertices, dodecahedronEdges, dodecahedronPosition};
	shapes[4] = {icosahedronVertices,  icosahedronEdges,  icosahedronPosition};
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