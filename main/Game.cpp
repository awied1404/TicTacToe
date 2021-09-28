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
    while(true)
    {
        if(hw.getNextField(&iRow, &iCol) != Hardware::HW_OK)
        {
            break;
        }
        char buffer[30] = {0};
        snprintf(buffer, 30, "Row: %i , Col: %i", iRow, iCol);
        Serial.println(buffer);
        if(game.playersMove(iRow, iCol) != TicTacToe::GAME_RUNNING)
        {
            break;
        }
        delay(1000);
        game.printGame();

    }

    return returnState;
}