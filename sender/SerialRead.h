#include "ESP8266WiFi.h"
#include "WiFiClient.h"

#define SIZE_DATA 30
#define ASCII_ZERO 48
class SerialRead
{
public:
    SerialRead();
    bool read();
    void getGameFields(char * piGameFields);
    bool getWinner(int * piPlayerWon, int * piStartingField, int * piEndingField);
private:
    bool parseGameFields(char * pcInput, int * piGameField);
    bool parseWinner(char * pcInput, int * piPlayerWon, int * piStartingField, int * piEndingField);
    int fillStringsWithTokenizer(char * pcInput, char *pcDelim, char * strings[]);

    int aiGameFields[9] = {0};
    int iPlayerWon = -1;
    int iStartingField;
    int iEndingField;
};
