#include "ESP8266WebServer.h"

class Parser 
{
public:
    Parser();
    bool parse(ESP8266WebServer *);

    bool getCurrentField(int * piGameField);
    bool getPlayerWon(int * piPlayerWon, int * piStartingField, int * piEndingField);
private:
    int iPlayerWon;
    int iStartingField; /* only necessary if a player has won the game*/
    int iEndingField; /* only necessary if a player has won the game*/

    int aiGameField[9] = {0};
};