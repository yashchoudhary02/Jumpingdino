#include <iostream>
#include <conio.h> // for _kbhit() and _getch()
#include <windows.h> // for Sleep()
#include <ctime>
#include <cstdlib>

using namespace std;

bool gameOver;
const int width = 80;
const int height = 10;
int dinoX, dinoY, obstacleX, obstacleY, score;
bool jump = false;
int jumpHeight = 2;
int jumpCount = 0;

void Setup() {
    gameOver = false;
    dinoX = 1;
    dinoY = height - 1;
    obstacleX = width - 1;
    obstacleY = height - 1;
    score = 0;
    srand(time(0));
}

void Draw() {
    system("cls"); // Clear the console
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == dinoY && j == dinoX)
                cout << "D"; // Dinosaur
            else if (i == obstacleY && j == obstacleX)
                cout << "O"; // Obstacle
            else
                cout << " ";
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w': // Jump with 'w' key
            if (!jump) {
                jump = true;
                jumpCount = jumpHeight;
            }
            break;
        case 'q': // Quit the game with 'q' key
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    if (jump) {
        if (jumpCount > 0) {
            dinoY--;
            jumpCount--;
        }
        else if (jumpCount > -jumpHeight) {
            dinoY++;
            jumpCount--;
        }
        else {
            jump = false;
        }
    }

    if (obstacleX == 0) {
        obstacleX = width - 1;
        score += 10;
    }
    else
        obstacleX--;

    if (dinoX == obstacleX && dinoY == obstacleY) {
        gameOver = true;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        // Set the difficulty of the Game
        // increase the value in sleep() to decrease the speed and vice versa..
        Sleep(10); // Adjust the speed of the game
    }

    cout << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;

    return 0;
}