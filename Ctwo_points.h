#pragma once

struct Spoint
{
	double m_dX_coordinate;
	double m_dY_coordinate;
	Spoint();
	Spoint(double x, double y);
};

class Ctwo_points
{
		// this class holds two points and calculate their distance.
	Spoint m_First_point;
	Spoint m_Second_point;
	double m_distance;
public:
	Ctwo_points();
	Ctwo_points(Spoint fir, Spoint sec);
	~Ctwo_points();
	double Get_distance();
	void Print();
};

