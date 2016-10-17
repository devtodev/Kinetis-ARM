/**
 * Proyecto Pathfinder
 * Autor Carlos Miguens
 *
 */

#include "RGB_Blue.h"
#include "RGB_Red.h"
#include "RGB_Green.h"

#define luces_ON  0
#define luces_OFF 1

void luces_setBlanco()
{
	RGB_Blue_PutVal(luces_ON);
	RGB_Red_PutVal(luces_ON);
	RGB_Green_PutVal(luces_ON);
}

void luces_setApagar()
{
	RGB_Blue_PutVal(luces_OFF);
	RGB_Red_PutVal(luces_OFF);
	RGB_Green_PutVal(luces_OFF);
}
