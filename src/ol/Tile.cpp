//
//
//

#include "Tile.h"

#include <iostream>

ol::Tile::~Tile()
{
#ifndef NDEBUG
    std::cout << "ol::Tile::~Tile(), uid=" << ol_uid << std::endl;
#endif
}
