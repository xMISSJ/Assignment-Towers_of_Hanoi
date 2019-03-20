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
static const int							MIN_SIZE = 3;
static const int							MAX_SIZE = 7;
static const int							TOWER_NAMES[3] = { 0, 1, 2 };
static const string           PROGRAM_INTRO = "Welcome to ";
static const string           PROGRAM_NAME = "Towers of Hanoi";
static const string           PROGRAM_OUTPUT = "\nPlease enter the amount of disks in the stack (3 - 7). \n";
static const string						PROGRAM_ERROR = "\nPlease pick number from 3 to 7. \n";

int														diskCounter = -1;
char													diskArray[] = { '1', '2', '3', '4', '5', '6', '7' };
int														diskAmount;
const int											amountOfPoles = 3;
char													grid[MIN_SIZE][MAX_SIZE];
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

void visualisationHanoi(int height, int disk, int currentPosition, int nextPosition) {

	for (int x = 0; x < amountOfPoles; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if ((int)grid[x][y] - 48 == disk) {

				// Save the disk
				char movingDisk = grid[x][y];

				// Remove the old position
				grid[x][y] = '|';

				// Move the disk to the next position
				for (int nextPole = height; nextPole --> 0;)
				{
					if (grid[nextPole][nextPosition] == '|') {
						grid[nextPole][nextPosition] = disk + '0';
						break;
					}
				}

			}
			cout << "   " << grid[x][y] << "   ";
		}
		cout << endl;
	}

	printf("---------------------------\n");
}

void TowerOfHanoi(int disk, int currentPosition, int midPillar, int nextPosition) {

	if (disk == 1) {
		moves++;
		printf("Move disk %d from %d to %d \n", disk, currentPosition, nextPosition);
		delay(10);
		visualisationHanoi(diskAmount, disk, currentPosition, nextPosition);
		return;
	}

	// Makes recursive call to move number - 1 disks to auxiliary pilar.
	TowerOfHanoi(disk - 1, currentPosition, nextPosition, midPillar);

	// Move the numberth disk from "A" to "B"
	printf("Move disk %d from %d to %d \n", disk, currentPosition, nextPosition);
	delay(10);
	visualisationHanoi(diskAmount, disk, currentPosition, nextPosition);

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
			cin >> diskAmount;

			if (diskAmount < MIN_SIZE || diskAmount > MAX_SIZE) {
				cerr << "\n**********************************" << endl
					<< "      ERROR: Invalid Input!					 " << endl
					<< "**********************************";
				cerr << PROGRAM_ERROR << endl;
			}
		} while (diskAmount < MIN_SIZE || diskAmount > MAX_SIZE);


		for (int x = 0; x < diskAmount; x++)
		{
			for (int y = 0; y < amountOfPoles; y++)
			{
				grid[x][y] = '|';
			}
			grid[x][0] = x + 1 + '0';
		}

		// A, B, C -> A is source, B is auxiliary and C is destination.
		TowerOfHanoi(diskAmount, TOWER_NAMES[0], TOWER_NAMES[1], TOWER_NAMES[2]);

		return 0;
}

