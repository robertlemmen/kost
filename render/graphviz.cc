#include "graphviz.h"

#include <boost/algorithm/string/replace.hpp>

using namespace std;

// XXX fqn mapping

string gv_escape_name(const string &name) {
    return boost::replace_all_copy(name, "-", "_"); 
}

void gv_dump(ostream& stream, const Entity &entity) {
    if (entity.type() == "SubSystem") {
        stream << "subgraph " << gv_escape_name(entity.name()) << " {" << endl;
        gv_dump(stream, entity.entities());
        stream << "}" << endl;
    }
    else if (entity.type() == "Service") {
        stream << gv_escape_name(entity.name()) << " [ shape=component label=\"" << entity.name() << "\" ]" << endl;
    }
    else {
        throw "type not supported";
    }
}

void gv_dump(ostream& stream, const list<Entity> &entities) {
    for (auto it : entities) {
        gv_dump(stream, it);
    }
}
