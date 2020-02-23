#ifndef SHAPE_READER_H
#define SHAPE_READER_H

#include "Shape.h"
#include <string>
#include <vector>

// Reads shape data from txt-files
// txt-file format (TAB-delimiter):
//	name	type	code		h	b	s	t	R1	R2	X	Y	A	m
//	# - comment

class ShapeReader
{
public:
	ShapeReader();
	~ShapeReader();
	void SetPath(std::wstring base_path);
	void ReadShapes(void);

	std::vector<Shape>* GetShapes_U(void) { return &shapes_U; }
	std::vector<Shape>* GetShapes_I(void) { return &shapes_I; }
	std::vector<Shape>* GetShapes_T(void) { return &shapes_T; }
	std::vector<Shape>* GetShapes_L(void) { return &shapes_L; }
	std::vector<Shape>* GetShapes_L1(void) { return &shapes_L1; }
	//std::vector<Shape>* GetShapes_O(void) { return &shapes_O; }
	
private:
	std::wstring file_path;
	std::vector<Shape> shapes_I;
	std::vector<Shape> shapes_U;
	std::vector<Shape> shapes_T;
	std::vector<Shape> shapes_L;
	std::vector<Shape> shapes_L1;
	//std::vector<Shape> shapes_O;

	bool CheckShape(const Shape &s) const;
};

#endif
