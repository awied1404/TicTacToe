#include "Hardware.h"
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

Hardware::t_HW_State Hardware::initSensors()
{
    // TODO
    return HW_OK;
}

Hardware::t_HW_State Hardware::getNextField(int * piRow, int * piCol)
{
    *piRow = random(3);
    *piCol = random(3);
    return HW_OK;
}

Hardware::t_HW_State Hardware::checkSensors()
{
    // TODO
    return HW_OK;
}