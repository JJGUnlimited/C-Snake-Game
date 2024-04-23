#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// boolean variable to check if the game is over or not 
bool gameOver;
//width of the board
const int width = 80;
// height of the board
const int height = 20;
//Coordinates of snake head, food coordinates, and the players score
int x, y, fruitX, fruitY, score;
// store the coordinates of snake tail (x- and y-axis)
int tailX[100], tailY[100];
// variable to store the length of the snake's tail
int nTail;
// for storing snake's moving eDirection
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
// eDirection variable
eDirecton dir;

// Function to initialize game variables
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

// Function for creating the game board & rendering
void Draw() {
    system("cls"); // Clears the screen
    
    // Creating top walls with '#'
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Creating the side walls
            if (j == 0 || j == width - 1)
                cout << "#";
            // Creating the snake head
            else if (i == y && j == x)
                cout << "O";
            // Creating the fruit
            else if (i == fruitY && j == fruitX)
                cout << "@";
            // Creating the snake tail
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                // Draw the first vertical wall
                if ((j == width / 3 || j == width / 3 - 1) && (i > 4 && i < height - 5))
                    cout << "#"; // Wall character
                // Draw the second vertical wall
                else if ((j == 2 * width / 3 || j == 2 * width / 3 - 1) && (i > 4 && i < height - 5))
                    cout << "#"; // Wall character
                else if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    // Creating bottom walls with '#'
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

// Function to handle user UserInput
void Input() {
    // Checks if a key is pressed or not 
    if (_kbhit()) {
        // Getting the pressed key
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void PlaceFruit() {
    while (true) {
        fruitX = rand() % width;
        fruitY = rand() % height;

        // Check if the fruit is placed inside the vertical walls
        bool isInsideWall = ((fruitX == width / 3 || fruitX == width / 3 - 1) && (fruitY > 4 && fruitY < height - 5)) ||
                            ((fruitX == 2 * width / 3 || fruitX == 2 * width / 3 - 1) && (fruitY > 4 && fruitY < height - 5));

        // If the fruit is not inside a wall, break the loop
        if (!isInsideWall) {
            break;
        }
    }
}

// Function for updating the game logic 
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    // Collision with the vertical walls
    if((x == width / 3 || x == width / 3 - 1) && (y > 4 && y < height - 5) ||
        (x == 2 * width / 3 || x == 2 * width / 3 - 1) && (y > 4 && y < height - 5)) {
        gameOver = true;
    }

    // Collision with the outer walls
    if (x >= width || x < 0 || y >= height || y < 0) {
        gameOver = true;
    }

    // Check collision with the tail
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // Check if fruit is eaten
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        PlaceFruit(); // Call the new PlaceFruit function
        nTail++;
    }
}

// Main function / game looping function
int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); //sleep(10);
    }
    return 0;
}
