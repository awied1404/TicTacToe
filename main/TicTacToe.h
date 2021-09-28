#include "config.h"
#include "stdio.h"
class TicTacToe
{
public:
    TicTacToe();
    typedef enum E_TIC_TAC_TOE_STATE {TTT_OKAY, INVALID_MOVE, PLAYER_ONE_WON, PLAYER_TWO_WON, DRAW, GAME_RUNNING, GAME_INITIALIZED} t_TTTState;
    typedef enum E_FIELD_STATE {UNDEFINED, PLAYER_ONE, PLAYER_TWO} t_FieldState;
    void reset();
    t_TTTState playersMove(int iRow, int iCol);
    void startGame(t_FieldState startingPlayer);
    void printGame();
    bool getGameFields(int * piFields);

private:
    t_FieldState aiGameFields[ROWS][COLUMNS] = {UNDEFINED};
    t_FieldState activePlayer = UNDEFINED;

    t_TTTState gameFinished();
    t_TTTState tttStateFromFieldState(t_FieldState tState);

};