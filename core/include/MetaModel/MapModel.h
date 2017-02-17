#pragma once

#include "MetaModel/MetaModel.h"
#include <map>
#include <string>
#include "idmap.h"

class MapModel : public MetaModel {
public:
    MapModel (const string& name);
    virtual ~MapModel ();

    id* find(const string& name);

protected:
    /* data */
    std::map< std::string, id* > data;

};

