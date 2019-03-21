/*
 *	This is the main.cpp file for the Towers of Hanoi.
 *	Developed for the Towers of Hanoi school assignment.
 *  This main.cpp solves the Towers of Hanoi puzzle with a recursive method (bruteforce). 
 *  The output is shown in the form of ASCII art.
 */

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <stdio.h>

using namespace std;

// Global variables.
static const int							MIN_SIZE = 3;
static const int							MAX_SIZE = 7;
static const int							AMOUNT_OF_POLES = 3;
static const int							TOWER_NAMES[3] = { 0, 1, 2 };
static const string           PROGRAM_INTRO = "Welcome to ";
static const string           PROGRAM_NAME = "Towers of Hanoi";
static const string           PROGRAM_OUTPUT = "\nPlease enter the amount of disks in the stack (3 - 7). \n";
static const string						PROGRAM_ERROR = "\nPlease pick number from 3 to 7. \n";

int														diskCounter = -1;
char													diskArray[] = { '1', '2', '3', '4', '5', '6', '7' };
int														poleHeight;
char													grid[MAX_SIZE][MAX_SIZE];
bool                          intro = false;
int														moves = 0;

void SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

void delay(int numberOfSeconds) {
// Converting time into milliseconds.
	int milliSeconds = 100 * numberOfSeconds;
	clock_t startTime = clock();

	// Looping until required time is achieved.
	while (clock() < startTime + milliSeconds);
}

void visualisationHanoi(int poleHeight, int disk, int currentPosition, int nextPosition, bool show = false) {
	SetColor(12);

	for (int y = 0; y < poleHeight; y++)
	{
		for (int x = 0; x < AMOUNT_OF_POLES; x++)
		{
			// Find the disk that is going to move
			if ((int)grid[x][y] - 48 == disk) {

				// Save the disk
				char movingDisk = grid[x][y];

				// Remove the old position
				grid[x][y] = '|';

				// Move the disk to the next position
				for (int nextPole = poleHeight; nextPole --> 0;)
				{
					// If the disk finds an available spot, it will insert it
					if (grid[nextPosition][nextPole] == '|') {
						grid[nextPosition][nextPole] = disk + '0';
						break;
					}
				}
			}
			if (show)
				cout << "     " << grid[x][y] << "  ";
		}
		if (show)
			cout << endl;
	}
	if (show)
		printf("---------------------------\n");
	SetColor(7);
}

void TowerOfHanoi(int disk, int currentPosition, int midPillar, int nextPosition) {

	moves++;

	if (disk == 0) {
		delay(10);
		visualisationHanoi(poleHeight, disk, currentPosition, nextPosition, true);
		return;
	}

	// Makes recursive call to move number - 1 disks to auxiliary pilar.
	TowerOfHanoi(disk - 1, currentPosition, nextPosition, midPillar);

	// Move the numberth disk from "A" to "B"
	printf("Move disk %d from %d to %d \n", disk, currentPosition, nextPosition);
	visualisationHanoi(poleHeight, disk, currentPosition, nextPosition);

	// Move number - 1 disk from auxiliary pilar to destination pilar.
	TowerOfHanoi(disk - 1, midPillar, currentPosition, nextPosition);
}

int main()
{
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
			cin >> poleHeight;

			if (poleHeight < MIN_SIZE || poleHeight > MAX_SIZE) {
				cerr << "\n**********************************" << endl
					<< "      ERROR: Invalid Input!					 " << endl
					<< "**********************************";
				cerr << PROGRAM_ERROR << endl;
			}
		} while (poleHeight < MIN_SIZE || poleHeight > MAX_SIZE);


		cout << "Height: " << poleHeight << endl;

		// Create poles
		for (int y = 0; y < poleHeight; y++)
		{
			for (int x = 0; x < AMOUNT_OF_POLES; x++)
			{
				grid[x][y] = '|';
			}
			// Insert disks
			grid[0][y] = y + 1 + '0';
		}

		cout << endl;
		// A, B, C -> A is source, B is auxiliary and C is destination.
		TowerOfHanoi(poleHeight, TOWER_NAMES[0], TOWER_NAMES[1], TOWER_NAMES[2]);

		return 0;
}

