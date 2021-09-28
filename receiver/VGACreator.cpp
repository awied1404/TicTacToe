#include "VGACreator.h"

VGACreator::VGACreator()
{
    init_hardware();
}

VGACreator::t_vga_state VGACreator::init_hardware()
{
    t_vga_state returnState = VGA_OK;
    ESPVGAX::begin();
    return returnState;
}

bool VGACreator::updateGameField(int * piGameField)
{
    // TODO
    return true;
}

bool VGACreator::start()
{
    // TODO
    return true;
}


void VGACreator::playerWon(int iPlayerWon, int iStartingField, int iEndingField)
{
    // TODO
}
