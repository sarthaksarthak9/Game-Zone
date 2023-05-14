#include <bits/stdc++.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
using namespace std;
char board[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
void display_board()
{
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "                                                                    -------------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "                                                                    | ";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " | ";
        }
        cout << endl;
        cout << "                                                                    -------------" << endl;
    }
}

bool is_valid_move(int row, int col)
{
    if (row < 0 || row > 2 || col < 0 || col > 2)
    {
        return false;
    }
    if (board[row][col] == 'X' || board[row][col] == 'O')
    {
        return false;
    }
    return true;
}

bool has_won(char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return true;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return true;
    }
    return false;
}

void play_game()
{
    char player = 'X';
    int row, col;
    while (!has_won('X') && !has_won('O'))
    {

        display_board();
        cout << "PLAYER " << player << " TURN.ENTER ROW AND COLUMN ";
        cin >> row >> col;
        if (is_valid_move(row - 1, col - 1))
        {
            board[row - 1][col - 1] = player;
            if (player == 'X')
            {
                player = 'O';
            }
            else
            {
                player = 'X';
            }
            system("cls");
        }
        else
        {
            system("cls");
            cout << "INVALID MOVE. TRY AGAIN!" << endl;
            sleep(2);
            system("cls");
        }
    }
    display_board();

    if (has_won('X'))
    {
        cout << "PLAYER X HAS WON!" << endl;
    }
    else
    {
        cout << "PLAYER O HAS WON!" << endl;
    }
}

void displayBoard(char board[])
{
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl;

    cout << "                                                                    " << board[0] << " | " << board[1] << " | " << board[2] << " " << endl;
    cout << "                                                                   ---+---+---" << endl;
    cout << "                                                                    " << board[3] << " | " << board[4] << " | " << board[5] << " " << endl;
    cout << "                                                                   ---+---+---" << endl;
    cout << "                                                                    " << board[6] << " | " << board[7] << " | " << board[8] << " " << endl;
}

bool checkWin(char board[], char player)
{
    for (int i = 0; i < 9; i += 3)
    {
        if (board[i] == player && board[i + 1] == player && board[i + 2] == player)
        {
            return true;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player)
        {
            return true;
        }
    }

    if (board[0] == player && board[4] == player && board[8] == player)
    {
        return true;
    }
    if (board[2] == player && board[4] == player && board[6] == player)
    {
        return true;
    }

    return false;
}

bool checkTie(char board[])
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
        {
            return false;
        }
    }

    return true;
}

int minimax(char board[], char player, int depth)
{
    if (checkWin(board, 'X'))
    {
        return -10 + depth;
    }
    if (checkWin(board, 'O'))
    {
        return 10 - depth;
    }
    if (checkTie(board))
    {
        return 0;
    }

    int bestScore;
    if (player == 'O')
    {
        bestScore = -1000;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] != 'X' && board[i] != 'O')
            {
                char temp = board[i];
                board[i] = 'O';
                int score = minimax(board, 'X', depth + 1);
                board[i] = temp;
                bestScore = max(bestScore, score);
            }
        }
    }
    else
    {
        bestScore = 1000;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] != 'X' && board[i] != 'O')
            {
                char temp = board[i];
                board[i] = 'X';
                int score = minimax(board, 'O', depth + 1);

                board[i] = temp;
                bestScore = min(bestScore, score);
            }
        }
    }
    return bestScore;
}

void makeMove(char board[])
{
    int bestScore = -1000;
    int bestMove = -1;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
        {
            char temp = board[i];
            board[i] = 'O';
            int score = minimax(board, 'X', 0);
            board[i] = temp;

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    board[bestMove] = 'O';
}

void playGame()
{
    char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    srand(time(NULL));
    bool playerTurn = rand() % 2 == 0;
    while (!checkWin(board, 'X') && !checkWin(board, 'O') && !checkTie(board))
    {
        displayBoard(board);

        if (playerTurn)
        {
            int move;
        again:
            cout << "ENTER YOUR MOVE(1-9): ";
            cin >> move;
            if (move > 9 || move < 1)
            {
                cout << "INVALID MOVE " << endl;
                sleep(2);
                system("cls");
                displayBoard(board);

                goto again;
            }
            while (board[move - 1] == 'X' || board[move - 1] == 'O')
            {
                system("cls");
                cout << "INVALID MOVE.ENTER YOUR MOVE (1-9)";
                cin >> move;
            }

            board[move - 1] = 'X';
        }
        else
        {
            system("cls");

            cout << "COMPUTER'S TURN" << endl;
            makeMove(board);
        }

        playerTurn = !playerTurn;
    }

    displayBoard(board);

    if (checkWin(board, 'X'))
    {
        cout << "YOU WIN!" << endl;
    }
    else if (checkWin(board, 'O'))
    {

        cout << "COMPUTER WINS!" << endl;
    }
    else
    {
        cout << "TIE GAME!" << endl;
    }
}

void display(vector<vector<int>> &board);
void solution(int ch);

class Set_Board
{
    int **board = new int *[9];

public:
    Set_Board()
    {
        for (int i = 0; i < 9; i++)
        {
            board[i] = new int[9];
        }
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                board[i][j] = 0;
            }
        }
    }
    int **getEasy()
    {
        board[0][2] = 4;
        board[0][4] = 5;
        board[1][0] = 9;
        board[1][3] = 7;
        board[1][4] = 3;
        board[1][5] = 4;
        board[1][6] = 6;
        board[2][2] = 3;
        board[2][4] = 2;
        board[2][5] = 1;
        board[2][7] = 4;
        board[2][8] = 9;
        board[3][1] = 3;
        board[3][2] = 5;
        board[3][4] = 9;
        board[3][6] = 4;
        board[3][7] = 8;
        board[4][1] = 9;
        board[4][7] = 3;
        board[5][1] = 7;
        board[5][2] = 6;
        board[5][4] = 1;
        board[5][6] = 9;
        board[5][7] = 2;
        board[6][0] = 3;
        board[6][1] = 1;
        board[6][3] = 9;
        board[6][4] = 7;
        board[6][6] = 2;
        board[7][2] = 9;
        board[7][3] = 1;
        board[7][4] = 8;
        board[7][5] = 2;
        board[7][8] = 3;
        board[8][4] = 6;
        board[8][6] = 1;
        return board;
    }
    int **getMedium()
    {
        board[0][2] = 7;
        board[0][6] = 5;
        board[0][8] = 4;
        board[1][0] = 6;
        board[1][1] = 4;
        board[1][8] = 3;
        board[2][1] = 3;
        board[2][2] = 1;
        board[2][3] = 9;
        board[2][8] = 7;
        board[3][3] = 8;
        board[3][4] = 3;
        board[3][7] = 7;
        board[4][0] = 2;
        board[4][3] = 7;
        board[4][7] = 6;
        board[5][0] = 7;
        board[5][1] = 5;
        board[5][7] = 4;
        board[6][0] = 9;
        board[6][5] = 8;
        board[6][7] = 5;
        board[6][8] = 1;
        board[7][3] = 4;
        board[7][4] = 2;
        board[7][5] = 9;
        board[7][8] = 6;
        board[8][4] = 6;
        board[8][6] = 9;
        board[8][7] = 8;
        return board;
    }
    int **getHard()
    {
        board[0][2] = 2;
        board[0][3] = 7;
        board[0][6] = 8;

        board[1][2] = 4;
        board[1][5] = 8;
        board[1][8] = 6;
        board[2][4] = 6;
        board[2][5] = 3;
        board[3][1] = 4;
        board[3][3] = 8;
        board[3][7] = 5;
        board[4][2] = 1;
        board[4][3] = 9;
        board[4][6] = 7;
        board[6][1] = 9;
        board[6][3] = 4;
        board[6][6] = 1;
        board[7][1] = 3;
        board[7][6] = 6;
        board[8][1] = 5;
        board[8][3] = 3;
        board[8][4] = 9;
        board[8][8] = 7;

        return board;
    }
};

int c = 0;
bool isSafe(int row, int col, vector<vector<int>> &board, int val)
{
    for (int i = 0; i < board.size(); i++)
    {
        if (board[row][i] == val)
        {
            return false;
        }
        if (board[i][col] == val)
        {
            return false;
        }
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == val)
        {
            return false;
        }
    }
    return true;
}

bool solve(vector<vector<int>> &board)
{
    c++;
    int n = board[1].size();

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (board[row][col] == 0)
            {
                for (int var = 1; var <= 9; var++)
                {
                    if (isSafe(row, col, board, var))
                    {
                        board[row][col] = var;
                        bool ispossible = solve(board);
                        if (ispossible)
                        {
                            return true;
                        }
                        else
                        {
                            board[row][col] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool isValid(int row, int col, int ch)
{
    vector<int> r, c;
    switch (ch)
    {
    case 1:
        r = {0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8};
        c = {2, 4, 0, 3, 4, 5, 6, 2, 4, 5, 7, 8, 1, 2, 4, 6, 7, 1, 7, 1, 2, 4, 6, 7, 0, 1, 3, 4, 6, 2, 3, 4, 5, 8, 4, 6};
        break;

    case 2:
        r = {0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8};
        c = {2, 6, 8, 0, 1, 8, 1, 2, 3, 8, 3, 4, 7, 0, 3, 7, 0, 1, 7, 0, 5, 7, 8, 3, 4, 5, 8, 4, 6, 7};
        break;

    case 3:
        r = {0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 6, 6, 6, 7, 7, 8, 8, 8, 8};
        c = {2, 3, 6, 2, 5, 8, 4, 5, 1, 3, 7, 2, 3, 6, 1, 3, 6, 1, 6, 1, 3, 4, 8};
        break;
    }
    for (int i = 0; i < r.size(); i++)
    {
        if (r[i] == row && c[i] == col)
        {
            return false;
        }
    }
    return true;
}

void input(vector<vector<int>> &board, int ch)
{
    int r, c, value = 0;
    int l = 0;
    do
    {
    st:
        display(board);
        cout << "ENETR ROW AND COLUMN TO BE FILLED(R,C) : " << endl;
        cin >> r >> c;
        if (r > 9 || r < 1 || c > 9 || c < 1)
        {
            system("cls");
            cout << "                                                           INVALID INPUT" << endl;
            cout << "                                                             RESETING";
            for (long long int i = 0; i < 7; i++)
            {
                cout << ".";
                for (long long int j = 0; j < 9999; j++)
                {
                    for (long long int k = 0; k < 10000; k++)
                    {
                    }
                }
            }
            system("cls");
            goto st;
        }
        if (isValid(r - 1, c - 1, ch))
        {
            cout << "Enter value : " << endl;
            cin >> value;
            if (isSafe(r - 1, c - 1, board, value))
            {
                board[r - 1][c - 1] = value;
            }
            else
            {
                cout << "**ALREADY FILLED**" << endl;
                sleep(2);
            }
            system("cls");
        }
        else
        {
            cout << "**ALREADY FILLED**" << endl;
        }
        cout << "PRESS 1 TO CONTINUE. \nPRESS 2 TO EXIT...\nPRESS 3 FOR HINT \n"
             << endl;
        cin >> l;
        if (l == 3)
        {
            system("cls");
            cout << "\n\nSOLUTION : " << endl;
            solution(ch);
            sleep(2);
            system("cls");
        }

    } while (l != 2);
}
void display(vector<vector<int>> &board)
{
    cout << "\n   1   2   3   4   5   6   7   8   9" << endl;
    cout << "   -----------------------------------" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << "|  ";
        for (int j = 0; j < 9; j++)
        {
            if (j == 2 || j == 5)
            {
                cout << board[i][j] << "|  ";
            }
            else
            {
                cout << board[i][j] << "   ";
            }
        }
        cout << endl;
    }

    cout << "   -----------------------------------" << endl;

    for (int i = 3; i < 6; i++)
    {
        cout << i + 1 << "|  ";
        for (int j = 0; j < 9; j++)
        {
            if (j == 2 || j == 5)
            {
                cout << board[i][j] << "|  ";
            }
            else
            {
                cout << board[i][j] << "   ";
            }
        }
        cout << endl;
    }

    cout << "   -----------------------------------" << endl;

    for (int i = 6; i < 9; i++)
    {
        cout << i + 1 << "|  ";
        for (int j = 0; j < 9; j++)
        {
            if (j == 2 || j == 5)
            {
                cout << board[i][j] << "|  ";
            }
            else
            {
                cout << board[i][j] << "   ";
            }
        }
        cout << endl;
    }
}

void solution(int ch)
{
    Set_Board *ob = new Set_Board();
    int **temp = new int *[9];
    for (int i = 0; i < 9; i++)
    {
        temp[i] = new int[9];
    }
    switch (ch)
    {
    case 1:
        temp = ob->getEasy();
        break;

    case 2:
        temp = ob->getMedium();
        break;

    case 3:
        temp = ob->getHard();
    }
    vector<vector<int>> board(9, vector<int>(9));
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = temp[i][j];
        }
    }
    solve(board);
    display(board);
}

int main()
{
    system("cls");
    string line;
    ifstream myfile("INTRO_FILE.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    getch();
    system("cls");
    int choice;
    cout << "\033[36m";
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "                                                             LOADING";
    for (long long int i = 0; i < 7; i++)
    {
        cout << ".";
        for (long long int j = 0; j < 9999; j++)
        {
            for (long long int k = 0; k < 10000; k++)
            {
            }
        }
    }
    system("cls");
    cout << "\033[0m";

    cout << "\033[40m";
    cout << "\033[36m";

    cout << "\033[1m";
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl;

    myfile.open("ENTER_GAMEZONE.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    getch();
    cout << "\033[0m";
    cout << "\033[0m";
    cout << "\033[0m";
l:
    system("cls");
    cout << "\033[95m";
    cout << "\033[1m";
    cout << "\033[1m";
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl;
    myfile.open("CHOICE.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    cout << "\033[0m";
    cout << "\033[0m";
    cin >> choice;
    if (choice == 1)
    {
        cout << "\033[95m";
        cout << "                                                             LOADING GAME";
        for (long long int i = 0; i < 7; i++)
        {
            cout << ".";
            for (long long int j = 0; j < 9999; j++)
            {
                for (long long int k = 0; k < 10000; k++)
                {
                }
            }
        }
        system("cls");
        ifstream myfile("INSTRUCTIONS_TIC_P_VS_P.txt");
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                cout << line << '\n';
            }
            myfile.close();
        }
        else
        {
            cout << "Unable to open file";
        }
        getch();
        system("cls");
        play_game();
        cout << "\033[0m";
    }
    else if (choice == 2)
    {
        cout << "\033[92m";
        cout << "\033[1m";
        cout << "                                                             LOADING GAME";
        for (long long int i = 0; i < 7; i++)
        {
            cout << ".";
            for (long long int j = 0; j < 9999; j++)
            {
                for (long long int k = 0; k < 10000; k++)
                {
                }
            }
        }
        system("cls");
        ifstream myfile("INSTRUCTIONS_TIC_P_VS_C.txt");
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                cout << line << '\n';
            }
            myfile.close();
        }
        else
        {
            cout << "Unable to open file";
        }
        getch();
        system("cls");
        playGame();
        cout << "\033[0m";
        cout << "\033[0m";
    }
    else if (choice == 3)
    {
        cout << "\033[91m";
        cout << "\033[1m";
        cout << "                                                             LOADING GAME";
        for (long long int i = 0; i < 7; i++)
        {
            cout << ".";
            for (long long int j = 0; j < 9999; j++)
            {
                for (long long int k = 0; k < 10000; k++)
                {
                }
            }
        }
        system("cls");
        ifstream myfile("INSTRUCTIONS_SUDOKU.txt");
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                cout << line << '\n';
            }
            myfile.close();
        }
        else
        {
            cout << "Unable to open file";
        }
        getch();
        system("cls");
        int ch;
        int **temp = new int *[9];
        for (int i = 0; i < 9; i++)
        {
            temp[i] = new int[9];
        }
        cout << "                                                                  MENU" << endl;
        cout << "                                                           1 -- EASY BOARD " << endl;
        cout << "                                                           2 -- MEDIUM BOARD " << endl;
        cout << "                                                           3 -- HARD BOARD " << endl;
        cout << "                                                           ENTER YOUR CHOICE : ";
        cin >> ch;
        system("cls");
        Set_Board *ob = new Set_Board();
        switch (ch)
        {
        case 1:
            temp = ob->getEasy();
            break;

        case 2:
            temp = ob->getMedium();
            break;

        case 3:
            temp = ob->getHard();
            break;

        default:
            cout << "INVALID CHOICE " << endl;
        }
        vector<vector<int>> board(9, vector<int>(9));
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                board[i][j] = temp[i][j];
            }
        }
        input(board, ch);
        cout << c;
        return 0;
        cout << "\033[0m";
        cout << "\033[0m";
    }
    else
    {
        cout << "YOU HAVE ENTERED A WRONG INPUT, PLEASE ENETR A VALID INPUT" << endl;
        goto l;
    }
    return 0;
}