#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 30;
const int height = 30;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, REIGHT, UP, DOWN };
eDirection dir;

void Setup(){ //параметры игры
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Drow() {
    system("cls");  //очистка поля

    //рамка/поле
    for (int i = 1; i <= width; i++) {
        for (int j = 1; j <= height; j++) {
            if ((j == 1 || j == height) || (i == 1 || i == width))
                cout << "#";
            else
                cout << " ";
            if (i == y && j == x)   //рисовка змейки
                cout << "~";
            else if (i == fruitY && j == fruitX)
                cout << "*";
            else {
                bool print = false;
                for (int num = 0; num < nTail; num++){
                    if(tailX[num] == j && tailY[num] == i){
                        print = true;
                        cout << "~";
                }
                if(!print)
                    cout << " ";
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void Input() ;{
    if (_kbhit ()){
        switch (_getch ())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = REIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'q':
            gameOver = true;
            break;

        }
    }
}

void Logic() {  //логика игры
    int prevX = tailX[0];   //хвост
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++){
        prev2X = tailX[1];
        prev2Y = tailY[1];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case REIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if (x > width || x < 1 || y > height || y < 1)
        gameOver = true;
    if (x == fruitX && y == fruitY) {
        score += 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while(!gameOver){
        Drow();
        Input();
        Logic();
    }
}