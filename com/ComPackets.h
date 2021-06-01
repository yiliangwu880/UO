#pragma once
#include "log_def.h"
#include "Geometry.h"

class CityInfo
{
public:
	string City;
	string Building;
	int Description;
	Point3D m_Location;
	CityInfo()
	{}
	CityInfo(string city, string building, int description, int x, int y, int z)
		:m_Location(x, y, z)
	{
		City = city;
		Building = building;
		Description = description;
		//Map = m;
	}

	CityInfo(string city, string building, int x, int y, int z)
		: CityInfo(city, building, 0, x, y, z)
	{ }



	int X() { return m_Location.X; }
	int Y() { return m_Location.Y; }
	int Z() { return m_Location.Z; }
	void X(int val) { m_Location.X=val; }
	void Y(int val) { m_Location.Y=val; }
	void Z(int val) { m_Location.Z=val; }

	const Point3D &Location(){ return m_Location; }
	//Map Map{ get; set; }
};

