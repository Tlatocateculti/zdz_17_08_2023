// zdz_17_08_2023.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <thread>
#include <ctime>
#include <chrono>
#include <Windows.h>
#include <sstream>

using namespace std;

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

void printText(string txt) {

    cout << txt;
}

void setTime(const bool *end) {
    tm* czas = new tm;
    for (;;) {
        time_t tme = time(NULL);
        
        localtime_s(czas, &tme);
        HANDLE cli = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = GetConsoleCursorPosition(cli);
        SetConsoleCursorPosition(cli, { 0,0 });
        stringstream ss;
        ss << ((czas->tm_hour < 10) ? "0" : "") << czas->tm_hour << ":" << ((czas->tm_min < 10) ? "0" : "") << czas->tm_min << ":" << ((czas->tm_sec < 10) ? "0" : "") << czas->tm_sec << "\n";
        thread pisz(printText, ss.str());
        pisz.join();
        //cout << ((czas->tm_hour < 10) ? "0" : "") << czas->tm_hour << ":" << ((czas->tm_min < 10) ? "0" : "") << czas->tm_min << ":" << ((czas->tm_sec < 10) ? "0" : "") << czas->tm_sec << "\n";
        
        //cerr << pos.X << " " << pos.Y << "\n";
        SetConsoleCursorPosition(cli, pos);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (*end) break;
    }
    delete czas;
}



int main()
{
    bool die = false;
    thread czas(setTime, &die);
    
    

    int menu = 0;
    string text = "\n\nMenu:\n1. Ustaw godzine\n2.Ustaw minuty\n3.Wyjdz\n\nTwoj wybor: ";
    thread pisz(printText, text);
    pisz.join();
    //cout << "\n\nMenu:\n1. Ustaw godzine\n2.Ustaw minuty\n3.Wyjdz\n\nTwoj wybor: ";
    
    cin >> menu;

    if (menu == 3) exit(0);
    if (menu == 1) {
        thread pisz(printText, "ZMIENIAM GODZINE!\n");
        pisz.join();
    }
    if (menu == 2) {
        thread pisz(printText, "ZMIENIAM MINUTE!\n");
        pisz.join();
    }
    die = true;
    //czas.detach();
    czas.join();
    return 0;
}


