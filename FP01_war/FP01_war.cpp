/**
  Brian Cox and Cody Auen
  coxb and auenc

  L07: War Card Game

  In this lab we will be recreating the card game by the name of War.
  The rules will be the same as the original besides one change.
  The cards will be from 0-9 instead of the regular 2-10 and face cards.
 */

#include <iostream> 
#include <algorithm>    // has shuffle
#include <vector> 
#include <random>
#include <chrono>
#include <stack>
#include <queue>
#include <deque>

using namespace std;


class Getrandom {
	/** Uses <random> and <chrono> from C++11 to return a random integer in range [1..size] */
public:
	Getrandom(int size) {
		auto seed = chrono::system_clock::now().time_since_epoch().count(); //gets a new seed for the randomness
		default_random_engine generator(seed);			//seeds our randomness
		uniform_int_distribution<int> intdist(1, size); //a distibution to make each in-range integer equally likely
		self_rand_int_ = intdist(generator);			//generates the randme number
	}
	int roll() {
		return self_rand_int_;
	}
private:
	int self_rand_int_;
};


class War {
	/**
	The entire card game of War and its functions
	*/
public:
	War() {
		// This code makes the 5 decks
		newdecks.reserve(125);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				newdecks.push_back(j);
			}
		}
		// This code gets a time-based seed for randomness
		unsigned seed = std::chrono::system_clock::now()
			.time_since_epoch()
			.count();
		//This code shuffles
		shuffle(newdecks.begin(), newdecks.end(), std::default_random_engine(seed));
	}

	void deal() {
		for (int i = 0; i < 25; i++) {
			myDeck.push(newdecks.back());
			newdecks.pop_back();
			comDeck.push(newdecks.back());
			newdecks.pop_back();
		}
	}



	void make_move() {
		char stop;
		while (!myDeck.empty() && !comDeck.empty()) {
			rMyCard();
			rComCard();
			display();
			compare();
		}
		while (game_on == true) {

			if (myDeck.empty() && myStorage.empty()) {
				cout << "You lost the game!" << endl;
				game_on = false;
				cin >> stop;
			}
			else if (comDeck.empty() && comStorage.empty()) {
				cout << "You win the game!" << endl;
				game_on = false;
				cin >> stop;
			}
			else if (myDeck.empty() && !myStorage.empty()) {
				move_myStorage();
			}
			else if (comDeck.empty() && !comStorage.empty()) {
				move_comStorage();
			}
		}

	}

	int rMyCard() {
		if (myDeck.empty() && game_on == true) {
			move_myStorage();
			rMyCard();
		}
		else {
			myCard = myDeck.top();
			myDeck.pop();
		}
		return myCard;
	}

	void move_myStorage() {
		while (!myStorage.empty()) {
			int z = myStorage.back();
			myStorage.pop_back();
			myDeck.push(z);
		}
		if (myStorage.empty()) {
			make_move();
		}
	}

	int rComCard() {
		if (myDeck.empty() && game_on == true) {
			move_comStorage();
			rComCard();
		}
		else {
			comCard = comDeck.top();
			comDeck.pop();
		}
		return comCard;
	}

	void move_comStorage() {
		while (!comStorage.empty()) {
			int z = comStorage.back();
			comStorage.pop_back();
			comDeck.push(z);
		}
		if (comStorage.empty()) {
			make_move();
		}
	}

	int display() {
		cout << endl;
		cout << "Your card: " << myCard << endl;
		cout << "Opponent card: " << comCard << endl;
		return myCard, comCard;
	}

	void compare() {
		if (myCard > comCard) {
			iWinRound();
		}
		else if (comCard > myCard) {
			comWinRound();
		}
		else if (comCard == myCard) {
			cout << "You've entered WAR!!" << endl;
			WAR();
		}
	}

	void iWinRound() {
		if (in_WAR == false) {
			myStorage.push_front(myCard);
			myStorage.push_front(comCard);
		}
		else {
			myStorage.push_front(myCard);
			myStorage.push_front(comCard);
			while (!lootPile.empty()) {
				int z = lootPile.back();
				lootPile.pop_back();
				myStorage.push_front(z);
			}
			in_WAR = false;
		}
		cout << "You win this round! :)" << endl;
		cout << endl;
		cout << "Press enter to continue" << endl;
		cin.ignore();
	}

	void comWinRound() {
		if (in_WAR == false) {
			comStorage.push_front(myCard);
			comStorage.push_front(comCard);
		}
		else {
			comStorage.push_front(myCard);
			comStorage.push_front(comCard);
			while (!lootPile.empty()) {
				int z = lootPile.back();
				lootPile.pop_back();
				comStorage.push_front(z);
			}
			in_WAR = false;
		}
		cout << "You lose this round! :(" << endl;
		cout << "Press enter to continue" << endl;
		cin.ignore();
	}

	/*void test() {
		int q = comDeck.size();
		int r = myDeck.size();
		int s = myStorage.size();
		int t = comStorage.size();
		cout << endl;
		cout << "Your deck: " << endl;
		for (int c = 0; c < r; c++) {
			cout << myDeck.top() << endl;
			myDeck.pop();
		}
		cout << endl;
		cout << "Your storage: " << endl;
		for (int a = 0; a < s; a++){
			cout << myStorage.front() << endl;
			myStorage.pop_front();
		}
		cout << endl;
		cout << "Com Deck: " << endl;
		for (int d = 0; d < q; d++) {
			cout << "Com Deck: " << comDeck.top() << endl;
			comDeck.pop();
		}
		cout << endl;
		cout << "Com Storage: " << endl;
		for (int b = 0; b < t; b++) {
			cout << comStorage.front() << endl;
			comStorage.pop_front();

		}
		cout << endl;
	}*/ // TEST

	void WAR() {
		//initiates WAR
		if (game_on == true) {
			in_WAR = true;
			lootPile.push_front(myCard);
			lootPile.push_front(comCard);
			rMyCard();
			rComCard();
			compare();
		}
	}



private:
	vector<int> newdecks;
	stack<int> myDeck;
	stack<int> comDeck;
	deque<int> myStorage;
	deque<int> comStorage;
	deque<int> lootPile;
	bool in_WAR = false;
	bool game_on = true;
	int myCard;
	int comCard;

}; //a semi colon must end every C++ class declaration.

//---------------------------------------------------------------------
// main begins here

int main() {
	char stopme;

	War game;
	game.deal();
	game.make_move();



	cin >> stopme; //holds open the window in some cases
	return 0;
}



