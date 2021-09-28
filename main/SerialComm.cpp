#include "SerialComm.h"
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

SerialComm::SerialComm()
{
    Serial.begin(115200);
}


/**
 * iPlayer: which player has won: allowed values 1,2
 * The game is defined with 0 as upper left field and 8 as lower right field
 * 0|1|2
 * 3|4|5
 * 6|7|8
 * iStartField: field with the starting point of "three in a row"
 * iEndField: field with the last point of "three in a row"
*/
void SerialComm::addWinner(int iPlayer, int iStartField, int iEndField)
{
    bool bParamsValid = false;
    /* parameter check */
    if (iPlayer < 3 && iPlayer > 0)
    {
        if (iStartField < 9 && iStartField >= 0 && iEndField < 9 && iEndField >= 0)
        {
            bParamsValid = true;
        }
    }

    if(bParamsValid)
    {
        iPlayerWon = iPlayer;
        iStartingField = iStartField;
        iEndingField = iEndField;
    }
}

void SerialComm::resetValues()
{
    iPlayerWon = -1;
    iStartingField = -1;
    iEndingField = -1;
}

void SerialComm::send(int aiGameField[ROWS*COLUMNS])
{
    Serial.print("START |");
    char buffer [ROWS*COLUMNS + 1] = {0};
    for (int i = 0; i < ROWS*COLUMNS; i++)
    {
        buffer[i] = aiGameField[i] + ASCII_ZERO;
    }
    Serial.print("FIELD: ");
    Serial.print(buffer);
    Serial.print(" | ")

    if (iPlayerWon != -1)
    {
        char buffer[20] = {0};
        snprintf(buffer, 20, "Player won: %i, %i, %i", iPlayerWon, iStartingField, iEndingField);
        Serial.print(buffer);
        Serial.print(" | ");
    }
    Serial.println("END");
    resetValues();
}