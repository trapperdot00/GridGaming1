#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <string>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;
using std::cout;
using std::cin;
using std::endl;
using std::end;
using std::begin;
using std::tolower;
using std::string;

inline void getMapSize(unsigned&, unsigned&);
void printMap(const char*, const unsigned&, const bool&, const unsigned&, const unsigned&);
void initMap(char*, unsigned&, const unsigned&, const unsigned&);
void doAction(char*, unsigned&, const unsigned&, const unsigned&, const char&, bool&);
inline void placeObj1(char *arr, const unsigned&);
const char getActionFromKeyStates();

int main()
{
    unsigned width, height;
    getMapSize(width, height);
    if (width > 2 || height > 2) {
        const unsigned mapSz = width * height;
        char gameMap[mapSz];
        unsigned playerIndex;
        initMap(gameMap, playerIndex, width, height);
        char action = 'n';
        bool playerShow = true;
        printMap(gameMap, playerIndex, playerShow, width, height);
        do {
            if (action != 'n') {
                doAction(gameMap, playerIndex, width, height, action, playerShow);
                printMap(gameMap, playerIndex, playerShow, width, height);
                sleep_for(100ms);
            }
            action = getActionFromKeyStates();
        } while (action != 'x');
    }
    return 0;
}


inline void getMapSize(unsigned &w, unsigned &h)
{
    cout << "Enter width and height of map: ";
    cin >> w >> h;
}

void printMap(const char *arr, const unsigned &playerPosIndex, const bool &playerShow, const unsigned &w, const unsigned &h)
{
    system("CLS");
    string fullMap;
    for (size_t index = 0; index != w*h; ++index) {
        fullMap += (playerShow && index == playerPosIndex) ? "X " : string() + arr[index] + ' ';
        if (index % w == w-1)
            fullMap += '\n';
    }
    cout << fullMap << endl;
}

void initMap(char *arr, unsigned &playerPosIndex, const unsigned &w, const unsigned &h)
{
    unsigned midW = w / 2;
    unsigned midH = h / 2;
    playerPosIndex = midH * w + midW;
    for (unsigned index = 0; index < w*h; ++index) {
        arr[index] = '-';
    }
}

void doAction(char *arr, unsigned &playerPosIndex, const unsigned &w, const unsigned &h, const char &direction, bool &show)
{
    switch (tolower(direction))
    {
        case 'u':   // up
            if (playerPosIndex >= w) {
                playerPosIndex -= w;
            }
            break;
        case 'd':   // down
            if (playerPosIndex < w*h-h) {
                playerPosIndex += w;
            }
            break;
        case 'l':   // left
            if (playerPosIndex % w != 0) {
                playerPosIndex -= 1;
            }
            break;
        case 'r':   // right
            if (playerPosIndex % w != w-1) {
                playerPosIndex += 1;
            }
            break;
        case 'p':   // place object1
            placeObj1(arr, playerPosIndex);
            break;
        case 'h':   // toggle player hide/show
            show = !show;
            break;
    }
}

inline void placeObj1(char *arr, const unsigned &playerPosIndex)
{
    arr[playerPosIndex] = arr[playerPosIndex] != 'O' ? 'O' : '-';
}

const char getActionFromKeyStates()
{
    if (GetKeyState('W') & 0x8000 || GetKeyState(VK_UP) & 0x8000) {
        return 'u'; // up
    }
    else if (GetKeyState('S') & 0x8000 || GetKeyState(VK_DOWN) & 0x8000) {
        return 'd'; // down
    }
    else if (GetKeyState('A') & 0x8000 || GetKeyState(VK_LEFT) & 0x8000) {
        return 'l'; // left
    }
    else if (GetKeyState('D') & 0x8000 || GetKeyState(VK_RIGHT) & 0x8000) {
        return 'r'; // right
    }
    else if (GetKeyState('E') & 0x8000 || GetKeyState(VK_SPACE) & 0x8000) {
        return 'p'; // place object1
    }
    else if (GetKeyState('H') & 0x8000) {
        return 'h'; // toggle player hide/show
    }
    else if (GetKeyState(VK_ESCAPE) & 0x8000) {
        return 'x'; // exit
    }
    return 'n'; // none
}
