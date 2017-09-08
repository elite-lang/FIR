#pragma once

#include "Pass.h"
#include <vector>
#include <list>
#include <string>
#include <set>
using namespace std;

namespace fir {

class ICodeGenContext;

class PassManager {
public:
    PassManager ();
    virtual ~PassManager ();

    void NewPassList(const string& name, const vector<Pass*>& vec);

    void NewPassList(const string& name, const list<Pass*>& lst);

    list<Pass*>* getPassList(const string& name);

    void RunPassList(const string& name, Node* node, ICodeGenContext* ctx);

    void RunPassListWithSet(const string& name, set<Node*>& nodes, ICodeGenContext* ctx);

    void LoadDefaultLists();

protected:
    /* data */

    /**
     * 所有PassList的存储位置
     */
    map<string, list<Pass*> > pass_lists;
};


}