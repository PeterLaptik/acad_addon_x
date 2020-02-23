#include "../StdAfx.h"
#include "Shape.h"
#include "../draw_helpers/Point.h"
#include "../draw_helpers/Drafter.h"
#include <axlock.h>
#include <math.h>


static const double bulge = -tan(3.14 / 8);			// default fillet bulge value (if tfe )
static const double MAXIMUM_SLOPE_RESTRAINT = 20;	// maximum slope for the flange (in percents)

Shape::Shape()
{ }

Shape::~Shape()
{ }

AcDbObjectId Shape::DrawMe()
{
	int seg_counter = 0;				// polyline segment number counter
	double delta = CalculateSlope();	// linear distance for slope

	if (type == L"U")
	{
		AcDbPolyline* polyline = new AcDbPolyline();
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X, -h / 2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X, h / 2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b - X, h / 2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b - X, h / 2 - t + R2 + delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b - X - R2, h / 2 - t+delta));
		polyline->setBulgeAt(seg_counter - 2, -GetCentralAngle(b - X, h / 2 - t + R2 + delta,
																b - X - R2, h / 2 - t +delta,
																R2));
		
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X + s + R1, h / 2 - t - delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X + s, h / 2 - t - R1 - delta));
		polyline->setBulgeAt(seg_counter - 2, GetCentralAngle(-X + s + R1, h / 2 - t - delta,
																-X + s, h / 2 - t - R1 - delta,
																R1));

		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X + s, -h / 2 + t + R1+delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X + s + R1, -h / 2 + t+delta));
		polyline->setBulgeAt(seg_counter - 2, GetCentralAngle(-X + s, -h / 2 + t + R1 + delta,
																-X + s + R1, -h / 2 + t + delta,
																R1));

		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X + b - R2, -h / 2 + t-delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X + b, -h / 2 + t - R2-delta));
		polyline->setBulgeAt(seg_counter - 2, -GetCentralAngle(-X + b - R2, -h / 2 + t - delta,
			-X + b, -h / 2 + t - R2 - delta,
			R2));

		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X + b, -h / 2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X, -h / 2));
		return AddPolyLineToTable(polyline);
	}

	if (type == L"I")
	{
		AcDbPolyline* polyline = new AcDbPolyline();
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b/2, -h / 2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b/2, -h / 2 + t - R2 - delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b/2 + R2, -h / 2 + t - delta));
		polyline->setBulgeAt(seg_counter - 2, -GetCentralAngle(-b / 2, -h / 2 + t - R2 - delta, -b / 2 + R2, -h / 2 + t - delta, R2));
		
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-s/2 - R1, -h / 2 + t + delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-s / 2, -h / 2 + t + R1 + delta));
		polyline->setBulgeAt(seg_counter - 2, GetCentralAngle(-s/2 - R1, -h / 2 + t + delta, -s / 2, -h / 2 + t + R1 + delta, R1));

		polyline->addVertexAt(seg_counter++, AcGePoint2d(-s / 2, h / 2 - t - R1 - delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-s / 2 - R1, h / 2 - t - delta));
		polyline->setBulgeAt(seg_counter - 2, GetCentralAngle(-s / 2, h / 2 - t - R1 - delta, -s / 2 - R1, h / 2 - t - delta, R1));
		
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b/2 + R2, h / 2 - t + delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b/2, h / 2 - t + R2 + delta));
		polyline->setBulgeAt(seg_counter - 2, -GetCentralAngle(-b/2 + R2, h / 2 - t + delta, -b/2, h / 2 - t + R2 + delta, R2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b/2, h / 2));
		
		// Symmetric part
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b/2, h / 2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b/2, h / 2 - t + R2 + delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b / 2 - R2, h / 2 - t + delta));
		polyline->setBulgeAt(seg_counter - 2, -GetCentralAngle(b / 2, h / 2 - t + R2 + delta, b / 2 - R2, h / 2 - t + delta, R2));

		polyline->addVertexAt(seg_counter++, AcGePoint2d(s / 2 + R1, h / 2 - t - delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(s / 2, h / 2 - t - R1 - delta));
		polyline->setBulgeAt(seg_counter - 2, GetCentralAngle(s / 2 + R1, h / 2 - t - delta, s / 2, h / 2 - t - R1 - delta, R1));
		
		polyline->addVertexAt(seg_counter++, AcGePoint2d(s / 2, -h / 2 + t + R1 + delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(s / 2 + R1, -h / 2 + t + delta));
		polyline->setBulgeAt(seg_counter - 2, GetCentralAngle(s / 2, -h / 2 + t + R1 + delta, s / 2 + R1, -h / 2 + t + delta, R1));
		
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b/2 - R2, -h / 2 + t - delta));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b/2, -h / 2 + t - R2 - delta));
		polyline->setBulgeAt(seg_counter - 2, -GetCentralAngle(b / 2 - R2, -h / 2 + t - delta, b / 2, -h / 2 + t - R2 - delta, R2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b/2, -h / 2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b/2, -h / 2));
		
		return AddPolyLineToTable(polyline);
	}

	if (type == L"T")
	{
		AcDbPolyline* polyline = new AcDbPolyline();
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b / 2, -Y));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b / 2, -Y + t - R2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b / 2 + R2, -Y + t));
		polyline->setBulgeAt(seg_counter - 2, bulge);

		polyline->addVertexAt(seg_counter++, AcGePoint2d(-s / 2 - R1, -Y + t));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-s / 2, -Y + t + R1));
		polyline->setBulgeAt(seg_counter - 2, -bulge);

		polyline->addVertexAt(seg_counter++, AcGePoint2d(-s / 2, -Y + h - R2));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-s / 2 + R2, -Y + h));
		polyline->setBulgeAt(seg_counter - 2, bulge);

		polyline->addVertexAt(seg_counter++, AcGePoint2d(s / 2 - R2, -Y + h));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(s / 2, -Y + h - R2));
		polyline->setBulgeAt(seg_counter - 2, bulge);

		polyline->addVertexAt(seg_counter++, AcGePoint2d(s / 2, -Y + t + R1));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(s / 2 + R1, -Y + t));
		polyline->setBulgeAt(seg_counter - 2, -bulge);

		polyline->addVertexAt(seg_counter++, AcGePoint2d(b/2 - R2, -Y + t));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(b / 2, -Y + t -R2));
		polyline->setBulgeAt(seg_counter - 2, bulge);

		polyline->addVertexAt(seg_counter++, AcGePoint2d(b / 2, -Y));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-b / 2, -Y));
		return AddPolyLineToTable(polyline);
	}

	if ((type == L"L") || (type == L"L1"))
	{
		AcDbPolyline* polyline = new AcDbPolyline();
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X, -Y));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X, h-Y));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X+s-R2, h-Y));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X+s, h-Y-R2));
		polyline->setBulgeAt(seg_counter - 2, bulge);

		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X+s, -Y+t+R1));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X+s+R1, -Y+t));
		polyline->setBulgeAt(seg_counter - 2, -bulge);

		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X+b-R2, -Y+t));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X+b, -Y+t-R2));
		polyline->setBulgeAt(seg_counter - 2, bulge);

		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X+b, -Y));
		polyline->addVertexAt(seg_counter++, AcGePoint2d(-X, -Y));

		return AddPolyLineToTable(polyline);
	}

	return 0;	// unknown shape type
}


// Adds created polyline into autocad table
// Returns created object ID
AcDbObjectId Shape::AddPolyLineToTable(AcDbPolyline* polyline)
{
	AcDbObjectId entity_id;
	AcAxDocLock lock(acdbHostApplicationServices()->workingDatabase());
	if (lock.lockStatus() == Acad::eOk) {
		AcDbBlockTable* block_table;
		acdbHostApplicationServices()->workingDatabase()->getSymbolTable(block_table, AcDb::kForRead);

		AcDbBlockTableRecord* table_record;
		Acad::ErrorStatus s = block_table->getAt(ACDB_MODEL_SPACE, table_record, AcDb::kForWrite);
		block_table->close();

		table_record->appendAcDbEntity(entity_id, polyline);
		table_record->close();
	}
	polyline->close();
	return entity_id;
}


// Calculates vertical linear distance for the flange slope
double Shape::CalculateSlope()
{
	double delta = 0;
	if ((slope <= 0) || (slope > MAXIMUM_SLOPE_RESTRAINT))
		return delta;

	if(type==L"U")
		delta = (b - s) / 2 * (slope / 100) / 2;

	if (type == L"I")
		delta = (b / 2 - s / 2) / 2 * (slope / 100) / 2;

	acutPrintf(L"\nSlope:%d\n", delta);
	return delta;
}


double Shape::GetCentralAngle(double x1, double y1, double x2, double y2, double r)
{
	if (r == 0)
		return 3.14 / 8;

	double length = pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);
	return (asin(length / (r * 2)))/2;
}