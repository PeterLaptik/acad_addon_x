#ifndef STRUCTURAL_SHAPE_H
#define STRUCTURAL_SHAPE_H

// Represents structural shape's properties
// Shape types (field 'type'):
//	I - I-beam
//	U - channel
//	L - angle
//	L1 - angle (unequal)
//	T - tee bar

#include "../StdAfx.h"
#include <string>

struct Shape
{
		double b;	// width
		double h;	// height
		double s;	// thickness
		double t;	// thickness
		double R1;	// fillet radius 1
		double R2;	// fillet radius 2
		double X;	// distance from center axis
		double Y;	// distance from center axis
		double A;	// surface - sq. mm
		double mass;	// mass - kg/m
		double R3;			// additional fillet radius
		std::wstring type;		// shape type
		std::wstring name;		// shape name
		std::wstring standard;	// code
		double slope = 0.0;		// flange slope value in percents
								// no slope for zero-value
								// the value is applied for I and U shapes only

		Shape(void);
		~Shape(void);
		virtual AcDbObjectId DrawMe(void);	// Draws element on model space in the current database

	private:
		AcDbObjectId AddPolyLineToTable(AcDbPolyline* polyline);
		double CalculateSlope(void);
		double GetCentralAngle(double x1, double y1, double x2, double y2, double r);
};

#endif
