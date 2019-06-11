#pragma once
#include "Ctwo_points.h"
#include "Globals.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>


class Clist_of_points
{
	int m_size;
	std::vector<Spoint> m_points_vec;		// points vector.
	std::vector<Spoint> m_sorted_points_vec_by_x;		// points vector sorted by X coordinate.
	std::vector<Spoint> m_sorted_points_vec_by_y;		// points vector sorted by Y coordinate.
	void sort_by_x();		// sorted by X coordinate.
	void sort_by_Y();		// sorted by Y coordinate.
			// find the two closest points, gets 2 points vectors sorted by their coordinates.
	Ctwo_points Find_closest_points(std::vector<Spoint> x_sorted, std::vector<Spoint> y_sorted);
			// returns two closest from three points.
	Ctwo_points Find_two_from_three_points(Spoint a, Spoint b, Spoint c);
public:
	Clist_of_points();
	Clist_of_points(int s, Spoint arr[]);
	Clist_of_points(int s, std::vector<Spoint> vec);
	Clist_of_points(const char* file_name);		// constructor to read the points from a file.
	~Clist_of_points();
			// find the two closest points in the all list.
	Ctwo_points Find_closest_points();
	Ctwo_points Slow_find_closest_points();		// find the two closest points with O(n^2) complexity.
	int Get_size();		// return the size of the list.
	void Print();
};


