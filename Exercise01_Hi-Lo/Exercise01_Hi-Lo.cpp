// Course:          IGME 309
// Student Name: Chase Martoccia
// Friday Exercise: 01

#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
using namespace std;

bool g_is_running = true;
int guessCount = 0;

int GenerateRandomNumber() {
    // TODO: generate a random integer from 1 to 100 (inclusive)
    srand(time(0));
    int targetNumber = 1 + rand() % 100;
    return targetNumber;
}

int PlayerEnterANumber() {
    int playerNumber = 0;
    cout << "Enter a number (-1 to quit): ";
    // TODO: read the player's input
    std::cin >> playerNumber;
    return playerNumber;
}

// Return 0 if correct, 1 if low, 2 if high.
int HighOrLow(int targetNumber, int playerNumber) {
    // TODO: compare the two numbers
    if (playerNumber == targetNumber)
    {
        return 0;
    }
    else if (playerNumber < targetNumber)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

void GameLoop() {
    int targetNumber = GenerateRandomNumber();

    // Challenge 1: after the core program works, add a guess counter here.

    while (g_is_running) {
        int playerNumber = PlayerEnterANumber();

        if (playerNumber == -1) {
            g_is_running = false;
            return;
        }

        // Challenge 2 (optional): reject values outside 1-100 here.

        int hilo = HighOrLow(targetNumber, playerNumber);
        guessCount++;

        if (hilo == 0) {
            cout << "Your guess is correct! The target number is "
                << targetNumber << "." << endl;
            cout << "You guessed correctly in "
                << guessCount << " guesses." << endl;
            guessCount = 0;
            break;
        }
        else if (hilo == 1) {
            cout << "Your guess is low." << endl;
        }
        else if (hilo == 2) {
            cout << "Your guess is high." << endl;
        }
    }

    cout << "Continue to play? (y/n): ";
    char sentinel;
    std::cin >> sentinel;
    if (sentinel != 'y' && sentinel != 'Y')
        g_is_running = false;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "Welcome to the Hi-Lo Game!" << endl;
    cout << "Please guess a number between 1 and 100." << endl;
    cout << "*****************************************" << endl << endl;

    do {
        GameLoop();
        cout << "*****************************************" << endl << endl;
    } while (g_is_running);

    cout << "Game End" << endl;
    return 0;
}