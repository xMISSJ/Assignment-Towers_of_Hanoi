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
static const int							MAX_SIZE = 9;
static const int							AMOUNT_OF_POLES = 3;
static const int							TOWER_NAMES[3] = { 0, 1, 2 };
static const string           PROGRAM_INTRO = "Welcome to ";
static const string           PROGRAM_NAME = "Towers of Hanoi";
static const string           PROGRAM_OUTPUT = "\nPlease enter the amount of disks in the stack (3 - 9): ";
static const string						PROGRAM_ERROR = "\nPlease pick number from 3 to 9. \n";

int														poleHeight;
char													grid[MAX_SIZE][MAX_SIZE];
bool                          intro = false;
int														moves = -1;

// Pointer.
int														*movesPtr = &moves; // Declare and assign the address of variable number to pointer movesPtr (0xyadayada).

void SetColour(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

void delay(int numberOfSeconds) {
	// Converting time into milliseconds.
	int milliSeconds = 100 * numberOfSeconds;
	clock_t startTime = clock();

	// Looping until required time is achieved.
	while (clock() < startTime + milliSeconds);
}

// The function operates the same address of every int reference and can thus modify its variable directly.
void visualisationHanoi(int *poleHeight, int *disk, int &currentPosition, int &nextPosition, bool show = false) {
	SetColour(12);
	//cout << "MovesPtr: " << movesPtr; Shares the same address as moves.
	for (int y = 0; y < *poleHeight; y++)
	{
		for (int x = 0; x < AMOUNT_OF_POLES; x++)
		{
			/* Find the disk that is going to move.
			 * We need to compare an char to an int. So instead we convert the char to an int.
			 * Since the disk is always a number we can substract 48 from the ASCII table to give its original value.
			 * Eg: 0 = 48, 1 = 49, 2 = 50...
			 */
			if ((int)grid[x][y] - 48 == *disk) {

				// Save the disk number.
				char movingDisk = grid[x][y];

				// Remove the old position, by putting a pole back.
				grid[x][y] = '|';

				/* Move the disk to the next position
				 * Since we are limited to the height of the pole, we use a reverse loop going from bottom to top to check if there
				 * is an available spot where we can put the disk. This prevents floating disks and allows the inserted disk to start at the bottom of the pole.
				 */
				for (int nextPole = *poleHeight; nextPole-- > 0;)
				{
					// If the disk finds an available spot (which is a pole "|"), we can proceed with inserting the disk in that position.
					if (grid[nextPosition][nextPole] == '|') { // Check if the position is available.
						grid[nextPosition][nextPole] = *disk + '0'; // Insert the disk, since the disk is an integer we need to convert it to a char. This is possible by adding + '0'.
						break; // Stop the loop, we are done searching with the available spot.
					}
				}
			}

			if (show)
				cout << "     " << grid[x][y] << "  ";        // Display the visualisation.
		}
		if (show)
			cout << endl;        // Separate the grid with a white line.
	}
	if (show)
		printf("---------------------------\n");
	SetColour(7);
}

void TowerOfHanoi(int disk, int currentPosition, int midPillar, int nextPosition) {
	if (disk == 0) {
		moves++;
		delay(10);
		visualisationHanoi(&poleHeight, &disk, currentPosition, nextPosition, true);
		return;
	}

	// Makes recursive call to move number - 1 disks to auxiliary pilar.
	TowerOfHanoi(disk - 1, currentPosition, nextPosition, midPillar);

	// Move the numberth disk from "A" to "B"
	printf("\nMove disk %d from pole %d to pole %d \n\n", disk, currentPosition + 1, nextPosition + 1);
	visualisationHanoi(&poleHeight, &disk, currentPosition, nextPosition);

	// Move number - 1 disk from auxiliary pilar to destination pilar.
	TowerOfHanoi(disk - 1, midPillar, currentPosition, nextPosition);
}

int main()
{
	// Program shows error, so long there is no valid number (minSize-maxSize).
	do {
		// codes;
		if (!intro) {
			// cout << "Moves: " << &moves << endl; // Shares the same address as movesPtr.
			cout << PROGRAM_INTRO;
			SetColour(4);
			cout << PROGRAM_NAME;
			SetColour(15);
			cout << "!" << PROGRAM_OUTPUT;
			intro = true;
		}

		cin >> poleHeight;

		SetColour(4);
		if (poleHeight < MIN_SIZE || poleHeight > MAX_SIZE) {
			cerr << "\n**********************************" << endl
				<< "      ERROR: Invalid Input!					 " << endl
				<< "**********************************";
			cerr << PROGRAM_ERROR << endl;
		}
		SetColour(15);
	} while (poleHeight < MIN_SIZE || poleHeight > MAX_SIZE);

	SetColour(10);
	cout << "\nStarting the Towers of Hanoi!" << endl;
	SetColour(15);

	// Create poles.
	for (int y = 0; y < poleHeight; y++)
	{
		for (int x = 0; x < AMOUNT_OF_POLES; x++)
		{
			grid[x][y] = '|';
		}
		// Insert disks.
		grid[0][y] = y + 1 + '0';
	}

	cout << endl;
	// A, B, C -> A is source, B is auxiliary and C is destination.
	TowerOfHanoi(poleHeight, TOWER_NAMES[0], TOWER_NAMES[1], TOWER_NAMES[2]);

	SetColour(10);
	cout << endl << "Finished the Towers of Hanoi in " << *movesPtr << " moves." << endl;
	SetColour(15);
	return 0;
	delete movesPtr;
}

