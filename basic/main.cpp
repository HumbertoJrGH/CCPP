#include <iostream>
#include <thread>
#include "celula.h"
#include <SFML/Graphics.hpp>

using namespace std;

// int recursive(int i)
// {
// 	if (i < 10)
// 	{
// 		cout << i << " + ";
// 		return i + recursive(i + 1);
// 	}
// 	else
// 	{
// 		cout << i << " = ";
// 		return i;
// 	}
// }

// void guessingGame()
// {
// 	srand(time(nullptr));
// 	const int min = 1;
// 	const int max = 100;
// 	const int secretNumber = rand() % (max - min + 1) + min;
// 	const int tries = 5;
// 	int remaining = tries;

// 	cout << "Guess the number!" << endl;
// 	cout << "Input a number between " << min << " and " << max << endl;
// 	cout << "You have " << tries << " chances. Good luck!" << endl;

// 	while (remaining > 0)
// 	{
// 		// cout << "\033[2J\033[1;1H";
// 		int guess;
// 		cout << "Tried " << tries - remaining << " times!" << endl;
// 		cout << "Input: ";
// 		cin >> guess;
// 		if (guess == secretNumber)
// 		{
// 			cout << "Success, you guessed the right number!" << endl;
// 			break;
// 		}
// 		else if (guess < secretNumber)
// 			cout << "Sorry, you guessed wrong, it was too low." << endl;
// 		else
// 			cout << "Sorry, you guessed wrong, it was too high." << endl;
// 		remaining--;
// 	}

// 	if (remaining == 0)
// 		cout << "You lost the game, the last secret number for guessing was: " << secretNumber << endl;
// }

// void mainThread()
// {
// 	cout << "Teste com thread em C++" << endl;
// 	cout << "Primeiro um teste com recursão" << endl;
// 	cout << "total: " << recursive(0) << endl;

// 	Celula *c = new Celula(1);

// 	cout << c->getValue() << endl;
// 	guessingGame();
// }

int main()
{
	// cout << "1º programa em C++" << endl;
	// thread one(mainThread);
	// one.join();

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works@");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}