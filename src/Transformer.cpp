#include "../include/Transformer.h"

Transformer::Transformer()
{

}

Transformer::~Transformer()
{

}

void Transformer::rotatePoint(Point &point, Point axis, double angle)
{
    Quaternion rotation      = Quaternion(axis, angle);
    Quaternion original 	 = Quaternion(point);
    Quaternion product  	 = rotation.inverse() * original * rotation;
    Point 	   rotatedPoint  = {product.getX(), product.getY(), product.getZ()};
    point = rotatedPoint;
}

void Transformer::rotatePointAboutAnother(Point &point, Point centerOfRotation, Point axis, double angle)
{
	Point difference = {point.x - centerOfRotation.x, point.y - centerOfRotation.y, point.z - centerOfRotation.z};
	rotatePoint(difference, axis, angle);
	Point sum = {difference.x + centerOfRotation.x, difference.y + centerOfRotation.y, difference.z + centerOfRotation.z};
	point = sum;
}

void Transformer::rotateShapeLocal(Shape3D &shape, Point axis, double angle)
{
	for (auto &vertex : shape.vertices)
	{
		rotatePointAboutAnother(vertex, shape.position, axis, angle);
	}
}

void Transformer::rotateShapeAboutPoint(Shape3D &shape, Point centerOfRotation, Point axis, double angle)
{
	for (auto &vertex : shape.vertices)
	{
		rotatePointAboutAnother(vertex, centerOfRotation, axis, angle);
	}
	rotatePointAboutAnother(shape.position, centerOfRotation, axis, angle);
}

template <int size>
void Transformer::rotateShapesLocal(Shape3D (&shapes)[size], Point axis, double angle)
{
	for (auto& shape : shapes)
	{
		rotateShapeLocal(shape, axis, angle);
	}
}

template <int size>
void Transformer::rotateShapesAboutPoint(Shape3D (&shapes)[size], Point centerOfRotation, Point axis, double angle)
{
	for (auto& shape : shapes)
	{
		rotateShapeAboutPoint(shape, centerOfRotation, axis, angle);
	}
}

void Transformer::translatePoint(Point &point, Point axis, double distance)
{
    Point newAxis = {0, 0, 0};
	double norm   = sqrt(axis.x*axis.x + axis.y*axis.y + axis.z*axis.z);
    if (norm != 0)
	    Point newAxis = {distance*(axis.x/norm), distance*(axis.y/norm), distance*(axis.z/norm)};
	point = {point.x + newAxis.x, point.y + newAxis.y, point.z + newAxis.z};
}

void Transformer::tanslateShape(Shape3D &shape, Point axis, double distance)
{
	for (auto &vertex : shape.vertices)
	{
		translatePoint(vertex, axis, distance);
	}
	translatePoint(shape.position, axis, distance);
}

template <int size>
void Transformer::translateShapes(Shape3D (&shapes)[size], Point axis, double distance)
{
	for (auto &shape : shapes)
	{
		tanslateShape(shape, axis, distance);
	}
}