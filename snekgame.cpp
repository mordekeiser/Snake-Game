#include <iostream>
#include <unistd.h> 
#include <termios.h> 
#include <cstdlib>   
#include <ctime>    
#include <fcntl.h> 
using namespace std;

const int WIDTH = 30; 
const int HEIGHT = 20; 
int x, y, fruitX, fruitY, superFruitX, superFruitY, score, highScore = 0;
int tailX[100], tailY[100], tailLength;
bool gameOver, superFruitExists = false;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void setup();
void draw();
void input();
void logic();
void displayMenu();
void endScreen();
void clearScreen();
char getInput();

int main() {
    while (true) {
        displayMenu();
        char choice;
        cin >> choice;

        if (choice == '1') {
            setup();
            while (!gameOver) {
                draw();
                input();
                logic();
                usleep(150000); 
            }
            endScreen();
        } else if (choice == '2') {
            clearScreen();
            cout << "======================" << endl;
            cout << "      HIGH SCORE      " << endl;
            cout << "======================" << endl;
            cout << "High Score: " << highScore << endl;
            cout << "Press any key to return to the menu..." << endl;
            cin.ignore();
            cin.get();
        } else if (choice == '3') {
            clearScreen();
            cout << "Exiting... Thank you for playing!" << endl;
            break;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}

void setup() {
    srand(time(0));
    gameOver = false;
    dir = RIGHT; 
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    superFruitExists = false; 
    score = 0;
    tailLength = 2;
}
void draw() {
    clearScreen();
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) cout << "#";
            if (i == y && j == x)
                cout << "O"; 
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else if (superFruitExists && i == superFruitY && j == superFruitX)
                cout << "S";
            else {
                bool isTail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; 
                        isTail = true;
                    }
                }
                if (!isTail) cout << " ";
            }
            if (j == WIDTH - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;

    cout << "Score: " << score << " | High Score: " << highScore << endl;
}

void input() {
    char key = getInput(); 
    switch (key) {
        case 'w': if (dir != DOWN) dir = UP; break;
        case 'a': if (dir != RIGHT) dir = LEFT; break;
        case 's': if (dir != UP) dir = DOWN; break;
        case 'd': if (dir != LEFT) dir = RIGHT; break;
        case 'x': gameOver = true; break;
    }
}

void logic() {
    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) gameOver = true;
    for (int i = 0; i < tailLength; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        if (score > highScore) highScore = score;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        tailLength++;
    }
    if (superFruitExists && x == superFruitX && y == superFruitY) {
        score += 50;
        if (score > highScore) highScore = score;
        superFruitExists = false; 
        tailLength += 3;        
    }

    if (!superFruitExists && rand() % 100 < 5) { 
        superFruitX = rand() % WIDTH;
        superFruitY = rand() % HEIGHT;
        superFruitExists = true;
    }
}

void displayMenu() {
    clearScreen();
    cout << "======================" << endl;
    cout << "   WELCOME TO SNAKE   " << endl;
    cout << "======================" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. View High Score" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

void endScreen() {
    clearScreen();
    cout << "======================" << endl;
    cout << "      GAME OVER       " << endl;
    cout << "======================" << endl;
    cout << "Your Score: " << score << endl;
    cout << "High Score: " << highScore << endl;
    cout << "Play Again? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        setup();
    }
}

void clearScreen() {
    cout << "\033[2J\033[1;1H"; 
    cout.flush(); 
}

char getInput() {
    struct termios oldt, newt;
    char ch = 0;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
}