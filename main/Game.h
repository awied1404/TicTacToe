#include "config.h"
#include "TicTacToe.h"
#include "Hardware.h"
#include "SerialComm.h"
class Game
{
public:
    typedef enum E_GAME_STATE {GAME_INITIALIZED, INIT_ERROR, SENSOR_ERROR, 
    PLAYER_ONE_WON, PLAYER_TWO_WON, GAME_RUNNING} t_GAME_STATE;
    Game();
    t_GAME_STATE startGame();

private:
    t_GAME_STATE playersMove(int iRow, int iCol);
    t_GAME_STATE gameFinished();
    t_GAME_STATE run();

    TicTacToe game;
    Hardware hw;
    SerialComm comm;
};