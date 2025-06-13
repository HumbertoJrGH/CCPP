#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

struct TarotCard
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
		init();
	}

	void CelticCross();
	void SimpleGame(int numCards)
	{
		cout << numCards << endl;
		vector<TarotCard> deck = major;
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
			TarotCard card = deck.back();
			deck.pop_back();
			cout << (i + 1) << ". " << card.name << ": " << card.meaning << endl;
			cout << card.element << " " << card.planet << endl;
		}
	}

private:
	vector<TarotCard> major;
	void init()
	{
		major.push_back({"O Louco", "Novos começos.", "Inocência", "", "Urano"});
		major.push_back({"O Mago", "Poder e Controle.", "Criação", "", "Mercúrio"});
		major.push_back({"A Sacerdotisa", "", "", "Lua"});
		major.push_back({"A Imperatriz", "", "", "Vênus"});
		major.push_back({"O Imperador", "", "", "Sol"});
		major.push_back({"O Hierofante", "", "Touro", "Vênus"});
		major.push_back({"Os Amantes", "", "", "Júpiter"});
		major.push_back({"A Carruagem", "", "", "Marte"});
		major.push_back({"A Força", "", "Libra", ""});
		major.push_back({"O Hermitão", "", "", "Saturno"});
		major.push_back({"A Roda da Forturna", "", "", "Júpiter"});
		major.push_back({"A Justiça", "", "Libra", ""});
		major.push_back({"O Enforcado", "", "", "Netuno"});
		major.push_back({"A Morte", "", "Escorpião", "Plutão"});
		major.push_back({"A Temperança", "", "", "Mercúrio"});
		major.push_back({"O Demônio", "", "", "Saturno"});
		major.push_back({"A Torre", "", "", "Mars"});
		major.push_back({"A Estrela", "", "", "Uranus"});
		major.push_back({"A Lua", "", "", "Netuno"});
		major.push_back({"O Sol", "", "", "Sol"});
		major.push_back({"O Julgamento", "", "", "Júpiter"});
		major.push_back({"O Mundo", "", "", "Saturno"});
	}

	void shuffleCards()
	{
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		shuffle(major.begin(), major.end(), default_random_engine(seed));
	}

	TarotCard pick()
	{
		if (major.empty())
			throw runtime_error("Baralho vazio! Não há mais cartas para tirar.");
		TarotCard card = major.back();
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