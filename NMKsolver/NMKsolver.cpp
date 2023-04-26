#include <iostream>
//#include <bits.h>


using namespace std;

const char genALlPosMov[] = { "GEN_ALL_POS_MOV" };
const char genALlPosMovCutIfGameOver[] = { "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER" };
const char solveStateGame[] = { "SOLVE_GAME_STATE" };

bool stringComparision(const char x[], const char y[])
{
    int xSize = 0;
    int ySize = 0;
    while (x[xSize] != '\0')
    {
        xSize++;
    }
    while (y[ySize] != '\0')
    {
        ySize++;
    }
    if (xSize != ySize)
    {
        return false;
    }
    for (int i = 0; i < xSize; i++)
    {
        if (x[i] != y[i])
        {
            return false;
        }
    }
    return true;
}

void print(char* board[], int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isMovesLeft(char* board[], int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == '0')
                return true;
    return false;
}

int ifWon(int n, int m, int k, char active, char* board[])
{
    int won = 0;

    int counter = 0;

    //horizontal
    for (int i = 0; i < n; ++i)
    {
        counter = 0;

        for (int j = 0; j < m - 1; ++j)
        {
            if ((board[i][j] == board[i][j + 1]) && board[i][j] != '0')
                counter++;
            else
                counter = 0;

            if (counter >= k - 1)
            {
                if (board[i][j] == '1')
                    return 1;
                else
                    return 2;
            }
        }
    }

    //vertical
    for (int i = 0; i < m; ++i)
    {
        counter = 0;

        for (int j = 0; j < n - 1; ++j)
        {
            if ((board[j][i] == board[j + 1][i]) && board[j][i] != '0')
                counter++;
            else
                counter = 0;

            if (counter >= k - 1)
            {
                if (board[j][i] == '1')
                    return 1;
                else
                    return 2;
            }
        }
    }

    int posX = 0;
    int posY = 0;

    //diagonals
    for (int i = 0; i < n - k + 1; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            counter = 0;
            posY = i;
            posX = j;

            if (j < m - k + 1)
            {
                while (posY + 1 < n && posX + 1 < m)
                {
                    if (board[posY][posX] == board[posY + 1][posX + 1] && board[posY][posX] != '0')
                        counter++;
                    else
                        counter = 0;

                    if (counter >= k - 1)
                    {
                        if (board[posY][posX] == '1')
                            return 1;
                        else
                            return 2;
                    }

                    posY++;
                    posX++;
                }
            }

            posY = i;
            posX = j;

            if (j >= k - 1)
            {
                while (posY + 1 < n && posX - 1 >= 0)
                {
                    if (board[posY][posX] == board[posY + 1][posX - 1] && board[posY][posX] != '0')
                        counter++;
                    else
                        counter = 0;

                    if (counter >= k - 1)
                    {
                        if (board[posY][posX] == '1')
                            return 1;
                        else
                            return 2;
                    }

                    posY++;
                    posX--;
                }
            }
        }
    }

    return won;
}

void genAllMoves(int n, int m, int k, char active, char* board[], int pos)
{
    int flag = 0;

    if (ifWon(n, m, k, active, board) > 0)
    {
        pos = 0;
    }

    cout << pos << endl;

    if (pos != 0)
    {
        for (int k = 0; k < pos; ++k)
        {
            flag = 0;

            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    if (board[i][j] == '0')
                    {
                        if (flag == k)
                        {
                            cout << active << " ";
                            flag++;
                        }
                        else
                        {
                            cout << board[i][j] << " ";
                            flag++;
                        }
                    }
                    else
                        cout << board[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
}

void genAllMovesCutIfOver(int n, int m, int k, char active, char* board[], int pos)
{
    bool won = 0;

    if (ifWon(n, m, k, active, board) > 0)
    {
        pos = 0;
        cout << pos << endl;
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (board[i][j] == '0' && !won)
                {
                    board[i][j] = active;

                    if (ifWon(n, m, k, active, board) > 0)
                    {
                        pos = 1;
                        cout << pos << endl;
                        print(board, n, m);
                        won = true;
                    }
                    else
                        board[i][j] = '0';
                }
            }
        }
        if (won == 0)
            genAllMoves(n, m, k, active, board, pos);
    }
}

int minimax(char* board[], int depth, bool isMax, int pos, int n, int m, int k, int active)
{
    int pom = ifWon(n, m, k, active, board);
    if (pom == 1)
        return 10;
    if (pom == 2)
        return -10;
    if (pos == depth)
        return 0;

    cout << depth << endl;

    if (isMax)
    {
        int best = -1000;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == '0')
                {
                    board[i][j] = '1';

                    int pom = minimax(board, depth + 1, !isMax, pos, n, m, k, active);

                    if (pom > best)
                    {
                        best = pom;
                    }

                    board[i][j] = '0';

                    if (best == 10)
                        return best;
                }
            }
        }
        return best;
    }

    else
    {
        int best = 1000;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == '0')
                {
                    board[i][j] = '2';

                    int pom = minimax(board, depth + 1, !isMax, pos, n, m, k, active);

                    if (pom < best)
                    {
                        best = pom;
                    }

                    board[i][j] = '0';

                    if (best == -10)
                        return best;
                }
            }
        }
        return best;
    }
}

int findBestMove(int n, int m, int k, char active, char* board[], int pos)
{
    int bestVal = -1000;
    bool player = false;

    if (active == '1')
        player = true;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == '0')
            {
                int moveVal = minimax(board, 0, player, pos, n, m, k, active);

                if (moveVal > bestVal)
                {
                    bestVal = moveVal;
                }

                board[i][j] = '0';
            }
        }
    }

    return bestVal;
}

void solveGame(int n, int m, int k, char active, char* board[], int pos)
{
    int pom = ifWon(n, m, k, active, board);
    if (pom == 1)
        cout << "FIRST_PLAYER_WINS" << endl;
    else if (pom == 2)
        cout << "SECOND_PLAYER_WINS" << endl;
    else if (isMovesLeft(board, n, m) == false)
        cout << "BOTH_PLAYERS_TIE" << endl;
    else
    {
        int pom = findBestMove(n, m, k, active, board, pos);

        if (pom == 10)
            cout << "FIRST_PLAYER_WINS" << endl;
        if (pom == 0)
            cout << "BOTH_PLAYERS_TIE" << endl;
        if (pom == -10)
            cout << "SECOND_PLAYER_WINS" << endl;
    }
}

int main()
{
    char command[33];
    int n, m, k, possibleMoves;
    char active;
    char** board;

    while (cin >> command)
    {
        if (stringComparision(command, genALlPosMov))
        {
            cin >> n >> m >> k >> active;

            possibleMoves = 0;
            board = new char* [n];

            for (int i = 0; i < n; ++i)
            {
                board[i] = new char[m];
            }

            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    cin >> board[i][j];

                    if (board[i][j] == '0')
                        possibleMoves++;
                }
            }

            genAllMoves(n, m, k, active, board, possibleMoves);
        }

        if (stringComparision(command, genALlPosMovCutIfGameOver))
        {
            cin >> n >> m >> k >> active;

            possibleMoves = 0;
            board = new char* [n];

            for (int i = 0; i < n; ++i)
            {
                board[i] = new char[m];
            }

            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    cin >> board[i][j];

                    if (board[i][j] == '0')
                        possibleMoves++;
                }
            }
            genAllMovesCutIfOver(n, m, k, active, board, possibleMoves);
        }

        if (stringComparision(command, solveStateGame))
        {
            cin >> n >> m >> k >> active;

            possibleMoves = 0;
            board = new char* [n];

            for (int i = 0; i < n; ++i)
            {
                board[i] = new char[m];
            }

            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    cin >> board[i][j];

                    if (board[i][j] == '0')
                        possibleMoves++;
                }
            }

            solveGame(n, m, k, active, board, possibleMoves);
        }
    }

    return 0;
}