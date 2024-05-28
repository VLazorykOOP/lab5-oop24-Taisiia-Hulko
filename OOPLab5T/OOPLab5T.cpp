#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// базовий клас "Транспорт"
class Transport {
public:
    virtual void print() = 0;
    virtual ~Transport() {}
};

// похідний клас "Автомобіль"
class Car : public Transport {
private:
    string model; // модель автомобіля
public:
    Car(string m) : model(m) {}
    void print() override {
        cout << "This is a car, model: " << model << endl;
    }
    ~Car() {
        cout << "Car destructor" << endl;
    }
};

// похідний клас "Вантажівка"
class Truck : public Transport {
private:
    string model; // модель вантажівки
public:
    Truck(string m) : model(m) {}
    void print() override {
        cout << "This is a truck, model: " << model << endl;
    }
    ~Truck() {
        cout << "Truck destructor" << endl;
    }
};

// похідний клас "Корабель"
class Ship : public Transport {
private:
    string name; // назва корабля
public:
    Ship(string n) : name(n) {}
    void print() override {
        cout << "This is a ship, name: " << name << endl;
    }
    ~Ship() {
        cout << "Ship destructor" << endl;
    }
};

// похідний клас "Літак"
class Plane : public Transport {
private:
    string model; // модель літака
public:
    Plane(string m) : model(m) {}
    void print() override {
        cout << "This is a plane, model: " << model << endl;
    }
    ~Plane() {
        cout << "Plane destructor" << endl;
    }
};

// клас карти
class Card {
private:
    string suit; // масть
    string rank; // ранг
public:
    Card(string s, string r) : suit(s), rank(r) {}
    void print() const {
        cout << rank << " of " << suit << endl;
    }
    string getRank() const {
        return rank;
    }
    string getSuit() const {
        return suit;
    }
};

// клас колоди карт
class Deck {
protected:
    vector<Card> cards; // вектор карт
public:
    Deck() {}
    Deck(bool shuffle) {
        string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
        for (const string& suit : suits) {
            for (const string& rank : ranks) {
                cards.push_back(Card(suit, rank));
            }
        }
        if (shuffle) {
            shuffleDeck();
        }
    }
    void shuffleDeck() {
        srand(time(0));
        random_shuffle(cards.begin(), cards.end());
    }
    void printDeck() const {
        for (const Card& card : cards) {
            card.print();
        }
    }
    int getSize() const {
        return cards.size();
    }
};

// клас пасьянсу, що успадковує Deck
class Solitaire : public Deck {
public:
    Solitaire(bool shuffle) : Deck(shuffle) {}
    void removeSameColor() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < cards.size() - 2; ++j) {
                if (cards[j].getSuit() == cards[j + 2].getSuit()) {
                    if ((cards[j].getSuit() == "Hearts" || cards[j].getSuit() == "Diamonds") &&
                        (cards[j + 2].getSuit() == "Hearts" || cards[j + 2].getSuit() == "Diamonds")) {
                        cards.erase(cards.begin() + j, cards.begin() + j + 3);
                    }
                    else if ((cards[j].getSuit() == "Clubs" || cards[j].getSuit() == "Spades") &&
                        (cards[j + 2].getSuit() == "Clubs" || cards[j + 2].getSuit() == "Spades")) {
                        cards.erase(cards.begin() + j, cards.begin() + j + 3);
                    }
                }
            }
        }
    }
};

int main() {
    setlocale(LC_CTYPE, "ukr");
    int choice;

    cout << "Введіть 1 для запуску коду Транспорту або 2 для запуску коду Карт: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        Car car("Toyota");
        Truck truck("Ford");
        Ship ship("Titanic");
        Plane plane("Boeing 747");

        car.print();
        truck.print();
        ship.print();
        plane.print();
        break;
    }
    case 2: {
        Deck orderedDeck(false);
        cout << "Ordered deck:" << endl;
        orderedDeck.printDeck();
        cout << "Size: " << orderedDeck.getSize() << endl << endl;

        Deck shuffledDeck(true);
        cout << "Shuffled deck:" << endl;
        shuffledDeck.printDeck();
        cout << "Size: " << shuffledDeck.getSize() << endl << endl;

        Solitaire solitaireDeck(true);
        cout << "Solitaire deck:" << endl;
        solitaireDeck.removeSameColor();
        solitaireDeck.printDeck();
        cout << "Size: " << solitaireDeck.getSize() << endl;
        break;
    }
    default: {
        cout << "Невірний вибір" << endl;
        break;
    }
    }

    return 0;
}
