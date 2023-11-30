#ifndef LETADLO_H_INCLUDED
#define LETADLO_H_INCLUDED

#include "Path.h"
#include "TerrainMap.h"

class Letadlo : public Path {
public:
    Letadlo(TerrainMap& m, std::string name_in, Point start_in, Point finish_in);
    virtual bool find();
};

#endif // LETADLO_H_INCLUDED
