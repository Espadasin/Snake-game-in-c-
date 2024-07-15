#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;

//Game
bool running = true;
int windowX = 52, windowY = 13;

//Player Variables
int playerScore;

//Snake Variables
int snakeX,snakeY;
int tailX[100], tailY[100];
int tailLen;
enum snakeStates{STOP = 0, LEFT, RIGHT, UP, DOWN};
snakeStates dir;

//Apple Variables
int appleX, appleY;

void GameInit(){
    running = true;
    playerScore = 0;
    dir = STOP;
    snakeX = windowX / 2;
    snakeY = windowY / 2;
    appleX = rand() % windowX;
    appleY = rand() % windowY;
}

void GameRender(string playerName){
    system("cls");
    
    string LastAndFirstRow(windowX, '-');

    cout << LastAndFirstRow << endl;


    for(int y = 0; y < windowY; y++){
        string bg(windowX, ' ');
        bg[0] = '|';
        bg[windowX - 1] = '|';

        if(y == snakeY){
            bg[snakeX] = '0';
        }
        
        if(y == appleY){
            bg[appleX] = '#';
        }

        for(int t = 0; t < tailLen; t++){
            if(y == tailY[t]){
                bg[tailX[t]] = 'o';
            }
        }


        cout << bg << endl;
    }


    cout << LastAndFirstRow << endl;

    cout << "Your name is: " << playerName << endl << "Score: " << playerScore << endl;


};

void GetInput(){

    if(kbhit()){
        switch(getch()){
            case 'd':
                dir = RIGHT;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'w':
                dir = UP;
                break;
        }
    }
}

void GameUpdate(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prevX2, prevY2;
    tailX[0] = snakeX;
    tailY[0] = snakeY;

    for(int t = 1; t < tailLen; t++){
        prevX2 = tailX[t];
        prevY2 = tailY[t];
        tailX[t] = prevX;
        tailY[t] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }

    switch(dir){
        case 2:
            snakeX++;
            break;
        case 1:
            snakeX--;
            break;
        case 4:
            snakeY++;
            break;
        case 3:
            snakeY--;
            break;
    }

    if(snakeX == 0 || snakeX == windowX || snakeY < 0 || snakeY == windowY){
        running = false;
    }
    
    if(snakeX == appleX && snakeY == appleY){
        appleX = rand() % windowX;
        appleY = rand() % windowY;
        playerScore += 10;
        tailLen++;
    }

    GetInput();
}

int main(){
    GameInit();

    string playerNameCMD;
    
    cout << "What's your name?: " << endl;
    cin >> playerNameCMD;

    while(running){
        GameRender(playerNameCMD);
        GameUpdate();
        Sleep(100);
    }
    return 0;
}