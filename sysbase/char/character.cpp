#include <iostream>

using namespace std;

class Character
{
public:
	Character()
	{
		cout << "created a new character" << endl;
	}

	Character(string name, string gender, int age, float height, string race, string job)
	{
		cout << name << endl
			  << gender << " " << race << " " << job << endl
			  << age << endl
			  << height << "cm" << endl
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