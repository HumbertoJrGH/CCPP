#include <iostream>
#include <cmath>

#include "geo.cpp"

using namespace std;

int main()
{
	Geo sanFrancisco(37.7749, -122.4194);
	Geo newYork(40.7128, -74.0059);
	cout << "San Francisco to New York: " << newYork.calcAngle(sanFrancisco) << "°" << endl
		  << "New York to San Francisco: " << sanFrancisco.calcAngle(newYork) << "°" << endl;
	return 0;
}