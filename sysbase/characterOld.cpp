// #include <iostream>
// #include <cmath>

// using namespace std;

// class Character
// {
// public:
// 	Character()
// 	{
// 		// cout << "defina o nome do seu personagem:" << endl;
// 	}
// };

// class Player
// {
// private:
// 	string name;
// 	int id;

// public:
// 	Player(int prev = 0)
// 	{
// 		// Character();
// 		this->id = prev + 1;
// 	}
// 	void setName(string n) { name = n; }
// 	int getID() const { return id; }
// 	string getName() const { return name; }
// 	void printName() const { cout << name << endl; }
// 	void printId() { cout << hex << uppercase << this->id << endl; }
// 	virtual void teste() { cout << "faça seu teste" << endl; }
// };

// // CELULA DUPLA
// class Celula
// {
// private:
// 	Player p;

// public:
// 	Celula *next;
// 	Celula *prev;
// 	Celula(Player p)
// 	{
// 		this->next = this->prev = nullptr;
// 		this->p = p;
// 	}
// 	Celula()
// 	{
// 		this->next = this->prev = nullptr;
// 	}

// 	Player getValue() { return this->p; }
// };

// class Lista
// {
// private:
// 	Celula *primeiro;
// 	Celula *ultimo;

// public:
// 	Lista()
// 	{
// 		primeiro = nullptr;
// 		ultimo = primeiro;
// 	}

// 	void InserirInicio(Player p)
// 	{
// 		cout << "Inserindo player " << p.getID() << endl;

// 		Celula *nova = new Celula(p);
// 		cout << nova;
// 		if (primeiro == nullptr)
// 			primeiro = nova;
// 		cout << "primeiro: " << primeiro;
// 		nova->prev = primeiro;
// 		nova->next = ultimo;
// 		cout << "prev: " << nova->prev;
// 		cout << "next: " << nova->next;
// 		primeiro->next = ultimo;

// 		if (primeiro == ultimo)
// 			ultimo = nova;
// 		else
// 			nova->next->prev = nova;
// 		cout << "next: " << nova->next;

// 		nova = nullptr;
// 	}

// 	void Mostrar()
// 	{
// 		Celula *aux = primeiro;

// 		cout << "[ ";
// 		while (aux != nullptr)
// 		{
// 			cout << aux->getValue().getID() << ": " << aux->getValue().getName()
// 				  << ", ";
// 			aux = aux->next;
// 		}
// 		cout << " ]" << endl;
// 	}
// };