#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;
using std::cout;
using std::cin;
using std::endl;
using std::end;
using std::begin;
using std::tolower;

void printMap(const char*, const unsigned&, const bool&, const unsigned&, const unsigned&);
void initMap(char*, unsigned&, const unsigned&, const unsigned&);
void moveTo(unsigned&, const unsigned&, const unsigned&, const char&);
void placeObj1(char *arr, const unsigned&);

int main()
{
    unsigned width, height, playerIndex;
    cout << "Enter width and height of map: ";
    if (cin >> width >> height && (width > 2 || height > 2)) {
        unsigned mapSz = width * height;
        char gameMap[mapSz];
        char direction;
        bool playerShow = true;

        initMap(gameMap, playerIndex, width, height);
        printMap(gameMap, playerIndex, playerShow, width, height);

        while (!(GetKeyState(VK_ESCAPE) & 0x8000)) {
            if (GetKeyState('W') & 0x8000 || GetKeyState(VK_UP) & 0x8000) {
                direction = 'u';
                moveTo(playerIndex, width, height, direction);
                printMap(gameMap, playerIndex, playerShow, width, height);
            }
            else if (GetKeyState('S') & 0x8000 || GetKeyState(VK_DOWN) & 0x8000) {
                direction = 'd';
                moveTo( playerIndex, width, height, direction);
                printMap(gameMap, playerIndex, playerShow, width, height);
            }
            else if (GetKeyState('A') & 0x8000 || GetKeyState(VK_LEFT) & 0x8000) {
                direction = 'l';
                moveTo(playerIndex, width, height, direction);
                printMap(gameMap, playerIndex, playerShow, width, height);
            }
            else if (GetKeyState('D') & 0x8000 || GetKeyState(VK_RIGHT) & 0x8000) {
                direction = 'r';
                moveTo(playerIndex, width, height, direction);
                printMap(gameMap, playerIndex, playerShow, width, height);
            }
            else if (GetKeyState('E') & 0x8000 || GetKeyState(VK_SPACE) & 0x8000) {
                placeObj1(gameMap, playerIndex);
                printMap(gameMap, playerIndex, playerShow, width, height);
            }
            else if (GetKeyState('H') & 0x8000) {
                playerShow = !playerShow;
                printMap(gameMap, playerIndex, playerShow, width, height);
            }
            sleep_for(100ms);
        }
    }
    return 0;
}

void printMap(const char *arr, const unsigned &playerPosIndex, const bool &playerShow, const unsigned &w, const unsigned &h)
{
    system("CLS");
    for (size_t index = 0; index != w*h; ++index) {
        if (!(index % w) && (index > 0))
            cout << endl;
            if (playerPosIndex != index || !playerShow) {
                cout << arr[index] << ' ';
            }
            else {
                cout << "X ";
            }
    }
    cout << '\n' << endl;
}

void initMap(char *arr, unsigned &playerPosIndex, const unsigned &w, const unsigned &h)
{
    bool oddScale = (w % 2 && h % 2);
    for (size_t index = 0; index != w*h; ++index) {
        arr[index] = '-';
        if ((oddScale && index == w*h/2) || (!oddScale && index == (w*h+w)/2)) {
            playerPosIndex = index;
        }
    }
}

void moveTo(unsigned &playerPosIndex, const unsigned &w, const unsigned &h, const char &direction)
{
    switch (tolower(direction))
    {
        case 'u':   // up
            playerPosIndex = playerPosIndex - w < w*h ? playerPosIndex - w : playerPosIndex;
            break;
        case 'd':   // down
            playerPosIndex = playerPosIndex + w < w*h ? playerPosIndex + w : playerPosIndex;
            break;
        case 'l':   // left
            playerPosIndex = (playerPosIndex - 1) % w < playerPosIndex % w ? playerPosIndex - 1 : playerPosIndex;
            break;
        case 'r':   // right
            playerPosIndex = (playerPosIndex + 1) % w > playerPosIndex % w ? playerPosIndex + 1 : playerPosIndex;
            break;
    }
}

void placeObj1(char *arr, const unsigned &playerPosIndex)
{
    arr[playerPosIndex] = arr[playerPosIndex] != 'O' ? 'O' : '-';
}

