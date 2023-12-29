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
    cout << "     \\_______________________________________________WWS_________/" << endl;
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

int main()
{
    showLoadingScreen();
    
    cout << "Press enter to start a game!";
    cin.get();
    cout << "Game started";
}