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
#include <time.h>
#include <stdio.h>

using namespace std;

// Global variables.
int														diskCounter = -1;
char													diskArray[] = { '1', '2', '3', '4', '5', '6', '7' };
int														diskAmount;
const int											amountOfPoles = 3;
char													grid[3][7];

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

void visualisationHanoi(int height, char grid[][7], int destination, int diskNumber) {

	// Fill the grid array.
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < amountOfPoles; y++)
		{
			grid[x][y] = '|';
		}
	}

	// Insert disks.
	for (int x = 0; x < height; x++)
	{
		diskCounter++;
		for (int y = 0; y < amountOfPoles; y++)
		{
			grid[diskCounter][0] = diskArray[diskCounter];
		}
	}

	// Reset counter.
	diskCounter = -1; 

	// Display the grid.
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < amountOfPoles; y++)
		{
			cout << "      " << grid[x][y];
		}
		cout << endl;
	}

	printf("---------------------------\n");
}

void TowerOfHanoi(int number, int firstPillar, int midPillar, int lastPillar) {

	if (number == 1) {
		printf("Move disk %d from %d to %d \n", number, firstPillar, lastPillar);
		delay(10);
		visualisationHanoi(diskAmount, grid, lastPillar, number);
		return;
	}

	// Makes recursive call to move number - 1 disks to auxiliary pilar.
	TowerOfHanoi(number - 1, firstPillar, lastPillar, midPillar);

	// Move the numberth disk from "A" to "B"
	printf("Move disk %d from %d to %d \n", number, firstPillar, lastPillar);
	delay(10);
	visualisationHanoi(diskAmount, grid, lastPillar, number);

	// Move number - 1 disk from auxiliary pilar to destination pilar.
	TowerOfHanoi(number - 1, midPillar, firstPillar, lastPillar);
}

int main()
{
	bool                          intro = false;
	static const int							MIN_SIZE = 3;
	static const int							MAX_SIZE = 7;
	static const int							TOWER_NAMES[3] = { 0, 1, 2 };
	static const string           PROGRAM_INTRO = "Welcome to ";
	static const string           PROGRAM_NAME = "Towers of Hanoi";
	static const string           PROGRAM_OUTPUT = "\nPlease enter the amount of disks in the stack (3 - 7). \n";
	static const string						PROGRAM_ERROR = "\nPlease pick number from 3 to 7. \n";

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
				cerr << "\n**********************************" << endl
					<< "      ERROR: Invalid Input!					 " << endl
					<< "**********************************";
				cerr << PROGRAM_ERROR << endl;
			}
		} while (diskAmount < MIN_SIZE || diskAmount > MAX_SIZE);

		// A, B, C -> A is source, B is auxiliary and C is destination.
		TowerOfHanoi(diskAmount, TOWER_NAMES[0], TOWER_NAMES[1], TOWER_NAMES[2]);

		return 0;
}

