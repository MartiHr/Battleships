#include <iostream>

using namespace std;

enum ShipType {
	Destroyed = 0,
	Boat = 2,
	Submarine = 3,
	Destroyer = 4,
	Carrier = 5
};

const char placeUnitsMeesage[] = "The current player should place their units: ";

const char waterChar = '~';
const char boatChar = 'b';
const char submarineChar = 's';
const char destroyerChar = 'd';
const char carrierChar = 'c';
const char destroyedChar = 'c';
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
			matrix[i][j] = waterChar;
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


// return a boolean and validate coordinates inside
bool placeUnit(char** matrix, int size, int x, int y, char orientation, ShipType unitType) {
	if (!matrix) {
		return false;
	}

	switch (unitType)
	{
	case Boat:
		if (orientation == horizontalOrientation)
		{
			for (int i = 0; i < (int)unitType; i++)
			{

			}
		}
		matrix[firstX][firstY] = boatChar;
		break;
	case Submarine:
		matrix[firstX][firstY] = submarineChar;
		break;
	case Destroyer:
		matrix[firstX][firstY] = destroyedChar;
		break;
	case Carrier:
		matrix[firstX][firstY] = carrierChar;
		break;
	case Destroyed:
		matrix[firstX][firstY] = destroyedChar;
		break;
	default:
		break;
	}

	return true;
}

void showPlaceUnitsMessage(int boatsCount, int submarinesCount, int destroyersCount, int carriersCount) {
	cout << placeUnitsMeesage << boatsCount << " boats, "
		<< submarinesCount << " submarines, "
		<< destroyersCount << " destroyers, "
		<< "and " << carriersCount << " carriers."
		<< endl;
}

void placeUnits(char** matrix, int size) {
	if (!matrix) {
		return;
	}

	int boatsCount = 1;
	int submarinesCount = 1;
	int destroyersCount = 1;
	int carriersCount = 1;

	while (boatsCount != 0 && submarinesCount && destroyersCount != 0 && carriersCount != 0) {
		showPlaceUnitsMessage(boatsCount, submarinesCount, destroyersCount, carriersCount);

		cout << "Enter type of unit : ";
		char unitType = ' ';
		cin >> unitType;

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
		case boatChar:
			if (placeUnit(matrix, size, startX, startY, 'h', ShipType::Boat)) {
				boatsCount--;
			}
			break;
		case submarineChar:
		
			placeUnit(matrix, size, startX, startY, 'h', ShipType::Submarine);
			submarinesCount--;
			break;
		case destroyerChar:
			if (true) {

			}
			placeUnit(matrix, size, startX, startY, 'h', ShipType::Destroyer);
			destroyersCount--;
			break;
		case carrierChar:
			placeUnit(matrix, size, startX, startY, 'h', ShipType::Carrier);
			carriersCount--;
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

	// Place units for first player
	placeUnits(firstPlayerMatrix, size);

	// Place units for second player
	placeUnits(secondPlayerMatrix, size);

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