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
		char * ptr = strtok(acBuffer, "|");
		byte index = 0;
		while(ptr != NULL)
		{
			strings[index] = ptr;
			index++;
			ptr = strtok(acBuffer, "|");
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

bool SerialRead::parseGameFields(char * pcInput, int * piGameField)
{
	if (pcInput == NULL || piGameField == NULL)
	{
		return false;
	}
	return true;
}

bool SerialRead::parseWinner(char * pcInput, int * piPlayerWon, int * piStartingField, int * piEndingField)
{
	if (pcInput == NULL || piPlayerWon == NULL || piStartingField == NULL || piEndingField == NULL)
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
