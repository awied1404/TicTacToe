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

TicTacToe::t_TTTState TicTacToe::gameFinished()
{
    t_TTTState returnState = GAME_RUNNING;
    t_FieldState previousState = UNDEFINED;

    /* check rows for a winner*/
    for (int i=0; i < ROWS; i++)
    {
        previousState = UNDEFINED;
        for(int j = 0; j < COLUMNS; j++)
        {
            t_FieldState currentState = aiGameFields[i][j];
            if(j == 0) /* first field in the column*/
            {
                previousState = currentState; 
            }
            /* last element in the column*/
            else if (j == 2 && currentState == previousState && currentState != UNDEFINED)
            {
                returnState = tttStateFromFieldState(currentState);
                Serial.print("Winner found in row");
                Serial.println(i);
            }
            /* second field in the column */
            else
            {
                if(previousState != currentState) 
                {
                    break;
                }
            }
        }
    }

    if (returnState == GAME_RUNNING)
    {
        /* check columns for winner */
        for (int i=0; i < ROWS; i++)
        {
            previousState = UNDEFINED;
            for(int j = 0; j < COLUMNS; j++)
            {
                t_FieldState currentState = aiGameFields[j][i];
                if(j == 0) /* first field in the column*/
                {
                    previousState = currentState;
                }
                /* last element in the column*/
                else if (j == 2 && currentState == previousState && currentState != UNDEFINED)
                {
                    returnState = tttStateFromFieldState(currentState);
                    Serial.print("Winner found in col");
                    Serial.println(j);
                }
                /* second field in the column */
                else
                {
                    if(previousState != currentState)
                    {
                        break;
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
                Serial.println("Winner found in first diagonal");
        
            }
            else if ((aiGameFields[0][2] == aiGameFields[1][1]) && (aiGameFields[1][1] == aiGameFields[2][0]))
            {
                /* code */
                returnState = tttStateFromFieldState(aiGameFields[0][0]);
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

        if(iCountUndefined == ROWS*COLUMNS)
        {
            returnState = DRAW;
            Serial.println("Draw");
        }
    }
    return returnState;
}

void TicTacToe::reset()
{
    // TODO
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

    for(int i = 0; i < ROWS*COLUMNS; i++)
    {
        *(piGameField+i) = (int) aiGameFields[i];
    }
    return true;
}
