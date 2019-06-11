#include "pch.h"
#include "Ctwo_points.h"
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;


Spoint::Spoint()
{
}

Spoint::Spoint(double x, double y)
{
	m_dX_coordinate = x;
	m_dY_coordinate = y;
}

Ctwo_points::Ctwo_points()
{
	double a, b;
	//calculate the distance.
	a = pow(m_First_point.m_dX_coordinate - m_Second_point.m_dX_coordinate, 2);
	b = pow(m_First_point.m_dY_coordinate - m_Second_point.m_dY_coordinate, 2);
	m_distance = sqrt(a + b);
}

Ctwo_points::Ctwo_points(Spoint fir, Spoint sec)
{
	double a, b;
	m_First_point = fir;
	m_Second_point = sec;
		//calculate the distance.
	a = pow(fir.m_dX_coordinate - sec.m_dX_coordinate, 2);
	b = pow(fir.m_dY_coordinate - sec.m_dY_coordinate, 2);
	m_distance = sqrt(a + b);
}

Ctwo_points::~Ctwo_points()
{
}

double Ctwo_points::Get_distance()
{
	return m_distance;
}

void Ctwo_points::Print()
{
	cout << "the first point is: " << m_First_point.m_dX_coordinate << " " << m_First_point.m_dY_coordinate << endl;
	cout << "the second point is: " << m_Second_point.m_dX_coordinate << " " << m_Second_point.m_dY_coordinate << endl;
	cout << "their distance is: " << m_distance << endl;
}

