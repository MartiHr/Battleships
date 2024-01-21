#include <iostream>

using namespace std;

enum ShipType {
	Destroyed = 0,
	Boat = 2,
	Submarine = 3,
	Destroyer = 4,
	Carrier = 5
};

const int MIN_SIZE = 3;
const int MAX_SIZE = 41;
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
	cout << "Please enter the size " << "[" << MIN_SIZE << ", " << MAX_SIZE << "]" 
		<< " for the game fields and press ENTER to start: ";
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

void readPositiveNumber(int& number) {
	const char POSITIVE_NUMBER_MESSAGE[] = "Please enter a non-negative number: ";
	const char INVALID_INPUT_MESSAGE[] = "Invalid input. Please enter a number : ";

	bool validInput = false;
	while (!validInput) {
		//std::cout << "Enter the size of the board: ";

		if (std::cin >> number) {
			if (number >= 0) {
				validInput = true;
			}
			else {
				std::cout << POSITIVE_NUMBER_MESSAGE;
			}
		}
		else {
			std::cin.clear(); // Clear the fail state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
			std::cout << INVALID_INPUT_MESSAGE;
		}
	}
}

int readSizeOfMatrix() {
	const char POSITIVE_NUMBER_MESSAGE[] = "Please enter a positive number: \n";
	const char INVALID_INPUT_MESSAGE[] = "Invalid input. Please enter a number : ";

	int size;
	readPositiveNumber(size);

	return size;
}

void printMatrix(char** matrix, int size) {
	if (!matrix) {
		return;
	}

	// Print column indices
	std::cout << "   ";
	for (int j = 0; j < size; j++) {
		std::cout << " " << j;
	}
	std::cout << std::endl;

	for (int i = 0; i < size; i++) {
		// Print row index
		if (i < 10) {
			std::cout << i << " |";
		}
		else {
			std::cout << i << "|";
		}
		for (int j = 0; j < size; j++) {
			std::cout << " " << matrix[i][j];
		}

		std::cout << std::endl;
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

// Is arguably worse
//void printBattlefieldInnerCheckings(char** leftMatrix, int i, int size, bool hidden) {
//	for (int j = 0; j < size; j++) {
//		char current = leftMatrix[i][j];
//		if (hidden) {
//			if (current == WATER_CHAR) {
//				cout << WATER_CHAR;
//			}
//			else if (current == MISSED_CHAR) {
//				cout << MISSED_CHAR;
//			}
//			else {
//				cout << DESTROYED_CHAR;
//			}
//		}
//		else {
//			cout << current;
//		}
//	}
//}

void printColumnIndices(int size) {
	// Print column indices for the left matrix
	std::cout << "   ";
	for (int j = 0; j < size; j++) {
		std::cout << " " << j;
	}

	// Print spacing between matrices
	std::cout << "\t\t\t\t\t";

	// Print column indices for the right matrix
	std::cout << "   ";
	for (int j = 0; j < size; j++) {
		std::cout << " " << j;
	}

	std::cout << std::endl;
}

void printBattlefieldsSideBySide(char** leftMatrix, char** rightMatrix, int size, bool hidden = true) {
	if (!leftMatrix || !rightMatrix) {
		return;
	}

	const int maxSizeForUpperIndices = 12;

	if (size < maxSizeForUpperIndices)
	{
		printColumnIndices(size);
	}

	// Print the matrices with row indices
	for (int i = 0; i < size; i++) {
		// Print row index
		if (i < 10) {
			std::cout << i << " |";
		}
		else {
			std::cout << i << "|";
		}
		// Print left matrix
		for (int j = 0; j < size; j++) {
			char current = leftMatrix[i][j];
			if (hidden) {
				if (current == WATER_CHAR) {
					std::cout << " " << WATER_CHAR;
				}
				else if (current == MISSED_CHAR) {
					std::cout << " " << MISSED_CHAR;
				}
				else {
					std::cout << " " << DESTROYED_CHAR;
				}
			}
			else {
				std::cout << " " << current;
			}
		}

		// Print spacing
		std::cout << "\t\t\t\t\t";

		if (i < 10) {
			std::cout << i << " |";
		}
		else {
			std::cout << i << "|";
		}
		// Print right matrix
		for (int j = 0; j < size; j++) {
			char current = rightMatrix[i][j];
			if (hidden) {
				if (current == WATER_CHAR) {
					std::cout << " " << WATER_CHAR;
				}
				else if (current == MISSED_CHAR) {
					std::cout << " " << MISSED_CHAR;
				}
				else {
					std::cout << " " << DESTROYED_CHAR;
				}
			}
			else {
				std::cout << " " << current;
			}
		}

		std::cout << std::endl;
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
	const char ENTER_X[] = "Enter start x coordinate: ";
	const char ENTER_X_AGAIN[] = "Coordinate outside of board, enter start x coordinate again: ";
	const char ENTER_Y[] = "Enter start y coordinate: ";
	const char ENTER_Y_AGAIN[] = "Coordinate outside of board, enter start y coordinate again: ";

	cout << ENTER_X;
	readPositiveNumber(startX);
	while (!checkCoordinateIsInside(startX, size)) {
		cout << ENTER_X_AGAIN;
		readPositiveNumber(startX);
	}

	cout << ENTER_Y;
	readPositiveNumber(startY);
	while (!checkCoordinateIsInside(startY, size)) {
		cout << ENTER_Y_AGAIN;
		readPositiveNumber(startY);
	}
}

void readOrientation(char& orientation) {
	const char ORIENTATION_MSG[] = "Enter orientation (h for horizontal, v - for vertical): ";
	const char WRONG_ORIENTATION_MSG[] = "Wrong orientation input, enter orientation again (h for horizontal, v - for vertical): ";

	cout << ORIENTATION_MSG;
	cin >> orientation;
	while (!isOrientationValid(orientation)) {
		cout << WRONG_ORIENTATION_MSG;
		cin >> orientation;
	}
}

void readUnitType(char& unitType) {
	const char UNIT_TYPES[] = "Enter type of unit - b for (b)oat, (s)ubmarine, (d)estroyer, (c)arrier: ";
	const char WRONG_UNIT_TYPES[] = "Wrong unit, enter type of unit - b for (b)oat, (s)ubmarine, (d)estroyer, (c)arrier again: ";

	cout << UNIT_TYPES;
	cin >> unitType;
	while (unitType != BOAT_CHAR && unitType != SUBMARINE_CHAR && unitType != DESTROYER_CHAR && unitType != CARRIER_CHAR) {
		cout << WRONG_UNIT_TYPES;
		cin >> unitType;
	}
}

void readUnits(int& boatsCount, int& submarinesCount, int& destroyersCount, int& carriersCount, int size) {
	const char UNIT_COUNTS[] = "Enter counts of units which would let them all be placed.";
	const char BOATS_NUMBER[] = "Enter number of boats:";
	const char SUBMARINES_NUMBER[] = "Enter number of submarines:";
	const char DESTROYERS_NUMBER[] = "Enter number of destroyers:";
	const char CARRIERS_NUMBER[] = "Enter number of carriers:";

	int maxSum = size * size;
	int sum;

	do {
		cout << UNIT_COUNTS << endl;
		sum = 0;

		cout << BOATS_NUMBER << endl;
		readPositiveNumber(boatsCount);
		cout << SUBMARINES_NUMBER << endl;
		readPositiveNumber(submarinesCount);
		cout << DESTROYERS_NUMBER << endl;
		readPositiveNumber(destroyersCount);
		cout << CARRIERS_NUMBER << endl;
		readPositiveNumber(carriersCount);

		sum = boatsCount * (int)Boat + submarinesCount * (int)Submarine + destroyersCount * (int)Destroyer + carriersCount * (int)Carrier;

	} while (sum > maxSum || sum == 0);
}

void placeUnits(char** matrix, int size, bool isFirstPlayer, 
	int boatsCount, int submarinesCount, int destroyersCount, int carriersCount) {
	const char OVERLAPPING_UNIT[] = "Cannot place unit there it overlaps. ";

	if (!matrix) {
		return;
	}

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
					cout << OVERLAPPING_UNIT;
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
					cout << OVERLAPPING_UNIT;
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
					cout << OVERLAPPING_UNIT;
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
					cout << OVERLAPPING_UNIT;
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

void readXAndYAttackCoordinates(int& x, int& y) {

}

void playerTurnAttack(char** defendingMatrix, int size) {
	const char ENTER_ATTACK_COORDINATES[] = "Enter coordinates to attack (x, y):";
	const char MISS[] = "Miss!";
	const char WASTED_SHOT[] = "You wasted a shot!";
	const char HIT[] = "Hit!";

	if (!defendingMatrix)
	{
		return;
	}

	// Implement the logic for a player's turn
	int x = 0;
	int y = 0;

	cout << ENTER_ATTACK_COORDINATES << endl;
	readPositiveNumber(x);
	readPositiveNumber(y);

	// Validate input
	while (!checkCoordinateIsInside(x, size) || !checkCoordinateIsInside(y, size)) {
		cout << "Invalid coordinates: " << endl;
		readPositiveNumber(x);
		readPositiveNumber(y);
	}

	// Check the result of the attack
	if (defendingMatrix[x][y] == WATER_CHAR) {
		cout << MISS << endl;
		defendingMatrix[x][y] = MISSED_CHAR;  // 'O' for miss
	}
	else if (defendingMatrix[x][y] == DESTROYED_CHAR) {
		cout << WASTED_SHOT << endl;
	}
	else {
		cout << HIT << endl;
		defendingMatrix[x][y] = DESTROYED_CHAR;
	}

	//printBattlefieldsSideBySide(defendingMatrix, size);
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
	const char PLAYER_1_TURN[] = "Player 1's Turn";
	const char PLAYER_2_TURN[] = "Player 2's Turn";
	const char PLAYER_1_WIN[] = "Player 1 Wins!";
	const char PLAYER_2_WIN[] = "Player 2 Wins!";
	const char FINAL_BOARDS[] = "Final boards:";
	const char GAME_OVER[] = "Game Over! ";

	if (!firstPlayerMatrix || !secondPlayerMatrix)
	{
		return;
	}

	bool isGameFinished = false;
	bool firstPlayerTurn = true;

	while (!isGameFinished) {
		// Display the boards
		/*cout << "Player 1's Board\t\t\tPlayer 2's Board" << endl;
		printBattlefieldsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size);*/

		// Determine current player
		// Player's turn
		cout << (firstPlayerTurn ? PLAYER_1_TURN : PLAYER_2_TURN) << endl;
		if (firstPlayerTurn) {
			playerTurnAttack(secondPlayerMatrix, size);
		}
		else {
			playerTurnAttack(firstPlayerMatrix, size);
		}

		// Check if the game is over
		isGameFinished = isGameOver(firstPlayerMatrix, size) || isGameOver(secondPlayerMatrix, size);

		// Switch turns
		firstPlayerTurn = !firstPlayerTurn;
	}

	// Display the final boards
	cout << FINAL_BOARDS << endl;
	printBattlefieldsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size, false);

	// Display the winner
	cout << GAME_OVER;
	cout << (isGameOver(firstPlayerMatrix, size) ? PLAYER_2_WIN : PLAYER_1_WIN) << endl;
}

void printInitialBoardsMessage() {
	const char INITIAL_BOARDS_MSG[] = "Initial Boards";
	cout << INITIAL_BOARDS_MSG << endl;
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
	printBattlefieldsSideBySide(firstPlayerMatrix, secondPlayerMatrix, size);

	const bool IT_IS_FIRST_PLAYER = true;

	// Read units (if more units are given the logic should be encapsulated in an array)
	int boatsCount = 0;
	int submarinesCount = 0;
	int destroyersCount = 0;
	int carriersCount = 0;

	readUnits(boatsCount, submarinesCount, destroyersCount, carriersCount, size);

	// Place units for first player
	placeUnits(firstPlayerMatrix, size, IT_IS_FIRST_PLAYER, boatsCount, submarinesCount, destroyersCount, carriersCount);

	// (Optional)
	//printSpacingToHidePlayerMoves();

	// Place units for second player
	placeUnits(secondPlayerMatrix, size, !IT_IS_FIRST_PLAYER, boatsCount, submarinesCount, destroyersCount, carriersCount);

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