#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>

const int NUMBER_OF_UNO_CARDS = 108;
const int START_NUMBER_OF_CARDS_IN_HAND = 7;
const int NUMBER_OF_WILD_CARDS = 4;
const int NUMBER_OF_WILD_DRAW_FOUR_CARDS = 4;
const int NUMBER_OF_COLORS = 4;
const int NUMBER_OF_ZEROS = 1; //the number of zeros for each color
const int NUMBER_OF_NON_ZEROS = 4; //number of all cards that are not zero, for each color
const int MAX_NUMBER_OF_CARDS_PER_COLOR = ((NUMBER_OF_UNO_CARDS -
((NUMBER_OF_WILD_CARDS + NUMBER_OF_WILD_DRAW_FOUR_CARDS) +
(NUMBER_OF_ZEROS * NUMBER_OF_COLORS))) / NUMBER_OF_COLORS) + 1;
//all cards minus wild cards and one zero per color divided into 4
//plus one for the zero just removed

typedef char Colors;
typedef char Values;

struct unoCard
{
	Colors color;
	Values value;
};

unoCard unoDeck[NUMBER_OF_UNO_CARDS];
unoCard discardPile[NUMBER_OF_UNO_CARDS];
unoCard cardToPlayOn;
unoCard editableCardToPlayOn = cardToPlayOn;

int numberOfPlayers;
int playerTurn = 0;
int numberOfCardsInDeck = NUMBER_OF_UNO_CARDS;
int numberOfCardsInDiscard = 0;
int reversOn = 1; //one is for clockwise and -1 for counter-clockwise
std::vector< std::vector<unoCard> > playersHands;

//pre-game setup
void startGame();
void makeUnoDeck();
void displayRules();
void howManyPlayers();
void makePlayers();
void firstShuffleDeck();
void dealHand();
void startPlayer();

//game-play mechanics
void playGame();
void showTopCard();
void displayPlayCard();
void showCurrentPlayersCards();
bool isLegalMove(Colors color, Values value);
void drawCard();
void drawTwoCards();
void drawFourCards();
int findInHand(Colors color, Values value);
void changePlayCard(int index);
void nextPlayer();
void wildCard();
void makeMove();
bool isWinner();

void main()
{
	srand(time(NULL));

	startGame();

	//this tests to see if the output is correct
	/*makeUnoDeck();
	for (int i = 0; i < NUMBER_OF_UNO_CARDS; i++)
	{
	std::cout << unoDeck[i].color << unoDeck[i].value << std::endl;
	}

	system("Pause");*/
}

//pre-game setup
void startGame()
{
	displayRules();
	makeUnoDeck();
	firstShuffleDeck();
	howManyPlayers();
	if (numberOfPlayers == 0)
	{
		std::cout << "Have a nice day." << std::endl;
		return;
	}
	makePlayers();
	dealHand();
	startPlayer();
	playGame();
}

void makeUnoDeck()
{
	int i = 0;
	//red
	for (i = 0; i < MAX_NUMBER_OF_CARDS_PER_COLOR; i++)
	{
		unoDeck[i].color = 'R';
		if (i == 0)
		{
			unoDeck[i].value = '0';
		}

		int counter = i;
		counter = i % 12;
		switch (counter + 1)
		{
		case 1:
			unoDeck[i].value = (char)(counter + 48);
			break;
		case 2:
			unoDeck[i].value = (char)(counter + 48);
			break;
		case 3:
			unoDeck[i].value = (char)(counter + 48);
			break;
		case 4:
			unoDeck[i].value = (char)(counter + 48);
			break;
		case 5:
			unoDeck[i].value = (char)(counter + 48);
			break;
		case 6:
			unoDeck[i].value = (char)(counter + 48);
			break;
		case 7:
			unoDeck[i].value = (char)(counter + 48);
			break;
		case 8:
			unoDeck[i].value = (char)(counter + 48);
			break;
		case 9:
			unoDeck[i].value = (char)(counter + 48);
			break;
		case 10:
			unoDeck[i].value = 'D';
			break;
		case 11:
			unoDeck[i].value = 'S';
			break;
		case 12:
			unoDeck[i].value = 'R';
			break;
		}
	}
	//yellow
	for (i = MAX_NUMBER_OF_CARDS_PER_COLOR - 1; i < (MAX_NUMBER_OF_CARDS_PER_COLOR * 2); i++)
	{
		unoDeck[i].color = 'Y';
		if (i == 0)
		{
			unoDeck[i].value = (char)i;
		}
		else
		{
			int counter = i;
			counter = i % 12;
			switch (counter + 1)
			{
			case 1:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 2:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 3:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 4:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 5:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 6:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 7:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 8:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 9:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 10:
				unoDeck[i].value = 'D';
				break;
			case 11:
				unoDeck[i].value = 'S';
				break;
			case 12:
				unoDeck[i].value = 'R';
				break;
			}
		}
	}
	//Blue
	for (i = (MAX_NUMBER_OF_CARDS_PER_COLOR * 2) - 2; i < (MAX_NUMBER_OF_CARDS_PER_COLOR * 3); i++)
	{
		unoDeck[i].color = 'B';
		if (i == 0)
		{
			unoDeck[i].value = (char)i;
		}
		else
		{
			int counter = i;
			counter = i % 12;
			switch (counter + 1)
			{
			case 1:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 2:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 3:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 4:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 5:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 6:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 7:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 8:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 9:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 10:
				unoDeck[i].value = 'D';
				break;
			case 11:
				unoDeck[i].value = 'S';
				break;
			case 12:
				unoDeck[i].value = 'R';
				break;
			}
		}
	}
	//Green
	for (i = (MAX_NUMBER_OF_CARDS_PER_COLOR * 3) - 3; i < (MAX_NUMBER_OF_CARDS_PER_COLOR * 4); i++)
	{
		unoDeck[i].color = 'G';
		if (i == 0)
		{
			unoDeck[i].value = (char)i;
		}
		else
		{
			int counter = i;
			counter = i % 12;
			switch (counter + 1)
			{
			case 1:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 2:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 3:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 4:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 5:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 6:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 7:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 8:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 9:
				unoDeck[i].value = (char)(counter + 48);
				break;
			case 10:
				unoDeck[i].value = 'D';
				break;
			case 11:
				unoDeck[i].value = 'S';
				break;
			case 12:
				unoDeck[i].value = 'R';
				break;
			}
		}
	}
	//Wild
	int counter = 0;
	while (i < NUMBER_OF_UNO_CARDS)
	{
		if (counter < 4)//wild draw 4
		{
			unoDeck[i].color = 'W';
			unoDeck[i].value = '4';
		}
		else//wild
		{
			unoDeck[i].color = 'W';
			unoDeck[i].value = '0';
		}
		i++;
		counter++;
	}
}

void displayRules()
{
	std::cout << "This is a card game with 108 card." << std::endl;
	std::cout << "One can play one card at a time";
	std::cout << ", where the card can be of the same color or value." << std::endl;
	std::cout << "One cannot play a card after drawing: D stands for draw 2 ";
	std::cout << "and a W4 means a wild card and to draw 4 ";
	std::cout << "while W0 means a wild card with no draw" << std::endl;
	std::cout << "A card with the letter R on it means it reverces order";
	std::cout << " and an S stands for skip." << std::endl;
	std::cout << "The first character states what color, or if it's wild, that it belongs to";
	std::cout << ", and the secound character is its value" << std::endl;
	std::cout << "Up to 10 players can play." << std::endl;
	system("Pause");
	system("cls");
}

void howManyPlayers()
{
	std::cout << "How many people will be playing? ";
	std::cin >> numberOfPlayers;
	if (numberOfPlayers > 10)//tests to see if the number of players is less than 11
	{
		std::cout << "Too many people. \n Enter a new value." << std::endl;
		howManyPlayers();
	}
}

void makePlayers()
{
	playersHands.resize(numberOfPlayers);
}

void firstShuffleDeck()
{
	unoCard holder;
	int random;
	for (int i = NUMBER_OF_UNO_CARDS; i > 0; i--)
	{
		random = rand() % i + 1;
		holder = unoDeck[random];
		unoDeck[random] = unoDeck[i];
		unoDeck[i] = holder;
	}
}

void dealHand()
{
	int cardsOut = 0;
	for (int i = 0; i < numberOfPlayers; i++)
	{
		for (int j = 0; j < 7; j++)//the player starts with 7 cards
		{
			playersHands[i].push_back(unoDeck[0]);
			//to shift cards to the left
			for (int k = 0; k < numberOfCardsInDeck; k++)
			{
				unoDeck[k] = unoDeck[k + 1];
			}
			unoDeck[(numberOfCardsInDeck)-1].color = NULL;
			unoDeck[(numberOfCardsInDeck)-1].value = NULL;
			numberOfCardsInDeck--;
		}
	}
}

void startPlayer()
{
	playerTurn = rand() % numberOfPlayers;
	std::cout << "Player " << playerTurn + 1 << " goes first" << std::endl;
	system("Pause");
	system("cls");
}


//game-play mechanics
void playGame()
{
	bool winner = false;
	showTopCard();
	do
	{
		system("pause");
		displayPlayCard();
		showCurrentPlayersCards();
		makeMove();
		winner = isWinner();
		if (winner != true)
		{
			if (editableCardToPlayOn.value == 'S')
			{
				nextPlayer();
			}
			nextPlayer();
		}
		system("pause");
		system("cls");
	} while (winner == false);
	std::cout << "congratulations player " << numberOfPlayers;
}

void showTopCard()
{
	system("cls");
	cardToPlayOn = unoDeck[0];
	editableCardToPlayOn = cardToPlayOn;
	for (int k = 0; k < numberOfCardsInDeck; k++)
	{
		unoDeck[k] = unoDeck[k + 1];
	}
	unoDeck[(numberOfCardsInDeck)-1].color = NULL;
	unoDeck[(numberOfCardsInDeck)-1].value = NULL;
	numberOfCardsInDeck--;
	numberOfCardsInDiscard++;
	std::cout << "\t\t\t" << cardToPlayOn.color << cardToPlayOn.value << std::endl;
}

void displayPlayCard()
{
	system("cls");
	std::cout << "\t\t\t" << editableCardToPlayOn.color << editableCardToPlayOn.value << std::endl;
}

void showCurrentPlayersCards()
{
	for (int i = 0; i < playersHands[playerTurn].size(); i++)
	{
		std::cout << std::setw(5) << playersHands[playerTurn][i].color << playersHands[playerTurn][i].value;
	}
	std::cout << std::endl;
}

bool isLegalMove(Colors color, Values value)
{
	if (color == editableCardToPlayOn.color || value == editableCardToPlayOn.value
		|| color == 'W' || editableCardToPlayOn.color == 'W')
	{
		return true;
	}

	return false;
}

void drawCard()
{
	playersHands[playerTurn].push_back(unoDeck[0]);//this adds a card
												   //this removes the card from the deck
	for (int k = 0; k < numberOfCardsInDeck; k++)
	{
		unoDeck[k] = unoDeck[k + 1];
	}
	unoDeck[(numberOfCardsInDeck)-1].color = NULL;
	unoDeck[(numberOfCardsInDeck)-1].value = NULL;
	numberOfCardsInDeck--;
}
void drawTwoCards()//for a draw 2
{
	drawCard();
	drawCard();
}
void drawFourCards()//for a wild draw 4
{
	drawCard();
	drawCard();
	drawCard();
	drawCard();
}

int findInHand(Colors color, Values value)
{
	int index = -1;
	for (int i = 0; i < playersHands[playerTurn].size() && index == -1; i++)
	{
		if (playersHands[playerTurn][i].color == color && playersHands[playerTurn][i].value == value)
		{//does cin take numbers as char or int
			index = i;
		}
		else if (color == 'W')
		{
			index = 1;
		}
		else
		{
			index = -1;
		}
	}
	return index;
}

void changePlayCard(int index)
{
	discardPile[numberOfCardsInDiscard] = playersHands[playerTurn][index];//copies it to discard
	numberOfCardsInDiscard++;//increases card count in discard
	cardToPlayOn = playersHands[playerTurn][index];
	editableCardToPlayOn = cardToPlayOn;

	playersHands[playerTurn].erase(playersHands[playerTurn].begin()
		+ index);//removes this card from the hand
}

void nextPlayer()
{
	if (numberOfPlayers - 1 == playerTurn)
	{
		playerTurn = 0;
	}
	else
	{
		playerTurn += reversOn;
	}
}

void wildCard()
{
	char newColor;
	std::cout << "What collor do you want? ";
	std::cin >> newColor;
	std::cin.ignore(1024, '\n');

	if (newColor == 'r' || newColor == 'y' || newColor == 'b' || newColor == 'g')
	{
		newColor = (char)((int)newColor - 32);
	}

	editableCardToPlayOn.color = newColor;
	editableCardToPlayOn.value = 'W';
}

void makeMove()
{
	int positionInHand = 1;
	char color, value;

	std::cout << "What card would you like to play (if you cannot play enter DC)? ";
	std::cin >> color >> value;
	std::cin.ignore(1024, '\n');

	if ((color == 'D' || color == 'd') && (value == 'C' || value == 'c'))
	{
		drawCard();
		return;
	}
	//to make it case insensitive
	if (color == 'r')
	{
		color = 'R';
	}
	else if (color == 'y')
	{
		color = 'Y';
	}
	else if (color == 'g')
	{
		color = 'G';
	}
	else if (color == 'b')
	{
		color = 'B';
	}
	else if (color == 'w')
	{
		color = 'W';
	}
	if (value == 'r')
	{
		value = 'R';
	}
	else if (value == 'd')
	{
		value = 'D';
	}
	else if (value == 's')
	{
		value = 'S';
	}

	if (isLegalMove(color, value))
	{
		positionInHand = findInHand(color, value);
		if (positionInHand < 0)//checks to see if the input is in their hand
		{
			std::cout << "You do not have this card.\a" << std::endl;
			makeMove();
		}
		else
		{
			changePlayCard(positionInHand);
			if (value == 'D')
			{
				drawTwoCards();
			}
			else if (value == 'R')
			{
				reversOn *= -1;
			}
			else if (value == 'S')
			{
				nextPlayer();
			}
			else if (color == 'W')
			{
				wildCard();
				if (value == '4')
				{
					drawFourCards();
				}
			}
		}
	}
	else//the move is not legal
	{
		std::cout << "That is not a legal move.\a" << std::endl;
		makeMove();
	}
}

bool isWinner()
{
	if (playersHands[playerTurn].size() == 0)
	{
		return true;
	}
	return false;
}
