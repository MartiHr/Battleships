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

const int MIN_SIZE = 3;
const int MAX_SIZE = 50;
const char WATER_CHAR = '~';
const char BOAT_CHAR = 'b';
const char SUBMARINE_CHAR = 's';
const char DESTROYER_CHAR = 'd';
const char CARRIER_CHAR = 'c';
const char DESTROYED_CHAR = 'X';
const char MISSED_CHAR = 'O';
const char HORIZONTAL_ORIENTATION = 'h';
const char VERTICAL_ORIENTATION = 'v';

void showLoadingScreen() {
	cout <<
		"                                     # #  ( )\n"
		"                                  ___#_#___|__\n"
		"                              _  |____________|  _\n"
		"                       _=====| | |            | | |==== _\n"
		"                 =====| |.---------------------------. | |====\n"
		"   <--------------------'   .  .  .  .  .  .  .  .   '--------------/\n"
		"    \\                                                             /\n"
		"     \\___________________________________________________________/\n"
		"  wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
		"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
		"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
    "          _           _   _   _           _     _         \n"
    "         | |         | | | | | |         | |   (_)        \n"
    "         | |__   __ _| |_| |_| | ___  ___| |__  _ _ __   ___  \n"
    "         | '_ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\ / __|  \n"
    "         | |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |\\__ \\ \n"
    "         |_.__/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/ |___/ \n"
    "                                                 | |         \n"
    "                                                 |_|         \n"
		"\n";
}

void printWrongInputMessage() {
	cout << "" << endl;
}

void promptUserToStartGame() {
	cout << "Please enter the size for the game " << "["<< MIN_SIZE << ", " << MAX_SIZE << "]" 
		<< " fields and press ENTER to start: ";
}

void showGameStartMessage() {
	const char gameStartedMessage[] = "Game started!\n";
	cout << gameStartedMessage << endl;
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
	const char POSITIVE_NUMBER_MESSAGE[] = "Please enter a positive number.\n";
	const char INVALID_INPUT_MESSAGE[] = "Invalid input. Please enter a number : ";

	int size;
	while (true) {
		if (std::cin >> size) {
			if (size > 0) {
				break;
			}
			else {
				std::cout << POSITIVE_NUMBER_MESSAGE;
			}
		}
		else {
			std::cin.clear(); // Clear the fail state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
			cout << INVALID_INPUT_MESSAGE;
		}
	}
	return size;
}

void printMatrix(char** matrix, int size) {
	if (!matrix) {
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

	for (int i = 0; i < size; i++) {
		matrix[i] = new char[size];

		for (int j = 0; j < size; j++) {
			matrix[i][j] = WATER_CHAR;
		}
	}
}

void printBattlefiedlsSideBySide(char** leftMatrix, char** rightMatrix, int size) {
	if (!leftMatrix || !rightMatrix) {
		return;
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << leftMatrix[i][j];
		}

		// Print spacing
		cout << "\t\t\t\t\t";

		for (int j = 0; j < size; j++) {
			cout << rightMatrix[i][j];
		}

		cout << endl;
	}
}

bool checkCoordinateIsInside(int coordinate, int size) {
	return (coordinate >= 0 && coordinate < size);
}

bool placeSymbols(char** matrix, int unitLength, char orientation, int x, int y, char placeSymbol) {
	if (!matrix)
	{
		return false;
	}

	if (orientation == VERTICAL_ORIENTATION) {
		int lastXCoordinate = unitLength + x;

		for (int i = x; i < lastXCoordinate; i++) {
			matrix[i][y] = placeSymbol;
		}
	}
	else if (orientation == HORIZONTAL_ORIENTATION) {
		int lastYCoordinate = unitLength + y;

		for (int i = y; i < lastYCoordinate; i++) {
			matrix[x][i] = placeSymbol;
		}
	}

	return true;
}

bool checkOverlap(char** matrix, int unitLength, char orientation, int x, int y) {
	if (!matrix) {
		return false;
	}

	if (orientation == VERTICAL_ORIENTATION) {
		int lastXCoordinate = unitLength + x;

		// Check if placement is possible
		for (int i = x; i < lastXCoordinate; i++) {
			if (matrix[i][y] != WATER_CHAR) {
				return true;
			}
		}
	}
	else if (orientation == HORIZONTAL_ORIENTATION) {
		int lastYCoordinate = unitLength + y;

		// Check if placement is possible
		for (int i = y; i < lastYCoordinate; i++) {
			if (matrix[x][i] != WATER_CHAR) {
				return true;
			}
		}
	}

	return false;
}

// return a boolean and validate coordinates inside
bool placeUnit(char** matrix, int size, int x, int y, char orientation, ShipType unitType) {
	if (!matrix) {
		return false;
	}

	int unitLength = (int)unitType;

	// Check for overlapping
	if (unitType != Destroyed && checkOverlap(matrix, unitLength, orientation, x, y)) {
		return false;
	}

	switch (unitType)
	{
		case Boat:
			placeSymbols(matrix, unitLength, orientation, x, y, BOAT_CHAR);
			break;	
		case Submarine:
			placeSymbols(matrix, unitLength, orientation, x, y, SUBMARINE_CHAR);
			break;
		case Destroyer:
			placeSymbols(matrix, unitLength, orientation, x, y, DESTROYER_CHAR);
			break;
		case Carrier:
			placeSymbols(matrix, unitLength, orientation, x, y, CARRIER_CHAR);
			break;
		case Destroyed:
			placeSymbols(matrix, unitLength, orientation, x, y, DESTROYED_CHAR);
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
	return (orientation == VERTICAL_ORIENTATION || orientation == HORIZONTAL_ORIENTATION);
}

void readStartCoordinates(int& startX, int& startY, int size) {
	cout << "Enter start x coordinate : ";
	cin >> startX;
	while (!checkCoordinateIsInside(startX, size)) {
		cout << "Coordinate outside of board, enter start x coordinate again : ";
		cin >> startX;
	}

	cout << "Enter start y coordinate: ";
	cin >> startY;
	while (!checkCoordinateIsInside(startY, size)) {
		cout << "Coordinate outside of board, enter start y coordinate again : ";
		cin >> startY;
	}
}

void readOrientation(char& orientation) {
	cout << "Enter orientation (h for horizontal, v - for vertical): ";
	cin >> orientation;
	while (!isOrientationValid(orientation)) {
		cout << "Wrong orientation input, enter orientation again (h for horizontal, v - for vertical) : ";
		cin >> orientation;
	}
}

void readUnitType(char unitType) {
	cout << "Enter type of unit - b for (b)oat, (s)ubmarine, (d)estroyer, (c)arrier : ";
	cin >> unitType;
	while (unitType != BOAT_CHAR && unitType != SUBMARINE_CHAR && unitType != DESTROYER_CHAR && unitType != CARRIER_CHAR)
	{
		cout << "Wrong unit, enter type of unit - b for (b)oat, (s)ubmarine, (d)estroyer, (c)arrier again : ";
		cin >> unitType;
	}
}

void placeUnits(char** matrix, int size, bool isFirstPlayer) {
	if (!matrix) {
		return;
	}

	int boatsCount = 2;
	int submarinesCount = 0;
	int destroyersCount = 0;
	int carriersCount = 0;

	while (boatsCount != 0 || submarinesCount != 0 || destroyersCount != 0 || carriersCount != 0) {
		showPlaceUnitsMessage(boatsCount, submarinesCount, destroyersCount, carriersCount, isFirstPlayer);

		char unitType = ' ';
		readUnitType(unitType);

		char orientation = ' ';
		readOrientation(orientation);

		//TODO: validate if coordinates have been already shot
		int startX = -1;
		int startY = -1;
		readStartCoordinates(startX, startY, size);

		bool unitWasPlaced = false;

		do
		{
			switch (unitType) {
			case BOAT_CHAR:
				if (placeUnit(matrix, size, startX, startY, orientation, ShipType::Boat)) {
					unitWasPlaced = true;
					boatsCount--;
					printMatrix(matrix, size);
				}
				else {
					cout << "Cannot place unit there it overlaps. ";
					readOrientation(orientation);
					readStartCoordinates(startX, startY, size);
				}
				break;
			case SUBMARINE_CHAR:
				if (placeUnit(matrix, size, startX, startY, orientation, ShipType::Submarine)) {
					unitWasPlaced = true;
					submarinesCount--;
					printMatrix(matrix, size);
				}
				else {
					cout << "Cannot place unit there it overlaps. ";
					readOrientation(orientation);
					readStartCoordinates(startX, startY, size);
				}
				break;
			case DESTROYER_CHAR:
				if (placeUnit(matrix, size, startX, startY, orientation, ShipType::Destroyer)) {
					unitWasPlaced = true;
					destroyersCount--;
					printMatrix(matrix, size);
				}
				else {
					cout << "Cannot place unit there it overlaps. ";
					readOrientation(orientation);
					readStartCoordinates(startX, startY, size);
				}
				break;
			case CARRIER_CHAR:
				if (placeUnit(matrix, size, startX, startY, orientation, ShipType::Carrier)) {
					unitWasPlaced = true;
					carriersCount--;
					printMatrix(matrix, size);
				}
				else {
					cout << "Cannot place unit there it overlaps. ";
					readOrientation(orientation);
					readStartCoordinates(startX, startY, size);
				}
				break;
			default:
				break;
			}
		} while (!unitWasPlaced);
	}
}

void playerTurnAttack(char** attackingMatrix, char** defendingMatrix, int size) {
	// Implement the logic for a player's turn
	int x, y;
	cout << "Enter coordinates to attack (x y): ";
	cin >> x >> y;

	// Validate input
	while (!checkCoordinateIsInside(x, size) || !checkCoordinateIsInside(y, size)) {
		cout << "Invalid coordinates. Enter again: ";
		cin >> x >> y;
	}

	// Check the result of the attack
	if (defendingMatrix[x][y] == WATER_CHAR) {
		cout << "Miss!" << endl;
		defendingMatrix[x][y] = MISSED_CHAR;  // 'O' for miss
	}
	else {
		cout << "Hit!" << endl;
		defendingMatrix[x][y] = DESTROYED_CHAR;
	}
}

bool isGameOver(char** matrix, int size) {
	if (!matrix)
	{
		return false;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != WATER_CHAR && matrix[i][j] != DESTROYED_CHAR && matrix[i][j] != MISSED_CHAR)
			{
				return false;
			}
		}
	}

	return true;
}


void playGame(char** firstPlayerMatrix, char** secondPlayerMatrix, int size) {
	if (!firstPlayerMatrix || !secondPlayerMatrix)
	{
		return;
	}

	bool isGameFinished = false;
	bool firstPlayerTurn = true;

	while (!isGameFinished) {
		// Display the boards
		cout << "Player 1's Board\t\t\tPlayer 2's Board" << endl;
		printBattlefiedlsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size);

		// Determine current player
		// Player's turn
		cout << (firstPlayerTurn ? "Player 1's Turn" : "Player 2's Turn") << endl;
		if (firstPlayerTurn) {
			playerTurnAttack(firstPlayerMatrix, secondPlayerMatrix, size);
		}
		else {
			playerTurnAttack(secondPlayerMatrix, firstPlayerMatrix, size);
		}

		// Check if the game is over
		isGameFinished = isGameOver(firstPlayerMatrix, size) || isGameOver(secondPlayerMatrix, size);

		// Switch turns
		firstPlayerTurn = !firstPlayerTurn;
	}

	// Display the final boards
	cout << "Player 1's Board\t\t\tPlayer 2's Board" << endl;
	printBattlefiedlsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size);

	// Display the winner
	cout << "Game Over! ";
	cout << (isGameOver(firstPlayerMatrix, size) ? "Player 2 Wins!" : "Player 1 Wins!") << endl;
}

void printInitialBoardsMessage() {
	const char intitialBoardsMsg[] = "Initial Boards";
	cout << intitialBoardsMsg << endl;
}

void printSpacingToHidePlayerMoves() {
	const int SPACING_SIZE = 10;

	for (int i = 0; i < SPACING_SIZE; i++) {
		cout << '\n';
	}

	cout << endl;
}

void startGame(char** firstPlayerMatrix, char** secondPlayerMatrix, int size) {
	if (!firstPlayerMatrix || !secondPlayerMatrix)
	{
		return;
	}

	printInitialBoardsMessage();
	// Show the board
	printBattlefiedlsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size);

	const bool IT_IS_FIRST_PLAYER = true;
	// Place units for first player
	placeUnits(firstPlayerMatrix, size, IT_IS_FIRST_PLAYER);

	printSpacingToHidePlayerMoves();

	// Place units for second player
	placeUnits(secondPlayerMatrix, size, !IT_IS_FIRST_PLAYER);

	// Show the board
	printBattlefiedlsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size);

	// Start the turns
	playGame(firstPlayerMatrix, secondPlayerMatrix, size);
}

bool isSizeValid(int size) {
	

	if (size >= MIN_SIZE && size <= MAX_SIZE) {
		return true;
	}
	else {
		std::cout << "Invalid size. Size must be a number between " << MIN_SIZE << " and " << MAX_SIZE << ". Try again: ";
		return false;
	}

	return true;
}

void startGameEngine() {
	showLoadingScreen();

	// For better UX 
	promptUserToStartGame();

	// Get the size of board
	int size;
	do {
		size = readSizeOfMatrix();
	} while (!isSizeValid(size));

	showGameStartMessage();

	// Initialize the boards
	char** firstPlayerMatrix = new char* [size];
	char** secondPlayerMatrix = new char* [size];
	initializeMatrix(firstPlayerMatrix, size);
	initializeMatrix(secondPlayerMatrix, size);

	// Start the game
	startGame(firstPlayerMatrix, secondPlayerMatrix, size);

	freeMemoryMatrix(firstPlayerMatrix, size);
	freeMemoryMatrix(secondPlayerMatrix, size);
}

int main()
{
	startGameEngine();
	return 0;
}