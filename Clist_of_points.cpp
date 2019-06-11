#include "pch.h"
#include "Clist_of_points.h"
#include <fstream>
using namespace std;

// compare two points by X/Y coordinate.
bool compare_x(const Spoint &a, const Spoint &b) { return a.m_dX_coordinate < b.m_dX_coordinate; }
bool compare_y(const Spoint &a, const Spoint &b) { return a.m_dY_coordinate < b.m_dY_coordinate; }

Clist_of_points::Clist_of_points()
{
}

Clist_of_points::Clist_of_points(int s, Spoint arr[])
{
		// set the list size and the points vector.
	m_size = s;
	for (int i = 0; i < m_size; i++)
	{
		m_points_vec.push_back(arr[i]);
	}
	sort_by_x();		//create the X sorted points vector.
	sort_by_Y();		//create the Y sorted points vector.
}

Clist_of_points::Clist_of_points(int s, std::vector<Spoint> vec)
{
	m_size = s;
	m_points_vec = vec;
	sort_by_x();
	sort_by_Y();
}

Clist_of_points::Clist_of_points(const char * file_name)
{
	int size = 0;
	double a, b;

	ifstream points_file(file_name);
	while (points_file >> a >> b)
	{
		size++;
		Spoint point(a, b);
		m_points_vec.push_back(point);
	}
	m_size = size;
	sort_by_x();		//create the X sorted points vector.
	sort_by_Y();		//create the Y sorted points vector.
}

Clist_of_points::~Clist_of_points()
{
}

Ctwo_points Clist_of_points::Find_closest_points()
{
	return Find_closest_points(m_sorted_points_vec_by_x, m_sorted_points_vec_by_y);
}

Ctwo_points Clist_of_points::Slow_find_closest_points()
{
	int i, j;
	double min_distance = std::numeric_limits<double>::max();
	Ctwo_points close_points;
	for (i = 0; i < m_size; i++)
	{
		for (j = i + 1; j < m_size; j++)
		{
			Ctwo_points t_p(m_points_vec[i], m_points_vec[j]);
			if (t_p.Get_distance() < min_distance)
			{
				close_points = t_p;
				min_distance = t_p.Get_distance();
			}
		}
	}
	return close_points;
}

Ctwo_points Clist_of_points::Find_closest_points(std::vector<Spoint> x_sorted, std::vector<Spoint> y_sorted)
{
			// set 'min' and 'max' to the min/max value possible for a double variable (the farthest possible points in the 2D space).
	Spoint a, b, c, max(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()), min(std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
	if (m_size <= 3)	// if there is just three or less points in the list - return the two closest points.
	{
		a = m_points_vec[0];
		b = m_points_vec[1];
		if (m_size < 3)		// if there is just two points - then return them.
		{
			return Ctwo_points(a, b);
		}
		c = m_points_vec[2];
		return Find_two_from_three_points(a, b, c);		// return the closet pair points.
	}

		// declare & initialize variables. 
	int i, j, right_size = floor(m_size / 2), left_size = ceil(m_size / 2), delta_distance_size = 0;
	double delta, new_delta, max_X_coordinate;
	Ctwo_points right_closet_points, left_closet_points, delta_distance_closet_points(max, min), finally_closet_points;
	std::vector<Spoint> right_vec, left_vec, delta_distance_vec;
	vector<Spoint>::iterator it, max_X_iter;

		// iterate over an half list - the (size/2) lowest x coordinates - and create the 'right vector'.
	for (it = m_sorted_points_vec_by_x.begin(); it != m_sorted_points_vec_by_x.begin() + right_size; it++)
	{
		right_vec.push_back(*it);
	}
	max_X_coordinate = (*it).m_dX_coordinate; // save the highest X coordinate for future use.
	max_X_iter = it;	// save a iterator to the point with the highest X coordinate for future use.
		// iterate over an half list - the (size/2) highest x coordinates - and create the 'left vector'.
	for (; it != m_sorted_points_vec_by_x.end(); it++)
	{
		left_vec.push_back(*it);
	}
		// create two lists of points - right & left - and then call recursively this method .
	Clist_of_points right(right_size, right_vec), left(left_size, left_vec);
	right_closet_points = right.Find_closest_points();
	left_closet_points = left.Find_closest_points();

		// find the points with the lowest distance in both lists - 'finally_closet_points' are the two closest points, 'delta' is the lowest distance.
	finally_closet_points = Min(right_closet_points, left_closet_points);
	delta = finally_closet_points.Get_distance();

		// iterate over all the points in the 'right_vec' which they are in a 'delta' distance from 'left_vec'.
		// then create the 'delta_distance_vec'.
	for (it = max_X_iter; (*it).m_dX_coordinate >= (max_X_coordinate - delta); it--)
	{
		delta_distance_vec.push_back(*it);
		delta_distance_size++;
		if (it == m_sorted_points_vec_by_x.begin())		// avoid "iterator out of range error".
		{
			break;
		}
	}
		// iterate over all the points in the 'left_vec' which they are in a 'delta' distance from 'right_vec'.
		// then create the 'delta_distance_vec'.
	for (it = max_X_iter + 1; (*it).m_dX_coordinate <= (max_X_coordinate + delta); it++)
	{
		delta_distance_vec.push_back(*it);
		delta_distance_size++;
		if (it == m_sorted_points_vec_by_x.end() - 1)	// avoid "iterator out of range error".
		{
			break;
		}
	}

		// if there are more then 15 points in the 'delta_distance_points'.
	if (delta_distance_size > 15)
	{
		cout << "there are " << delta_distance_size << " points in a delta distance from the pivot axis" << endl;
			// create a list from all the points with a "delta distance" from the border of the two lists.
		Clist_of_points delta_distance_points(delta_distance_size, delta_distance_vec);
			
			// iterate over the points sorted by their Y coordinates.
			// compare each point with the 15 next points and save the two closest points in 'delta_distance_closet_points'.
		for (i = 0, it = m_sorted_points_vec_by_y.begin(); i < delta_distance_size; i++, it++)
		{
			for (j = 1; (j < 16) || (i + j <= delta_distance_size) ; j++)
			{
				Ctwo_points tow_points((*it), (*(it + j)));
				delta_distance_closet_points = (delta_distance_closet_points.Get_distance() < tow_points.Get_distance()) ? delta_distance_closet_points : tow_points;
			}
		}
	}

		// compare the tow minimum distance and return the tow closest points.
	return Min(finally_closet_points, delta_distance_closet_points);
}

Ctwo_points Clist_of_points::Find_two_from_three_points(Spoint a, Spoint b, Spoint c)
{
	Ctwo_points min_d_e, min_d_f, d(a, b), e(a, c), f(b, c);		// create all three possible pairs of points.
	min_d_e = Min(d, e);	// find the section with the minimum distance of the two first point pairs.
	min_d_f = Min(d, f);	// find the section with the minimum distance of the first and lest point pairs.
	return Min(min_d_e, min_d_f);		// return the pair with the lowest distance.
}

int Clist_of_points::Get_size()
{
	return m_size;
}

void Clist_of_points::Print()
{
	vector<Spoint>::iterator it_1, it_2, it_3;
	it_1 = m_points_vec.begin();
	it_2 = m_sorted_points_vec_by_x.begin();
	it_3 = m_sorted_points_vec_by_y.begin();
	// prints the three vectors.
	cout << "the original array:,	 the sorted by X array:,	the sorted by Y array:" << endl;
	for (; it_1 != m_points_vec.end(); it_1++, it_2++, it_3++)
	{
		cout << (*it_1).m_dX_coordinate << "	" << (*it_1).m_dY_coordinate << "	||	 ";
		cout << (*it_2).m_dX_coordinate << "	" << (*it_2).m_dY_coordinate << "	||		";
		cout << (*it_3).m_dX_coordinate << "	" << (*it_3).m_dY_coordinate;
		cout << endl;
	}
	cout << endl;
}

void Clist_of_points::sort_by_x()
{
		// set the X sorted vector to the original vector and then sort it using the "compare_x" method.
	m_sorted_points_vec_by_x = m_points_vec;
	sort(m_sorted_points_vec_by_x.begin(), m_sorted_points_vec_by_x.end(), compare_x);
}

void Clist_of_points::sort_by_Y()
{
		// set the X sorted vector to the original vector and then sort it using the "compare_y" method.
	m_sorted_points_vec_by_y = m_points_vec;
	sort(m_sorted_points_vec_by_y.begin(), m_sorted_points_vec_by_y.end(), compare_y);
}
