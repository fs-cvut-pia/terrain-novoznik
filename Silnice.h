#ifndef SILNICE_H_INCLUDED
#define SILNICE_H_INCLUDED

#include "Path.h"
#include "TerrainMap.h"

class Silnice : public Path {
public:
    Silnice(TerrainMap& m, std::string name_in, Point start_in, Point finish_in);
    virtual bool find();
};

#endif // SILNICE_H_INCLUDED
