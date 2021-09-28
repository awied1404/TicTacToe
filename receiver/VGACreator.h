#include "ESPVGAX.h"

class VGACreator
{
public:
    VGACreator();
    typedef enum E_VGA_STATE {VGA_OK, VGA_HW_ERROR} t_vga_state;
    bool start();
    bool updateGameField(int * piGameField);
    void playerWon(int iPlayerWon, int iStartingField, int iEndingField);

private:
    t_vga_state init_hardware();

};