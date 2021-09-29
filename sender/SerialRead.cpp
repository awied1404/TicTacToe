#include "SerialRead.h"

SerialRead::SerialRead() {}
bool SerialRead::read()
{
	int iAvailableBytes = Serial.available();
	if (iAvailableBytes)
	{
		char acBuffer[100] = {0};
		char * strings[5];
		int iCharsRead = Serial.readBytesUntil('\n', acBuffer, sizeof(acBuffer) - 1);
		char * strings[5];
    	int iTransmittedFields = fillStringsWithTokenizer(pcChar, "|", strings);	
		if (iTransmittedFields == 0)
		{
			return false;
		}
		if (!parseGameFields(strings[1], aiGameFields))
		{
			return false;
		}

		if (index > 3)
		{
			if(!parseWinner(strings[2], &iPlayerWon, &iStartingField, &iEndingField))
			{
				return false;
			}
		}
	}
	return true;
}

int SerialRead::fillStringsWithTokenizer(char * pcInput, char *pcDelim, char * strings[])
{
	char * ptr = strtok(pcInput, pcDelim);
    int index = 0;
    while (ptr != NULL)
    {
        strings[index] = ptr;
        index ++;
        ptr = strtok(NULL, pcDelim);
    }
    return index;
}

bool SerialRead::parseGameFields(char * pcInput, int * piGameField)
{
	if (pcInput == NULL || piGameField == NULL)
	{
		return false;
	}
	char * strings[3];
    if (fillStringsWithTokenizer(pcInput, " ", strings))
    {
        char * pcGameFields = strings[1];
        for(int i = 0; i < 2*9; i+=2)
        {
            *(piGameField + i/2) = atoi(&pcGameFields[i]);
        }
    }
	return true;
}

bool SerialRead::parseWinner(char * pcInput, int * piPlayerWon, int * piStartingField, int * piEndingField)
{
	if (pcInput == NULL || piPlayerWon == NULL || piStartingField == NULL || piEndingField == NULL)
	{
		return false;
	}
	char * strings[5];
    if (fillStringsWithTokenizer(pcInput, ":,", strings) > 0)
    {
        *piPlayerWon = atoi(strings[1]);
        *piStartingField = atoi(strings[2]);
        *piEndingField = atoi(strings[3]);
        return true;
    }
    else
    {
        return false;
    }
	return true;
}

void SerialRead::getGameFields(char * pcGameFields)
{
	for (int i = 0; i < 9; i++)
	{
		*(pcGameFields+i) = aiGameFields[i] + ASCII_ZERO;
	}
}

bool SerialRead::getWinner(int * piPlayerWon, int * piStartingField, int * piEndingField)
{
	if (iPlayerWon == -1)
	{
		return false;
	}
	else
	{
		*piPlayerWon = iPlayerWon;
		*piStartingField = iStartingField;
		*piEndingField = iEndingField;
		iPlayerWon = -1;
		return true;
	}
}
