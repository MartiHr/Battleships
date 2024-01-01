#include <iostream>

using namespace std;

enum ShipType {
	Destroyed = 0,
	Boat = 2,
	Submarine = 3,
	Destroyer = 4,
	Carrier = 5
};

const char placeUnitsMeesage[] = "";

const char WATER_CHAR = '~';
const char BOAT_CHAR = 'b';
const char SUBMARINE_CHAR = 's';
const char destroyerChar = 'd';
const char carrierChar = 'c';
const char destroyedChar = 'X';
const char missedChar = 'O';
const char horizontalOrientation = 'h';
const char verticalOrientation = 'v';

void showLoadingScreen() {
	cout << "                                     # #  ( )" << endl;
	cout << "                                  ___#_#___|__" << endl;
	cout << "                              _  |____________|  _" << endl;
	cout << "                       _=====| | |            | | |==== _" << endl;
	cout << "                 =====| |.---------------------------. | |====" << endl;
	cout << "   <--------------------'   .  .  .  .  .  .  .  .   '--------------/" << endl;
	cout << "    \\                                                             /" << endl;
	cout << "     \\___________________________________________________________/" << endl;
	cout << "  wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" << endl;
	cout << "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" << endl;
	cout << "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" << endl;

	cout << "           _           _   _   _           _     _         " << endl;
	cout << "          | |         | | | | | |         | |   (_)        " << endl;
	cout << "          | |__   __ _| |_| |_| | ___  ___| |__  _ _ __   ___  " << endl;
	cout << "          | '_ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\ / __|  " << endl;
	cout << "          | |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |\\__ \\ " << endl;
	cout << "          |_.__/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/ |___/ " << endl;
	cout << "                                                  | |         " << endl;
	cout << "                                                  |_|         " << endl;
	cout << "" << endl;

}

void printWrongInputMessage() {
	cout << "" << endl;
}

void promptUserToStartGame() {
	cout << "Please enter the size for the game fields and press ENTER to start: ";
}

void showGameStartMessage() {
	cout << "Game started!" << endl;
}

void freeMemoryMatrix(char** matrix, int size) {
	if (!matrix) {
		return;
	}

	for (int i = 0; i < size; ++i) {
		delete[] matrix[i];
	}

	delete[] matrix;
}

int readSizeOfMatrix() {
	int size = 0;
	cin >> size;
	return size;
}

void printMatrix(char** matrix, int size) {
	if (!matrix)
	{
		return;
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j];
		}

		cout << endl;
	}
}

void initializeMatrix(char** matrix, int size) {
	if (!matrix) {
		return;
	}

	for (int i = 0; i < size; i++)
	{
		matrix[i] = new char[size];

		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = WATER_CHAR;
		}
	}
}

void printBattlefiedlsSideBySide(char** leftMatrix, char** rightMatrix, int size) {
	if (!leftMatrix || !rightMatrix) {
		return;
	}

	for (int i = 0; i < size; i++)
	{

		for (int j = 0; j < size; j++)
		{
			cout << leftMatrix[i][j];
		}

		// Print a tabular
		cout << '\t';

		for (int j = 0; j < size; j++)
		{
			cout << rightMatrix[i][j];
		}

		cout << endl;
	}
}

bool checkCoordinateIsInside(int coordinate, int size) {
	return (coordinate >= 0 && coordinate < size);
}

void placeSymbols(char** matrix, int unitLength, char orientation, int x, int y, char placeSymbol) {
	if (orientation == verticalOrientation) {
		int lastXCoordinate = unitLength + x;

		for (int i = x; i < lastXCoordinate; i++)
		{
			matrix[i][y] = BOAT_CHAR;
		}
	}
	else if (orientation == horizontalOrientation) {
		int lastYCoordinate = unitLength + y;

		for (int i = y; i < lastYCoordinate; i++)
		{
			matrix[x][i] = BOAT_CHAR;
		}
	}
}

// return a boolean and validate coordinates inside
bool placeUnit(char** matrix, int size, int x, int y, char orientation, ShipType unitType) {
	if (!matrix) {
		return false;
	}

	int unitLength = (int)unitType;

	switch (unitType)
	{
	case Boat:
		placeSymbols(matrix, unitLength, orientation, x, y, BOAT_CHAR);
	case Submarine:
		placeSymbols(matrix, unitLength, orientation, x, y, SUBMARINE_CHAR);
		break;
	case Destroyer:
		placeSymbols(matrix, unitLength, orientation, x, y, destroyedChar);
		break;
	case Carrier:
		placeSymbols(matrix, unitLength, orientation, x, y, carrierChar);
		break;
	case Destroyed:
		placeSymbols(matrix, unitLength, orientation, x, y, destroyedChar);
		break;
	default:
		break;
	}

	return true;
}

void showPlaceUnitsMessage(int boatsCount, int submarinesCount, int destroyersCount, int carriersCount, bool isFirstPlayer) {
	cout << "The " << (isFirstPlayer ? "first" : "second")
		<< " player should place their units : "
		<< boatsCount << " boats, "
		<< submarinesCount << " submarines, "
		<< destroyersCount << " destroyers, "
		<< "and " << carriersCount << " carriers."
		<< endl;
}

bool isOrientationValid(char orientation) {
	return (orientation == verticalOrientation || orientation == horizontalOrientation);
}

void placeUnits(char** matrix, int size, bool isFirstPlayer) {
	if (!matrix) {
		return;
	}

	int boatsCount = 1;
	int submarinesCount = 1;
	int destroyersCount = 1;
	int carriersCount = 1;

	while (boatsCount != 0 || submarinesCount != 0 || destroyersCount != 0 || carriersCount != 0) {
		showPlaceUnitsMessage(boatsCount, submarinesCount, destroyersCount, carriersCount, isFirstPlayer);

		cout << "Enter type of unit : ";
		char unitType = ' ';
		cin >> unitType;

		cout << "Enter orientation (h for horizontal, v - for vertical): ";
		char orientation = ' ';
		cin >> orientation;
		while (!isOrientationValid(orientation)) {
			cout << "Wrong orientation input, enter orientation again : ";
			cin >> orientation;
		}

		//TODO: validate if coordinates have been already shot
		int startX = -1;
		cout << "Enter start x coordinate : ";
		cin >> startX;
		while (!checkCoordinateIsInside(startX, size)) {
			cout << "Coordinate outside of board, enter start x coordinate again : ";
			cin >> startX;
		}

		cout << "Enter start y coordinate: ";
		int startY = -1;
		cin >> startY;
		while (!checkCoordinateIsInside(startY, size)) {
			cout << "Coordinate outside of board, enter start y coordinate again : ";
			cin >> startY;
		}

		switch (unitType) {
		case BOAT_CHAR:
			if (placeUnit(matrix, size, startX, startY, orientation, ShipType::Boat)) {
				boatsCount--;
				printMatrix(matrix, size);
			}
			break;
		case SUBMARINE_CHAR:
			if (placeUnit(matrix, size, startX, startY, orientation, ShipType::Submarine))
			{
				submarinesCount--;
				printMatrix(matrix, size);
			}
			break;
		case destroyerChar:
			if (placeUnit(matrix, size, startX, startY, orientation, ShipType::Destroyer)) {
				destroyersCount--;
				printMatrix(matrix, size);
			}
			break;
		case carrierChar:
			if (placeUnit(matrix, size, startX, startY, orientation, ShipType::Carrier))
			{
				carriersCount--;
				printMatrix(matrix, size);
			}
			break;
		default:
			break;
		}
	}
}

void startGame(char** firstPlayerMatrix, char** secondPlayerMatrix, int size) {
	if (!firstPlayerMatrix || !secondPlayerMatrix)
	{
		return;
	}

	bool isGameFinished = false;
	bool firstPlayerTurn = true;

	// Show the board
	printBattlefiedlsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size);

	const bool IT_IS_FIRST_PLAYER = true;
	// Place units for first player
	placeUnits(firstPlayerMatrix, size, IT_IS_FIRST_PLAYER);

	// Place units for second player
	placeUnits(secondPlayerMatrix, size, !IT_IS_FIRST_PLAYER);

	// Show the board
	printBattlefiedlsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size);

	/*while (!isGameFinished) {

	}*/
}

int main()
{
	showLoadingScreen();

	// For better UX 
	promptUserToStartGame();

	// Get the size of board
	int size = readSizeOfMatrix();
	showGameStartMessage();

	// Initialize the board
	char** firstPlayerMatrix = new char* [size];
	char** secondPlayerMatrix = new char* [size];
	initializeMatrix(firstPlayerMatrix, size);
	initializeMatrix(secondPlayerMatrix, size);

	// Start the game
	startGame(firstPlayerMatrix, secondPlayerMatrix, size);

	freeMemoryMatrix(firstPlayerMatrix, size);
	freeMemoryMatrix(secondPlayerMatrix, size);
}