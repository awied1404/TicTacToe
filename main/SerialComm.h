#include "config.h"
class SerialComm
{
public:
    SerialComm();
    void send(int aiGameField[ROWS*COLUMNS]);
    void addWinner(int iPlayer, int iStartField, int iEndField);
private:
    int iPlayerWon;
    int iStartingField; /* only necessary if a player has won the game*/
    int iEndingField; /* only necessary if a player has won the game*/

    int aiGameField[ROWS*COLUMNS] = {0};

    void resetValues();
};