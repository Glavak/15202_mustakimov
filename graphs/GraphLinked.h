//
// Created by glavak on 29.12.16.
//

#ifndef MYARRAY_GRAPHLINKED_H
#define MYARRAY_GRAPHLINKED_H

#include <vector>

template<typename ContentType>
class Vertex
{
public:
    std::vector<Vertex<ContentType> *> neigbours;
    ContentType content;
};

#endif //MYARRAY_GRAPHLINKED_H
