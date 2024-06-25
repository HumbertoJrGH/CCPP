#include <iostream>
#include <iomanip>

using namespace std;

class Character
{
public:
	Character()
	{
		cout << "created a new character" << endl;
	}

	Character(string name, string surname, string gender, int age, float height, string race, string job)
	{
		cout << name << " " << surname << endl
			  << gender << " " << race << " " << job << endl
			  << age << endl
			  << fixed << std::setprecision(2) << height << "cm" << endl
			  << endl;
		this->name = name;
		this->gender = gender;
		this->age = age;
		this->height = height;
		this->race = race;
		this->job = job;
	}

private:
	string name;
	string gender;
	int age;
	float height;
	string race;
	string job;
};

class NPC : Character
{
public:
	NPC()
	{
		cout << "of the type NPC" << endl
			  << endl;
	}
};

class Player : Character
{
public:
	Player()
	{
		cout << "of the type Player" << endl
			  << endl;
	}
};