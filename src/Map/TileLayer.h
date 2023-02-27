#ifndef TILELAYER_H
#define TILELAYER_H
#include "Layer.h"
#include <string>
#include <vector>

struct Tileset{
    int First, LastID;
    int NumRows,NumCols;
    int TileCount,TileSize;


};

class TileLayer
{
    public:
        TileLayer();

    private:
};

#endif // TILELAYER_H
