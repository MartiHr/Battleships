#include <iostream>

using namespace std;

enum ShipType {
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
	cout << "Please enter the size for both game fields and press ENTER to start: ";
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

		cout << '\t';

		for (int j = 0; j < size; j++)
		{
			cout << rightMatrix[i][j];
		}

		cout << endl;
	}
}

void placeAUnit(char** matrix, int size, int x, int y, ShipType unitType) {
	if (!matrix) {
		return;
	}
}

void showPlaceUnitsMessage(int boatsCount, int submarinesCount, int destroyersCount, int carriersCount) {
	cout << placeUnitsMeesage << boatsCount << " boats, "
		<< submarinesCount <<  " submarines, " 
		<< destroyersCount << " destroyers, "
		<< carriersCount << "and carriers."
		<< endl;
}

void placeUnits(char** matrix, int size, int boatsCount, int submarinesCount, int destroyersCount, int carriersCount) {
	if (!matrix) {
		return;
	}

	showPlaceUnitsMessage(boatsCount, submarinesCount,  destroyersCount, carriersCount);

	while (boatsCount != 0 && submarinesCount  && destroyersCount != 0 && carriersCount != 0)
	{

	}
}

int main()
{
	showLoadingScreen();

	// For better UX 
	promptUserToStartGame();

	int size = readSizeOfMatrix();
	showGameStartMessage();

	char** firstPlayerMatrix = new char* [size];
	char** secondPlayerMatrix = new char* [size];
	initializeMatrix(firstPlayerMatrix, size);
	initializeMatrix(secondPlayerMatrix, size);

	bool isGameFinished = false;
	bool firstPlayerTurn = true;
	while (!isGameFinished)
	{
		printBattlefiedlsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size);
		placeUnits(firstPlayerMatrix, size);
		placeUnits(secondPlayerMatrix, size);
	}

	freeMemoryMatrix(firstPlayerMatrix, size);
	freeMemoryMatrix(secondPlayerMatrix, size);
}