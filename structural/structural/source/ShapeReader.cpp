#include "ShapeReader.h"
#include "FileReader.h"
#include <iostream>
#include <atlconv.h>
#include <locale>
#include <codecvt>


ShapeReader::ShapeReader()
{ }

ShapeReader::~ShapeReader()
{ }

void ShapeReader::SetPath(std::wstring base_path)
{
	file_path = base_path;
}

void ShapeReader::ReadShapes()
{
	std::string path(file_path.begin(), file_path.end());
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;	// Cyrillic converting
	FileReader reader;

	// Reading U-shapes
	shapes_U.clear();
	reader.SetFilePath(path + "U.txt");
	reader.OpenFile();

	std::string token;
	Shape shape;
	while (reader.ReadLine())
	{
		if (reader.IsEmpty())
			continue;

		if (reader.StartsWith() == '#')		// comment
			continue;

		token = reader.GetStringTrimmed();	// name
		if (token.empty())
			continue;

		shape.name = convert.from_bytes(token);

		token = reader.GetString();					// type
		shape.type = convert.from_bytes(token);
		token = reader.GetString();
		shape.standard = convert.from_bytes(token);

		shape.h = reader.GetDouble();
		shape.b = reader.GetDouble();
		shape.s = reader.GetDouble();
		shape.t = reader.GetDouble();

		shape.R1 = reader.GetDouble();
		shape.R2 = reader.GetDouble();
		shape.X = reader.GetDouble();
		shape.Y = reader.GetDouble();

		shape.A = reader.GetDouble();
		shape.mass = reader.GetDouble();
		shape.slope = reader.GetDouble();

		if(CheckShape(shape))
			shapes_U.push_back(shape);
	}
	reader.CloseFile();

	// Reading I-shapes
	shapes_I.clear();
	reader.SetFilePath(path + "I.txt");
	reader.OpenFile();

	while (reader.ReadLine())
	{
		if (reader.IsEmpty())
			continue;

		if (reader.StartsWith() == '#')
			continue;

		token = reader.GetStringTrimmed();	// name
		shape.name = convert.from_bytes(token);
		//std::cout << "Reading..." << token << std::endl;

		if (shape.name.empty())
			continue;

		token = reader.GetString();					// type
		shape.type = convert.from_bytes(token);
		token = reader.GetString();
		shape.standard = convert.from_bytes(token);

		shape.h = reader.GetDouble();
		shape.b = reader.GetDouble();
		shape.s = reader.GetDouble();
		shape.t = reader.GetDouble();

		shape.R1 = reader.GetDouble();
		shape.R2 = reader.GetDouble();
		shape.X = reader.GetDouble();
		shape.Y = reader.GetDouble();

		shape.A = reader.GetDouble();
		shape.mass = reader.GetDouble();
		shape.slope = reader.GetDouble();

		if (CheckShape(shape))
			shapes_I.push_back(shape);
	}
	reader.CloseFile();

	// Reading T-shapes
	shapes_T.clear();
	reader.SetFilePath(path + "T.txt");
	reader.OpenFile();

	while (reader.ReadLine())
	{
		if (reader.IsEmpty())
			continue;

		if (reader.StartsWith() == '#')
			continue;

		token = reader.GetStringTrimmed();	// name
		shape.name = convert.from_bytes(token);

		if (shape.name.empty())
			continue;

		token = reader.GetString();					// type
		shape.type = convert.from_bytes(token);
		token = reader.GetString();
		shape.standard = convert.from_bytes(token);

		shape.h = reader.GetDouble();
		shape.b = reader.GetDouble();
		shape.s = reader.GetDouble();
		shape.t = reader.GetDouble();

		shape.R1 = reader.GetDouble();
		shape.R2 = reader.GetDouble();
		shape.X = reader.GetDouble();
		shape.Y = reader.GetDouble();

		shape.A = reader.GetDouble();
		shape.mass = reader.GetDouble();
		shape.R3 = reader.GetDouble();

		if (CheckShape(shape))
			shapes_T.push_back(shape);
	}
	reader.CloseFile();

	// Reading L-shapes
	shapes_L.clear();
	reader.SetFilePath(path + "L.txt");
	reader.OpenFile();

	while (reader.ReadLine())
	{
		if (reader.IsEmpty())
			continue;

		if (reader.StartsWith() == '#')
			continue;

		token = reader.GetStringTrimmed();	// name
		shape.name = convert.from_bytes(token);

		if (shape.name.empty())
			continue;

		token = reader.GetString();					// type
		shape.type = convert.from_bytes(token);
		token = reader.GetString();
		shape.standard = convert.from_bytes(token);

		shape.h = reader.GetDouble();
		shape.b = reader.GetDouble();
		shape.s = reader.GetDouble();
		shape.t = reader.GetDouble();

		shape.R1 = reader.GetDouble();
		shape.R2 = reader.GetDouble();
		shape.X = reader.GetDouble();
		shape.Y = reader.GetDouble();

		shape.A = reader.GetDouble();
		shape.mass = reader.GetDouble();
		shape.R3 = reader.GetDouble();

		if (CheckShape(shape))
			shapes_L.push_back(shape);
	}
	reader.CloseFile();

	// Reading L1-shapes
	shapes_L1.clear();
	reader.SetFilePath(path + "L1.txt");
	reader.OpenFile();

	while (reader.ReadLine())
	{
		if (reader.IsEmpty())
			continue;

		if (reader.StartsWith() == '#')
			continue;

		token = reader.GetStringTrimmed();	// name
		shape.name = convert.from_bytes(token);

		if (shape.name.empty())
			continue;

		token = reader.GetString();					// type
		shape.type = convert.from_bytes(token);
		token = reader.GetString();
		shape.standard = convert.from_bytes(token);

		shape.h = reader.GetDouble();
		shape.b = reader.GetDouble();
		shape.s = reader.GetDouble();
		shape.t = reader.GetDouble();

		shape.R1 = reader.GetDouble();
		shape.R2 = reader.GetDouble();
		shape.X = reader.GetDouble();
		shape.Y = reader.GetDouble();

		shape.A = reader.GetDouble();
		shape.mass = reader.GetDouble();
		shape.R3 = reader.GetDouble();

		if (CheckShape(shape))
			shapes_L1.push_back(shape);
	}
	reader.CloseFile();

	// Reading O-shapse
	/*
	shapes_O.clear();
	reader.SetFilePath(path + "O.txt");
	reader.OpenFile();

	while (reader.ReadLine())
	{
		if (reader.IsEmpty())
			continue;

		if (reader.StartsWith() == '#')
			continue;

		token = reader.GetStringTrimmed();	// name
		shape.name = convert.from_bytes(token);

		if (shape.name.empty())
			continue;

		token = reader.GetString();					// type
		shape.type = convert.from_bytes(token);
		token = reader.GetString();
		shape.standard = convert.from_bytes(token);

		shape.h = reader.GetDouble();
		shape.b = reader.GetDouble();
		shape.s = reader.GetDouble();
		shape.t = reader.GetDouble();

		shape.R1 = reader.GetDouble();
		shape.R2 = reader.GetDouble();
		shape.X = reader.GetDouble();
		shape.Y = reader.GetDouble();

		shape.A = reader.GetDouble();
		shape.mass = reader.GetDouble();
		shape.R3 = reader.GetDouble();

		std::wcout << L"Adding" << std::endl;
		shapes_O.push_back(shape);
	}
	reader.CloseFile();
	*/
}


bool ShapeReader::CheckShape(const Shape &s) const
{
	if ((s.h == 0) || (s.b == 0))
		return false;

	if (s.name == L"")
		return false;

	if ((s.t == 0) || (s.s == 0))
		return false;

	return true;
}