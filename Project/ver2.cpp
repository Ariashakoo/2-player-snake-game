#include "clui.h"
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
using namespace std;
int timer = 0;
int hours = 0;
int minutes = 0;
int seconds = 0;
int score1, score2, Gamemode;
enum direction
{
    Stop = 0,
    Left,
    Right,
    Up,
    Down
};
enum directioon
{
    stop = 0,
    lleft,
    rright,
    up,
    down
};

struct Player
{
    string name;
    int score;
};

direction dir; // dir stands for direction
directioon dir1;
const int width = 30, height = 20;
string name1, name2;
bool gameover;

struct coord
{
    int x, y;
};
coord tail1[2000], tail2[2000];
coord player1, player2, Fruit, bomb;
int tail_length1, tail_length2;
void hidecursor() // a solution for the showing of cursur.
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void panel()
{
    change_color_rgb(255, 51, 70);
    cursor_to_pos(0, 0);
    cout << "-------------------------------------------------" << endl;
    restore_cursor();
    reset_color();
    change_color_rgb(51, 246, 255);
    cursor_to_pos(2, 0);
    cout << "Welcome to 2 player snake game ! :)" << endl;
    cout << "The control keys for the second player are arrow keys " << endl;
    cout << "Please Enter your names and select the game mode :') " << endl;
    delay(6000);
    clear_screen();
    cout << "The first name will be : ";
    cin >> name1;
    cout << "The second name will be : ";
    cin >> name2;
    clear_screen();
    reset_color();
    restore_cursor();
    change_color_rgb(171, 249, 5);
    cout << "The game modes : " << endl;
    cout << "1.Slow and easy " << endl;
    cout << "2.Medium speed and difficulty" << endl;
    cout << "3.Fast and Hard" << endl;
    cin >> Gamemode;
    reset_color();
    change_color_rgb(255, 51, 70);
    cout << "-------------------------------------------------" << endl;
    reset_color();
}
void setup()
{
    player1.x = 8;
    player1.y = 0;
    player2.x = width - 8;
    player2.y = 0;
    Fruit.x = rand() % (width - 2) + 1;
    Fruit.y = rand() % (height - 2) + 1;
    bomb.x = rand() % (width - 2) + 1;
    bomb.y = rand() % (height - 2) + 1;
    tail_length1 = 3;
    tail_length2 = 3;
    dir = Stop;
    dir1 = stop;
    gameover = false;
}
void snake1_coo()
{
    for (int i = 0; i <= tail_length1; i++)
    {
        tail1[i].x = player1.x - i - 1;
        tail1[i].y = player1.y;
    }
}
void snake2_coo()
{
    for (int i = 0; i <= tail_length2; i++)
    {
        tail2[i].x = player2.x + i + 1;
        tail2[i].y = player2.y;
    }
}
void draw()
{                   // the box and movement
    clear_screen(); // it deletes the frame and remakes it
    if (dir == Stop)
    {
        snake1_coo();
    }
    if (dir1 == stop)
    {
        snake2_coo();
    }
    for (int i = 0; i < width; i++)
    {
        change_color(13);
        cout << "#";
        reset_color();
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 or j == width - 1)
            {
                change_color(13);
                cout << "#";
                reset_color();
            }
            else if (j == player1.x and i == player1.y)
            {
                change_color(10);
                cout << "O";
                reset_color();
            }
            else if (j == Fruit.x and i == Fruit.y)
            {
                change_color(3);
                cout << "F";
                reset_color();
            }
            else if (j == bomb.x and i == bomb.y)
            {
                change_color(15);
                cout << "B";
                reset_color();
            }
            else if (j == player2.x and i == player2.y)
            {
                change_color(2);
                cout << "O";
                reset_color();
            }
            else
            {
                bool flag = false;
                for (int k = 0; k < tail_length1; k++)
                {
                    if (j == tail1[k].x and i == tail1[k].y)
                    {
                        change_color(10);
                        cout << "o";
                        reset_color();
                        flag = true;
                    }
                }
                for (int k = 0; k < tail_length2; k++)
                {
                    if (j == tail2[k].x and i == tail2[k].y)
                    {
                        change_color(2);
                        cout << "o";
                        reset_color();
                        flag = true;
                    }
                }
                if (!flag)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; i++)
    {
        change_color(13);
        cout << "#";
        reset_color();
    }
    cout << " \n --------------------------------------------------------" << endl;
    cout << "Score player1 : " << score1 << endl;
    cout << "Score player2 : " << score2 << endl;
    cout << "| Hours : " << hours << " Minutes :" << minutes << " Seconds : " << seconds << "|" << endl;
    // cout << player2.x << " , " << player2.y << endl;
    // cout << tail2[1].x << "," << tail2[1].y << endl;
    // cout << tail2[2].x << "," << tail2[2].y << endl;
    // cout << tail2[3].x << " , " << tail2[3].y << endl;
}

void input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'w':
        case 'W':
            dir = Up;
            break;
        case 72:
            dir1 = up;
            break;
        case 's':
        case 'S':
            dir = Down;
            break;
        case 80:
            dir1 = down;
            break;
        case 'a':
        case 'A':
            dir = Left;
            break;
        case 75:
            dir1 = lleft;
            break;
        case 'd':
        case 'D':
            dir = Right;
            break;
        case 77:
            dir1 = rright;
            break;
        default:
            break;
        }
    }
}

void logic()
{
    for (int i = tail_length1 - 1; i >= 1; i--)
    {
        tail1[i].x = tail1[i - 1].x;
        tail1[i].y = tail1[i - 1].y;
    }
    tail1[0].x = player1.x;
    tail1[0].y = player1.y;
    for (int i = tail_length2 - 1; i >= 1; i--)
    {
        tail2[i].x = tail2[i - 1].x;
        tail2[i].y = tail2[i - 1].y;
    }
    tail2[0].x = player2.x;
    tail2[0].y = player2.y;
    switch (dir)
    {
    case Left:
        player1.x = player1.x - 1;
        break;
    case Right:
        player1.x = player1.x + 1;
        break;
    case Up:
        player1.y = player1.y - 1;
        break;
    case Down:
        player1.y = player1.y + 1;
        break;
    default:
        break;
    }
    switch (dir1)
    {
    case lleft:
        player2.x = player2.x - 1;
        break;
    case rright:
        player2.x = player2.x + 1;
        break;
    case up:
        player2.y = player2.y - 1;
        break;
    case down:
        player2.y = player2.y + 1;
        break;
    default:
        break;
    }
    if (player1.x == width - 1 or player1.x == 0 or player1.y == -1 or player1.y == height)
    {
        Beep(440, 1000);
        gameover = true;
    }
    if (player1.x == bomb.x and player1.y == bomb.y)
    {
        Beep(440, 1000);
        gameover = true;
    }
    if (player2.x == width - 1 or player2.x == 0 or player2.y == -1 or player2.y == height)
    {
        Beep(440, 1000);
        gameover = true;
    }
    if (player2.x == bomb.x and player2.y == bomb.y)
    {
        Beep(440, 1000);
        gameover = true;
    }
    if (player1.x == player2.x and player1.y == player2.y)
    {
        Beep(440, 1000);
        gameover = true;
    }
    if(score1>=10){
        for (int i = 0; i <= tail_length2; i++)
        {
            if (player1.x == tail1[i].x and player1.y == tail1[i].y)
            {
                Beep(440, 1000);
                gameover = true;
                break;
            }
        }
    }
    if (score2 >= 10)
    {
        for (int i = 0; i <= tail_length2; i++)
        {
            if (player2.x == tail2[i].x and player2.y == tail2[i].y)
            {
                Beep(440, 1000);
                gameover = true;
                break;
            }
        }
    }
    for (int i = 0; i <= tail_length2; i++)
    {
        if (player1.x == tail2[i].x and player1.y == tail2[i].y)
        {
            Beep(440, 1000);
            gameover = true;
            break;
        }
    }
    for (int i = 0; i <= tail_length2; i++)
    {
        if (player2.x == tail1[i].x and player2.y == tail1[i].y)
        {
            Beep(440, 1000);
            gameover = true;
            break;
        }
    }
    if (player1.x == Fruit.x and player1.y == Fruit.y)
    {
        Beep(523, 500);
        score1 += 10;
        Fruit.x = rand() % (width - 2) - 1;
        Fruit.y = rand() % (height - 2) - 1;
        tail_length1++;
    }
    else if (player2.x == Fruit.x and player2.y == Fruit.y)
    {
        Beep(523, 500);
        score2 += 10;
        Fruit.x = rand() % (width - 2) - 1;
        Fruit.y = rand() % (height - 2) - 1;
        tail_length2++;
    }
}

void saveGame(string name1, string name2, int score1, int score2)
{

    ofstream file("LeaderBoard.txt", ios::app);
    if (file.is_open())
    {
        file << name1 << " - " << score1 << "\n"
             << name2 << " - " << score2 << "\n";
        file.close();
    }
    else
    {
        cout << endl
             << "Unable to open the file." << endl;
    }
}

int sortHelper(const Player &player1, const Player &player2)
{
    if (player2.score < player1.score)
        return 1;
    return 0;
}

void displayLeaderBoard()
{
    clear_screen();
    string line, word;
    ifstream file("LeaderBoard.txt");
    int l = 0;
    if (file.is_open())
    {
        while (getline(file, line))
            l++;

        file.clear();
        file.seekg(0);

        Player player[l];

        int i = 0;
        while (getline(file, line))
        {
            int j = 0;
            if (i == 0)
            {
                file.clear();
                file.seekg(0);
            }

            while (file >> word)
            {
                if (word == "-")
                    continue;

                switch (j)
                {
                case 0:
                    player[i].name = word;
                    break;
                case 1:
                    player[i].score = stoi(word);
                    break;
                }
                if (j == 1)
                    break;

                j++;
            }

            i++;
        }

        Player *playerLength = player + sizeof(player) / sizeof(player[0]);
        sort(player, playerLength, sortHelper);

        int counter = 0;
        for (int i = 0; i < l; i++)
        {
            string name = player[i].name;

            for (int j = i + 1; j < l - counter; j++)
            {
                if (player[j].name == name)
                {
                    player[i].score += player[j].score;
                    swap(player[j], player[l - 1 - counter]);
                    counter++;
                }
            }
        }

        cout << "\033[32m"
             << setw(8) << left << "Rank" << setw(8)
             << "  |  "
             << setw(8) << left << "Name" << setw(8)
             << "  |  "
             << setw(8) << left << "Score" << setw(8) << "\033[37m" << endl;

        for (int i = 0; i < l - counter; i++)
        {
            cout << "\033[34m"
                 << setw(8) << left << i + 1 << setw(8) << "  |  "
                 << setw(8) << left << player[i].name << setw(8) << "  |  "
                 << setw(8) << left << player[i].score << setw(8) << "\033[37m" << endl;
        }

        file.close();

        ofstream fileOutput("LeaderBoard.txt", ios::trunc);
        if (fileOutput.is_open())
        {
            for (int i = 0; i < l - counter; i++)
            {
                fileOutput << player[i].name << " - " << player[i].score << "\n";
            }
        }

        fileOutput.close();
    }
    else
    {
        cout << endl
             << "\033[31m"
             << "No Data available, please play first"
             << "\033[37m" << endl;
    }
}

int main()
{
    srand(time(NULL));
    clear_screen();
    panel();
    setup();
    switch (Gamemode)
    {
    case 1:
        while (!gameover)
        {
            draw();
            seconds++;
            if (seconds == 60)
            {
                minutes++;

                if (minutes == 60)
                {
                    hours++;
                    minutes = 0;
                }

                seconds = 0;
            }
            input();
            logic();

            delay(200); // it allows fps for slower speed increase the number and faster speed decrease the number
            hidecursor();
            // timer++;
        }
        break;
    case 2:
        while (!gameover)
        {
            draw();
            seconds++;
            if (seconds == 60)
            {
                minutes++;

                if (minutes == 60)
                {
                    hours++;
                    minutes = 0;
                }

                seconds = 0;
            }
            input();
            logic();

            delay(100); // it allows fps, for slower speed increase the number and faster speed decrease the number
            hidecursor();
            // timer++;
        }
        break;
    case 3:
        while (!gameover)
        {
            ShowCursor(false);
            draw();
            seconds++;
            if (seconds == 60)
            {
                minutes++;

                if (minutes == 60)
                {
                    hours++;
                    minutes = 0;
                }

                seconds = 0;
            }
            input();
            logic();

            delay(50); // it allows fps for slower speed increase the number and faster speed decrease the number
            hidecursor();
            // timer++;
        }
        break;
    }
    /*while (!gameover)
    {
        draw();
        input();
        logic();

        delay(200); // it allows fps for slower speed increase the number and faster speed decrease the number
        hidecursor();
        // timer++;
    }
    */

    if (gameover)
    {
        saveGame(name1, name2, score1, score2);
        displayLeaderBoard();
    }

    getch();
    return 0;
}
