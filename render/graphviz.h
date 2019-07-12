#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include "ast.h"

void gv_dump(std::ostream& stream, const std::list<Entity>& entities);

#endif /* GRAPHVIZ_H */
