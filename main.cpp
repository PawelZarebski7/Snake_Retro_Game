#include <iostream>
#include <conio.h> // getch()
#include <cstdlib>
#include <time.h>
#include <windows.h>

using namespace std;

int width, height, speedGame;
int keyUP, keyDOWN, keyLeft, keyRight;
int XSnake, YSnake;
int XFood, YFood;
int gameKey;
int snakeLenght = 3, historyX[10000], historyY[10000];
int howMuch = 0;
char snakeSign = 219, eatSign = 177, pd = 188, pg = 187, lg = 201, ld = 200, poz = 205, pio = 186;
char destinatiON = 'p';
char fieldGame[35][35];

void gotoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X=x;
    dwPos.Y=y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

warningForThePlayer() {
    cout << "Number out of range !! Bastard !!" << endl;
    cout << "You have last chance. Enter the width of the board from 5 to 35:" << endl;
    cin >> width;
    if (width<5 || width>35) width=15;
}

warningForThePlayerTwo(){
    cout << "Number out of range !! Bastard !!" << endl;
    cout << "You have last chance. Enter the height of the board from 5 to 35:" << endl;
    cin >> height;
    if (height<5 || height>35) height=15;
}

int main()
{
    cout << "Enter the width of the board from 5 to 35" << endl;
    cin >> width;
    if (width < 5 || width > 35) warningForThePlayer();

    cout << "Enter the height of the board from 5 to 35" << endl;
    cin >> height;
    if (height < 5 || height > 35) warningForThePlayerTwo();

    cout << "Enter the speed of Snake game from 1 to 10: " << endl;
    cin >> speedGame;
    if (speedGame < 1) speedGame = 1;
    if (speedGame > 10) speedGame = 10;

    cout << "Press the keys you want to play" << endl;
    cout << "KeyUP" << endl;
    keyUP = getch();
    if(keyUP==224) keyUP = keyUP + getch();
    if(keyUP==0) keyUP = keyUP - getch();

    cout << "KeyDOWN" << endl;
    keyDOWN = getch();
    if(keyDOWN==224) keyDOWN = keyDOWN + getch();
    if(keyDOWN==0) keyDOWN = keyDOWN - getch();

    cout << "KeyLEFT" << endl;
    keyLeft = getch();
    if(keyLeft==224) keyLeft = keyLeft + getch();
    if(keyLeft==0) keyLeft = keyLeft - getch();

    cout << "KeyRIGHT" << endl;
    keyRight = getch();
    if(keyRight==224) keyRight = keyRight + getch();
    if(keyRight==0) keyRight = keyRight - getch();

    // cout << keyDOWN << " " << keyUP << " " << keyLeft << " " <<keyRight;

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            fieldGame[j][i] = 'p';
        }
    }

    srand(time(NULL));

    XSnake=rand()%width;
    YSnake=rand()%height;

    fieldGame[XSnake][YSnake]='w';

    do {
    XFood=rand()%width;
    YFood=rand()%height;
    } while (fieldGame[XFood][YFood] != 'p');

    fieldGame[XFood][YFood] = 'j';

    system("cls");

    gotoxy(0,0); // back to start drawing

    cout << lg;
    for (int i=0; i < width; i++) {
        cout << poz << poz;
    }

    cout << pg;

    for (int i=0; i < height; i++){
        cout << endl << pio;
        for(int j=0; j<width; j++)
        {
            if(fieldGame[j][i] == 'p') cout << "  ";
            if(fieldGame[j][i] == 'w') cout << snakeSign << snakeSign;
            if(fieldGame[j][i] == 'j') cout << eatSign << eatSign;
        }
        cout << pio;
    }

    cout << endl;

    cout << ld;

    for (int i=0; i < width; i++) {
        cout << poz << poz;
    }
    cout << pd;

    for(;;) {
    // drawing a board
        howMuch++;
        historyX[howMuch] = XSnake;
        historyY[howMuch] = YSnake;





    Sleep(500/speedGame);

    if(kbhit())
    {
        gameKey = getch();
        if(gameKey==224) gameKey += getch();
        if(gameKey==0) gameKey -= getch();

        if(gameKey==keyUP  && (destinatiON =='l' || destinatiON =='p')) destinatiON = 'g';
        if(gameKey==keyDOWN && (destinatiON =='l' || destinatiON =='p')) destinatiON = 'd';
        if(gameKey==keyLeft && (destinatiON =='g' || destinatiON =='d')) destinatiON = 'l';
        if(gameKey==keyRight && (destinatiON =='g' || destinatiON =='d')) destinatiON = 'p';
    }


    if(destinatiON == 'd') YSnake++;
    if(destinatiON == 'g') YSnake--;
    if(destinatiON == 'l') XSnake--;
    if(destinatiON == 'p') XSnake++;


    if(XSnake==width) XSnake=0;
    if(XSnake==-1) XSnake=width-1;
    if(YSnake==height) YSnake=0;
    if(YSnake==-1) YSnake= height-1;

    if(fieldGame[XSnake][YSnake] == 'w') // snake eat snake
    {
        break;
    }

    if(fieldGame[XSnake][YSnake] == 'j') // after eat
    {
        snakeLenght++;

        do {
            XFood=rand()%width;
            YFood=rand()%height;
        } while (fieldGame[XFood][YFood] != 'p');

    fieldGame[XFood][YFood] = 'j';
    gotoxy(XFood*2+1,YFood+1);
    cout << eatSign << eatSign;
    }
    else {fieldGame[historyX[howMuch - snakeLenght]][historyY[howMuch - snakeLenght]] = 'p';
    gotoxy(historyX[howMuch - snakeLenght]*2+1,historyY[howMuch - snakeLenght]+1);
    cout << "  ";}
    fieldGame[XSnake][YSnake] = 'w';
    gotoxy(XSnake*2+1,YSnake+1);
    cout << snakeSign << snakeSign;

    }


    if (speedGame == 10)
    {
        gotoxy(0, height+4);
        cout << endl << "LEVEL MASTER !";
    }
    cout << endl << "\a\a\aGAME OVER. YOUR SCORE: " << snakeLenght + 1 << ".";

}
