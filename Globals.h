#pragma once
#include "Ctwo_points.h"
template <typename T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

Ctwo_points Min(Ctwo_points a, Ctwo_points b)
{
	return (a.Get_distance() < b.Get_distance()) ? a : b;
}