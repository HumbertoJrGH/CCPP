#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;

struct Card
{
	string name;
	string meaning;
	string archetype;
	string element;
	string planet;
};

class Tarot
{
public:
	Tarot()
	{
		major = deckLoader("./cards.txt");
	}

	void CelticCross();
	void SimpleGame(int numCards)
	{
		cout << numCards << endl;
		vector<Card> deck = major;

		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		shuffle(deck.begin(), deck.end(), default_random_engine(seed));

		if (numCards <= 0 || numCards > deck.size())
		{
			cout << "Invalid card number.";
			return;
		}

		cout << "\nSimple game." << endl;
		for (int i = 0; i < numCards; ++i)
		{
			Card card = deck.back();
			deck.pop_back();
			cout << (i + 1) << ". " << card.name << ": " << card.meaning << endl;
			cout << card.element << " " << card.planet << endl;
		}
	}

private:
	vector<Card> major;

	void shuffleCards()
	{
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		shuffle(major.begin(), major.end(), default_random_engine(seed));
	}

	vector<Card> deckLoader(const string &filename)
	{
		vector<Card> deck;
		ifstream file(filename); // No need for .c_str() in modern C++
		if (!file.is_open())
		{
			cerr << "Error: Could not open " << filename << endl;
			return deck; // Return empty deck
		}

		string line;
		Card currentCard;
		bool inCardBlock = false;

		while (getline(file, line))
		{
			// Trim leading/trailing whitespace
			line.erase(0, line.find_first_not_of(" \t\r\n"));
			line.erase(line.find_last_not_of(" \t\r\n") + 1);

			if (line.empty())
			{
				// Blank line indicates end of a card block (if we were in one)
				if (inCardBlock)
				{
					deck.push_back(currentCard);
					currentCard = Card(); // Reset for next card
					inCardBlock = false;
				}
				continue; // Skip blank lines
			}

			// Ignore header lines that start with '---'
			if (line.rfind("---", 0) == 0)
			{ // C++11 way to check prefix
				continue;
			}

			if (!inCardBlock)
			{
				// First non-blank, non-header line starts a new card block (this is the name)
				currentCard.name = line;
				inCardBlock = true;
			}
			else
			{
				// Parse other fields based on prefix
				if (line.rfind("Meaning: ", 0) == 0)
				{
					currentCard.meaning = line.substr(string("Meaning: ").length());
				}
				else if (line.rfind("Archetype: ", 0) == 0)
				{
					currentCard.archetype = line.substr(string("Archetype: ").length());
				}
				else if (line.rfind("Element: ", 0) == 0)
				{
					currentCard.element = line.substr(string("Element: ").length());
				}
				else if (line.rfind("Planet: ", 0) == 0)
				{
					currentCard.planet = line.substr(string("Planet: ").length());
				}
				// Add more `else if` for other fields if you extend the struct
			}
		}

		// Add the last card if the file doesn't end with a blank line
		if (inCardBlock)
		{
			deck.push_back(currentCard);
		}

		file.close();
		return deck;
	}

	Card pick()
	{
		if (major.empty())
			throw runtime_error("Baralho vazio! Não há mais cartas para tirar.");
		Card card = major.back();
		major.pop_back();
		return card;
	}
};

int main()
{
	Tarot myTarot; // Cria uma instância do seu baralho de Tarot

	int escolha;
	do
	{
		cout << "\n--- Bem-vindo ao Sorteador de Tarot ---" << endl;
		cout << "Escolha um jogo:" << endl;
		cout << "1. Tiragem Simples (3 cartas)" << endl;
		cout << "2. Cruz Celta (10 cartas)" << endl;
		cout << "0. Sair" << endl;
		cout << "Sua escolha: ";
		cin >> escolha;

		switch (escolha)
		{
		case 1:
			myTarot.SimpleGame(3);
			break;
		case 2:
			cout << "not ready";
			break;
		case 0:
			cout << "Saindo do programa. Até a próxima!" << endl;
			break;
		default:
			cout << "Escolha inválida. Por favor, tente novamente." << endl;
		}
	} while (escolha != 0);

	return 0;
}
