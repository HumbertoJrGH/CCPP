
#include <iostream>
#include <vector>

using namespace std;

class Race
{
public:
	Race()
	{
		cout << "Raça!" << endl;
	}
};

class Elf : Race
{
private:
	Element tipo;

public:
	Elf() : tipo("a")
	{
		cout << "Elfo?";
	}
};

class Elements
{
private:
	vector<Element> ElementList;

public:
	Elements()
	{
		ElementList.push_back(Element("Neutral"));
		ElementList.push_back(Element("Spirit"));
		ElementList.push_back(Element("Fire"));
		ElementList.push_back(Element("Water"));
		ElementList.push_back(Element("Light"));
		ElementList.push_back(Element("Dark"));
		ElementList.push_back(Element("Air"));
		ElementList.push_back(Element("Earth"));
		ElementList.push_back(Element("Life"));
		ElementList.push_back(Element("Death"));
	}

	void printElements() const
	{
		for (const auto &element : ElementList)
		{
			cout << element.getName() << endl;
		}
	}
};

class Element
{
private:
	string Name;

public:
	Element(string name) : Name(name) {}

	string getName() const
	{
		return this->Name;
	}
};