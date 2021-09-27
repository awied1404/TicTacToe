#include "config.h"

class Hardware
{
public:
    typedef enum E_HW_STATE {HW_OK, HW_INIT_ERROR} t_HW_State;
    t_HW_State initSensors();
    t_HW_State getNextField(int * piRow, int * piCol);

private:
    t_HW_State checkSensors();
};