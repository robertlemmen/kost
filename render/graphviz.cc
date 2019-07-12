#include "graphviz.h"

using namespace std;

// XXX escape names, fqn mapping

void gv_dump(ostream& stream, const Entity &entity) {
    if (entity.type() == "SubSystem") {
        stream << "subgraph " << entity.name() << " {" << endl;
        gv_dump(stream, entity.entities());
        stream << "}" << endl;
    }
    else if (entity.type() == "Service") {
        stream << entity.name() << " [ shape=component label=\"" << entity.name() << "\" ]" << endl;
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
