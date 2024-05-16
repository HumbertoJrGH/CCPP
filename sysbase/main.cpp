#include <iostream>
#include <cmath>

#include "geo.cpp"
#include "char/generator.cpp"

using namespace std;

void Geo()
{
	// Geo sanFrancisco(37.7749, -122.4194);
	// Geo newYork(40.7128, -74.0059);
	// cout << "San Francisco to New York: " << newYork.calcAngle(sanFrancisco) << "°" << endl
	// 	  << "New York to San Francisco: " << sanFrancisco.calcAngle(newYork) << "°" << endl;
}

int main()
{
	// Player p;
	// NPC npc;
	// Character c;

	cout << "How many? ";
	int input;
	cin >> input;
	cout << endl
		  << endl;

	Generator g(input);

	return 0;
}