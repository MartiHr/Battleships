#include <iostream>

using namespace std;

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

void showEnterSizeMessage() {
	cout << "" << endl;
}

int readSizeOfMatrix() {
	int size = 0;
	cin >> size;
	return size;
}

void initializeMatrix(char** matrix, int size) {
	if (!matrix) {
		return;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = '~';
		}
	}
}

int main()
{
	showLoadingScreen();
	showEnterSizeMessage();
	int size = readSizeOfMatrix();

	char** matrix = new char* [size];
}