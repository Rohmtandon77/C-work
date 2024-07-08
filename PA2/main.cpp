/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#include <time.h>
#include "boss.h"
#include "Coins.h"
#include "Elements.h"
#include "Game.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Warp.h"
#include "World.h"

int main(int argc, char *argv[])
{
    Game g1;
    g1.game_method(argv[1], argv[2]);
    return 0;
}
