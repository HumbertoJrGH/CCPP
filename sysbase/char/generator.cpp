#include <iostream>
#include <vector>
#include <random>

#include "character.cpp"

using namespace std;

class Generator
{
public:
	Generator(int x)
	{
		for (int i = 0; i < x; ++i)
			characterList.push_back(generateCharacter());
	}

	const vector<Character> &getCharacters() const { return characterList; }

private:
	vector<Character> characterList;

	Character generateCharacter()
	{
		random_device rd;
		mt19937 generator(rd());

		vector<string> maleNames = {"Alan", "Bernarde", "Charles", "Donnie", "Evan", "Fabrizio", "Gustave"};
		vector<string> femaleNames = {"Alice", "Bella", "Caroline", "Diana", "Eliane", "Fernanda", "Gabriela"};
		vector<string> fElfNames = {"Aaelar", "Belinar", "Celinar", "Delinar", "Evinar", "Farenar", "Garenar"};
		vector<string> mElfNames = {"Arenon", "Boulon", "Coelon", "Donon", "Eon", "Faelon", "Garenon"};
		vector<string> cElfNames = {"Aisin", "Bharin", "Cacin", "Dalinain", "Erin", "Faelin", "Gonin"};
		vector<string> lElfNames = {"Aela", "Baera", "Caoura", "Daianara", "Elara", "Foea", "Goaua"};

		vector<string> races = {"Human", "Elf", "Dwarf", "Orc", "Gnome"};
		vector<string> jobs = {"Warrior", "Mage", "Cleric", "Rogue", "Knight"};

		uniform_int_distribution<int> raceDist(0, races.size() - 1);
		uniform_int_distribution<int> jobDist(0, jobs.size() - 1);
		uniform_real_distribution<float> heightDist(140.0f, 220.0f);
		string race = races[raceDist(generator)];
		string name, gender;

		if (race == "Elf")
		{
			uniform_int_distribution<int> elfGenderDist(0, 3);
			int elfGender = elfGenderDist(generator);
			if (elfGender == 0)
			{
				name = mElfNames[generateIndex(mElfNames.size(), generator)];
				gender = "Male";
			}
			else if (elfGender == 1)
			{
				name = fElfNames[generateIndex(fElfNames.size(), generator)];
				gender = "Female";
			}
			else if (elfGender == 3)
			{
				name = cElfNames[generateIndex(cElfNames.size(), generator)];
				gender = "Ceresine";
			}
			else
			{
				name = lElfNames[generateIndex(cElfNames.size(), generator)];
				gender = "Lunine";
			}
		}
		else
		{
			uniform_int_distribution<int> genderDist(0, 1);
			int genderIdx = genderDist(generator);
			if (genderIdx == 0) // Male
			{
				name = maleNames[generateIndex(maleNames.size(), generator)];
				gender = "Male";
			}
			else // Female
			{
				name = femaleNames[generateIndex(femaleNames.size(), generator)];
				gender = "Female";
			}
		}

		return Character(name, gender, generateAge(), heightDist(generator), race, jobs[jobDist(generator)]);
	}

	int generateIndex(int size, mt19937 &generator)
	{
		uniform_int_distribution<int> dist(0, size - 1);
		return dist(generator);
	}

	int generateAge()
	{
		random_device rd;
		mt19937 generator(rd());

		// AGE WEIGTH - POP PYRAMID
		vector<pair<pair<int, int>, float>> weights = {
			 {{14, 20}, 0.40f},
			 {{21, 35}, 0.35f},
			 {{36, 50}, 0.15f},
			 {{51, 90}, 0.10f}};

		uniform_real_distribution<float> dist(0.0f, 1.0f);
		float r = dist(generator);
		float cumulative_prob = 0.0f;
		int age = -1;

		for (const auto &w : weights)
		{
			cumulative_prob += w.second;
			if (r <= cumulative_prob)
			{
				uniform_int_distribution<int> ageDist(w.first.first, w.first.second);
				age = ageDist(generator);
				break;
			}
		}
		return age;
	}
};