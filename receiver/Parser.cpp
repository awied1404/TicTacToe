#include "Parser.h"

Parser::Parser()
{

}

bool Parser::parse(ESP8266WebServer * server)
{
    if (server->hasArg("player_won")) { // this is the variable sent from the client
        iPlayerWon = server->arg("player_won").toInt();
        if(server->hasArg("start_field"))
        {
            iStartingField = server->arg("start_field").toInt();
        }
        if(server->hasArg("end_field"))
        {
            iStartingField = server->arg("end_field").toInt();
        }
    }
    if(server->hasArg("game_field"))
    {
        String GameField = server->arg("game_field");
        for(int i = 0; i < 9; i++)
        {
            aiGameField[i] = atoi((char *) GameField[i]);
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool Parser::getCurrentField(int * piGameField)
{
    if (piGameField == NULL)
    {
        return false;
    }
    
    piGameField = aiGameField;
    return true;
}

bool Parser::getPlayerWon(int * piPlayerWon, int * piStartingField, int * piEndingField)
{
    if (iPlayerWon == -1 || piEndingField == NULL || piPlayerWon == NULL || piStartingField == NULL)
    {
        return false;
    }

    *piPlayerWon = iPlayerWon;
    *piStartingField = iStartingField;
    *piEndingField = iEndingField;
    return true;
}
