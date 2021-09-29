#include "TicTacToe.h"
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

TicTacToe::TicTacToe() {}

void TicTacToe::startGame(t_FieldState startingPlayer)
{
    activePlayer = startingPlayer;
}

TicTacToe::t_TTTState TicTacToe::playersMove(int iRow, int iCol)
{
    t_TTTState returnState = TTT_OKAY;
    /*check if parameters are valid*/
    if (iRow < ROWS && iCol < COLUMNS && activePlayer != UNDEFINED)
    {
        /* check if field was already played */
        if (aiGameFields[iRow][iCol] == UNDEFINED)
        {
            aiGameFields[iRow][iCol] = activePlayer;
            /* change the active player */
            if (activePlayer == PLAYER_ONE)
            {
                activePlayer = PLAYER_TWO;
            }
            else
            {
                activePlayer = PLAYER_ONE;
            }
        }
        returnState = gameFinished();
    }
    else
    {
        returnState = INVALID_MOVE;
    }
    return returnState;
}

TicTacToe::t_TTTState TicTacToe::gameFinished(bool verbose)
{
    t_TTTState returnState = GAME_RUNNING;
    t_FieldState previousState = UNDEFINED;

    if (verbose)
    {
        Serial.println("#################");
        printGame();
    }
    /* check rows for a winner*/
    if (verbose)
    {
        Serial.println("Checking rows");
    }
    for (int i=0; i < ROWS; i++)
    {
        previousState = UNDEFINED;
        for(int j = 0; j < COLUMNS; j++)
        {
            t_FieldState currentState = aiGameFields[i][j];
            if(verbose)
            {
                Serial.print("Row: ");
                Serial.print(i);
                Serial.print(" Col: ");
                Serial.println(j);
            }
            if(j == 0) /* first field in the row*/
            {
                previousState = currentState; 
                if (verbose)
                {
                    Serial.print("j = 0 ");
                    Serial.print("previous state");
                    Serial.println(previousState);
                }
            }
            /* last element in the row*/
            else if (j == 2 && currentState == previousState && currentState != UNDEFINED)
            {
                returnState = tttStateFromFieldState(currentState);
                iStartingField = ROWS * i;
                iEndingField = ROWS * i + j;
                Serial.print("Winner found in row");
                Serial.println(i);
            }
            /* second field in the row*/
            else
            {
                if(previousState != currentState) 
                {
                    if(verbose)
                    {
                        Serial.print("Break when j = 1 ");
                        Serial.print("Prev: ");
                        Serial.print(previousState);
                        Serial.print(" Current: ");
                        Serial.println(currentState);
                    }
                        break;
                }
                else
                {
                    if(verbose)
                    {
                        Serial.println("j = 1 ");
                    }
                }
            }
        }
    }

    if (returnState == GAME_RUNNING)
    {
        if(verbose)
        {
            Serial.println("Checking columns");
        }
        /* check columns for winner */
        for (int i=0; i < ROWS; i++)
        {
            previousState = UNDEFINED;
            for(int j = 0; j < COLUMNS; j++)
            {
                t_FieldState currentState = aiGameFields[j][i];
                if(verbose)
                {
                    Serial.print("Row: ");
                    Serial.print(i);
                    Serial.print(" Col: ");
                    Serial.println(j);
                }
                if(j == 0) /* first field in the column*/
                {
                    previousState = currentState;
                    if (verbose)
                    {
                        Serial.print("j = 0 ");
                        Serial.print("previous state");
                        Serial.println(previousState);
                    }
                }
                /* last element in the column*/
                else if (j == 2 && currentState == previousState && currentState != UNDEFINED)
                {
                    returnState = tttStateFromFieldState(currentState);
                    iStartingField = i;
                    iEndingField = ROWS*j + i;
                    Serial.print("Winner found in col");
                    Serial.println(i);
                }
                /* second field in the column */
                else
                {
                    if(previousState != currentState) 
                    {
                        if(verbose)
                        {
                            Serial.print("Break when j = 1 ");
                            Serial.print("Prev: ");
                            Serial.print(previousState);
                            Serial.print(" Current: ");
                            Serial.println(currentState);
                        }
                        break;
                    }
                    else
                    {
                        if(verbose)
                        {
                            Serial.println("j = 1 ");
                        }
                    }
                    
                }
            }
        }
    }

    if (returnState == GAME_RUNNING)
    {
        if (aiGameFields[1][1] != UNDEFINED)
        {
            /* check diagonals for winners*/
            if ((aiGameFields[0][0] == aiGameFields[1][1]) && (aiGameFields[2][2] == aiGameFields[1][1]))
            {
                returnState = tttStateFromFieldState(aiGameFields[0][0]);
                iStartingField = 0;
                iEndingField = 8;
                Serial.println("Winner found in first diagonal");
        
            }
            else if ((aiGameFields[0][2] == aiGameFields[1][1]) && (aiGameFields[1][1] == aiGameFields[2][0]))
            {
                /* code */
                returnState = tttStateFromFieldState(aiGameFields[0][0]);
                iStartingField = 2;
                iEndingField = 6;
                Serial.println("Winner found in second diagonal");
            }
        }
        
    }

    if (returnState == GAME_RUNNING)
    {
        /* check for draw*/
        int iCountUndefined = 0;
        for (int i = 0; i < ROWS; i ++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                if(aiGameFields[i][j] == UNDEFINED)
                {
                    iCountUndefined++;
                }
                else
                {
                    break;
                }
            }
        }
        if(iCountUndefined == 0)
        {
            returnState = DRAW;
            Serial.println("Draw");
        }
    }
    if (verbose)
    {
        Serial.println("###############");
    }
    return returnState;
}

void TicTacToe::reset()
{
    iStartingField = 0;
    iEndingField = 0;
    for(int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            aiGameFields[i][j] = UNDEFINED;
        }
    }
}

TicTacToe::t_TTTState TicTacToe::tttStateFromFieldState(t_FieldState tState)
{
    t_TTTState returnState;
    if (tState == PLAYER_ONE)
    {
        returnState = PLAYER_ONE_WON;
    }
    else if (tState == PLAYER_TWO)
    {
        /* code */
        returnState = PLAYER_TWO_WON;
    }
    return returnState;
}

void TicTacToe::printGame()
{
    Serial.println("Current status of the game:");
    for (int i = 0; i < ROWS; i++)
    {
        char acChars[3] = {' ', ' ', ' '};
        for (int j = 0; j < ROWS; j++)
        {
            if (aiGameFields[i][j] == PLAYER_ONE)
            {
                acChars[j] = 'x';
            }
            else if (aiGameFields[i][j] == PLAYER_TWO)
            {
                acChars[j] = 'o';
            }
        }
        char buffer[15] = {0};
        snprintf(buffer, 15, "%c | %c | %c", acChars[0], acChars[1], acChars[2]);
        Serial.println(buffer);
        if (i < 2)
        {
            Serial.println("-----------");
        }
    }
}

bool TicTacToe::getGameFields(int * piGameField)
{
    /* param valid check */
    if (piGameField == NULL)
    {
        return false;
    }
    
    for(int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            int iOffset = ROWS * i + j;
            if(aiGameFields[i][j] == UNDEFINED)
            {
                *(piGameField + iOffset) = 0;
            }
            else if(aiGameFields[i][j] == PLAYER_ONE)
            {
                *(piGameField + iOffset) = 1;
            }
            else
            {
                *(piGameField + iOffset) = 2;
            }
        }
        
    }
    return true;
}

bool TicTacToe::getWinningFields(int * piPlayer, int * piStartingField, int * piEndingField)
{
    t_TTTState state = gameFinished();
    if (state == PLAYER_ONE_WON || state == PLAYER_TWO_WON)
    {
        *piStartingField = iStartingField;
        *piEndingField = iEndingField;
        if (state == PLAYER_ONE_WON)
        {
            *piPlayer = 1;
        }
        else
        {
            *piPlayer = 2;
        }
        return true;
    }
    else
    {
        return false;
    }
}