#include "Game.h"
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
Game::Game()
{

}

Game::t_GAME_STATE Game::startGame()
{
    t_GAME_STATE returnState = GAME_INITIALIZED;

    if (hw.initSensors() != Hardware::HW_OK)
    {
        return INIT_ERROR;
    }

    game.startGame((TicTacToe::t_FieldState) random(2));
    int iRow, iCol;
    bool bRunning = true;
    int iMovesMade = 0;
    while(bRunning)
    {
        if(hw.getNextField(&iRow, &iCol) != Hardware::HW_OK)
        {
            break;
        }
        if(game.playersMove(iRow, iCol) != TicTacToe::GAME_RUNNING)
        {
            bRunning = false;
        }
        delay(1000);
        //char buffer[30] = {0};
        //snprintf(buffer, 30, "Row: %i , Col: %i", iRow, iCol);
        //Serial.println(buffer);
        //iMovesMade++;
        int aiGameField[9] ={0};
        //if (iMovesMade > 10)
        //{
            //game.gameFinished(true);
        //}
        if (game.getGameFields(aiGameField))
        {
            int iStartingField, iEndingField, iPlayer;
            if (game.getWinningFields(&iPlayer, &iStartingField, &iEndingField))
            {
                comm.addWinner(iPlayer, iStartingField, iEndingField);
            }
            comm.send(aiGameField);
        }


    }

    return returnState;
}