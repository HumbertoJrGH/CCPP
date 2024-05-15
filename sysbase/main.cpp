#include <iostream>
#include <cmath>

#include "geo.cpp"
#include "character.cpp"

using namespace std;

int main()
{
	// Geo sanFrancisco(37.7749, -122.4194);
	// Geo newYork(40.7128, -74.0059);
	// cout << "San Francisco to New York: " << newYork.calcAngle(sanFrancisco) << "°" << endl
	// 	  << "New York to San Francisco: " << sanFrancisco.calcAngle(newYork) << "°" << endl;


	Lista *l = new Lista();
	l->Mostrar();

	Player p;
	cout << "Digite o nome do player: ";
	string name;
	cin >> name;
	p.setName(name);
	l->InserirInicio(p);
	l->Mostrar();

	// l->InserirInicio(p);
	// l->Mostrar();

	return 0;
}