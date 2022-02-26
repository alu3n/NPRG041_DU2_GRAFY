//
// Created by Vojtěch Pröschl on 25.02.2022.
//

//Note: Destructor isn't neccessary - all elements are self-destructible

#ifndef DU2_REFACTOREDV2_NODE_H
#define DU2_REFACTOREDV2_NODE_H

#include <cstddef>

//region Node Declaration
template<typename NData>
class Node{
    /**
     * This class is used to represent node in the Graph class. First template argument is datatype of the node data in the graph and second is datatype of the edge data;
     */
    size_t id;
    NData data;
public:
    //Constructors
    Node<NData>() = default;
    Node<NData>(size_t id, NData data);
    //Basic access
    size_t getId() const;
    NData & getData();
    //Print
    template<typename ND>
    friend std::ostream & operator<<(std::ostream &, const Node<ND> &);
};

//endregion

//region Constructor Implementation
template<typename NData>
Node<NData>::Node(size_t id, NData data){
    this->id = id;
    this->data = data;
}
//endregion

//region Access Implementation

template<typename NData>
size_t Node<NData>::getId() const {
    return id;
}

template<typename NData>
NData & Node<NData>::getData() {
    return data;
}
//endregion

//region Print Implementation
template<typename NData>
std::ostream & operator<<(std::ostream & os, const Node<NData> & node){
    os << "node " << "(" << node.getId() << " {" << node.data << "})" <<"\r\n";
    return os;
}
//endregion

#endif //DU2_REFACTOREDV2_NODE_H
