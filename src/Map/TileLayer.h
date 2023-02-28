#ifndef TILELAYER_H
#define TILELAYER_H
#include "Layer.h"
#include <string>
#include <vector>

struct Tileset{
    int FirstID, LastID;
    int RowCount,ColCount;
    int TileCount,TileSize;
    std::string Name, Source;


};

using Tilesetlist = std::vector<Tileset>;
using Tilemap=std::vector<std::vector<int> >;


class TileLayer : public Layer
{
    public:
        TileLayer(int tilesize, int rowcount, int colcount, Tilemap tilemap, Tilesetlist tilesets);
        virtual void Render();
        virtual void Update();
        inline Tilemap GetTilemap(){return m_Tilemap;}

    private:
        int m_TileSize;
        int m_RowCount,m_ColCount;
        Tilemap m_Tilemap;
        Tilesetlist m_Tilesets;

};

#endif // TILELAYER_H
