#include "../include/Transformer.h"

std::vector<Shape3D> platonicSolids()
{
	std::vector<Shape3D> platonicSolids;
	double scale = 50;
    const double PHI   = 1.61803398874989484820;
	std::vector<Point> cubeVertices = {
		{ scale, scale, scale}, { scale, scale, -scale}, { scale, -scale, scale}, { scale, -scale, -scale},
        {-scale, scale, scale}, {-scale, scale, -scale}, {-scale, -scale, scale}, {-scale, -scale, -scale}};
	std::vector<std::pair<int, int>> cubeEdges = {
		{0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3},
        {2, 6}, {3, 7}, {4, 5}, {4, 6}, {5, 7}, {6, 7}};
	Point cubePosition = {0, 0, 0};
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
	Point tetrahedronPosition = {200, 0, 0};
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
        {1, 4}, {1, 5}, {2, 4}, {2, 5}, {3, 4}, {3, 5}};
	Point octahedronPosition = {-200, 0, 0};
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
        {scale*PHI, 0, scale/PHI}, {scale*PHI, 0, -scale/PHI}, {-scale*PHI, 0, scale/PHI},  {-scale*PHI, 0, -scale/PHI}};
	std::vector<std::pair<int, int>> dodecahedronEdges = {
		{ 0,  8}, { 0, 12}, { 0, 16}, { 1,  9}, { 1, 12}, { 1, 17},
        { 2, 10}, { 2, 13}, { 2, 16}, { 3, 11}, { 3, 13}, { 3, 17},
        { 4,  8}, { 4, 14}, { 4, 18}, { 5,  9}, { 5, 14}, { 5, 19},
        { 6, 10}, { 6, 15}, { 6, 18}, { 7, 11}, { 7, 15}, { 7, 19},
        { 8, 10}, { 9, 11}, {12, 14}, {13, 15}, {16, 17}, {18, 19}};
	Point dodecahedronPosition = {0, 200, 0};
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
	Point icosahedronPosition = {0, -200, 0};
	for (auto& vertex : icosahedronVertices)
	{
		vertex.x += icosahedronPosition.x;
		vertex.y += icosahedronPosition.y;
		vertex.z += icosahedronPosition.z;
	};

	platonicSolids.push_back({cubeVertices,         cubeEdges,         cubePosition});
	platonicSolids.push_back({tetrahedronVertices,  tetrahedronEdges,  tetrahedronPosition});
	platonicSolids.push_back({octahedronVertices,   octahedronEdges,   octahedronPosition});
	platonicSolids.push_back({dodecahedronVertices, dodecahedronEdges, dodecahedronPosition});
	platonicSolids.push_back({icosahedronVertices,  icosahedronEdges,  icosahedronPosition});
	return platonicSolids;
}

void rotatePoint(Point &point, Point axis, double angle)
{
    Quaternion rotation      = Quaternion(axis, angle);
    Quaternion original 	 = Quaternion(point);
    Quaternion product  	 = rotation.inverse() * original * rotation;
    Point 	   rotatedPoint  = {product.getX(), product.getY(), product.getZ()};
    point 					 = rotatedPoint;
}

void rotatePointAboutAnother(Point &point, Point centerOfRotation, Point axis, double angle)
{
	Point difference   = point - centerOfRotation;
	rotatePoint(difference, axis, angle);
	Point rotatedPoint = difference + centerOfRotation;
	point = rotatedPoint;
}

void rotateShapeLocal(Shape3D &shape, Point axis, double angle)
{
	for (auto &vertex : shape.vertices)
	{
		rotatePointAboutAnother(vertex, shape.position, axis, angle);
	}
}

void rotateShapeAboutPoint(Shape3D &shape, Point centerOfRotation, Point axis, double angle)
{
	for (auto &vertex : shape.vertices)
	{
		rotatePointAboutAnother(vertex, centerOfRotation, axis, angle);
	}
	rotatePointAboutAnother(shape.position, centerOfRotation, axis, angle);
}

void rotateShapesLocal(std::vector<Shape3D> &shapes, Point axis, double angle)
{
	for (auto &shape : shapes)
	{
		rotateShapeLocal(shape, axis, angle);
	}
}

void rotateShapesAboutPoint(std::vector<Shape3D> &shapes, Point centerOfRotation, Point axis, double angle)
{
	for (auto &shape : shapes)
	{
		rotateShapeAboutPoint(shape, centerOfRotation, axis, angle);
	}
}

void translatePoint(Point &point, Point axis, double distance)
{
    Point newAxis = axis;
	double norm   = sqrt(axis.x*axis.x + axis.y*axis.y + axis.z*axis.z);
    if (norm != 0)
	{
	    newAxis /= norm;
		newAxis *= distance;
	}
	else
		return;
	point += newAxis;
}

void tanslateShape(Shape3D &shape, Point axis, double distance)
{
	for (auto &vertex : shape.vertices)
	{
		translatePoint(vertex, axis, distance);
	}
	translatePoint(shape.position, axis, distance);
}

void translateShapes(std::vector<Shape3D> &shapes, Point axis, double distance)
{
	for (auto &shape : shapes)
	{
		tanslateShape(shape, axis, distance);
	}
}