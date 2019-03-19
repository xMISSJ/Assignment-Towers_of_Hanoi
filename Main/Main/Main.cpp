// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
 *	This is the main.cpp file for the Towers of Hanoi.
 *	Developed for the Towers of Hanoi school assignment.
 *	This .cpp file fetches and stores user input data. It also prints text for the user in the console.
 */

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

/*
 * 1. Blue         6. Yellow (Dark)        11. Bright Cyan
 * 2. Green        7. Default White        12. Bright Red
 * 3. Cyan         8. Grey                 13. Magenta
 * 4. Red          9. Bright Blue          14. Yellow
 * 5. Purple       10. Bright Green        15. Bright White
 * Numbers after '15' are background colours/
 */
void SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

int main()
{
	int                           diskAmount;
	bool                          intro = false;
	static const int							MIN_SIZE = 3;
	static const int							MAX_SIZE = 7;
	static const string           PROGRAM_INTRO = "Welcome to ";
	static const string           PROGRAM_NAME = "Towers of Hanoi";
	static const string           PROGRAM_OUTPUT = "\nPlease enter the amount of discs (3 - 7). \n";
	static const string						PROGRAM_ERROR = "\nInvalid number. Please pick number from 3 to 7. \n";

		// Program shows error, so long there is no valid number (minSize-maxSize).
		do {
			// codes;
			if (!intro) {
				cout << PROGRAM_INTRO;
				SetColor(12);
				cout << PROGRAM_NAME;
				SetColor(7);
				cout << "!" << PROGRAM_OUTPUT;
				intro = true;
			}
			cin >> diskAmount;

			if (diskAmount < MIN_SIZE || diskAmount > MAX_SIZE) {
				cout << PROGRAM_ERROR << endl;
			}
		} while (diskAmount < MIN_SIZE || diskAmount > MAX_SIZE);
}

