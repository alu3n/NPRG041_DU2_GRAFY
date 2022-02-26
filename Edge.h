//
// Created by Vojtěch Pröschl on 25.02.2022.
//

//Note: Destructor isn't neccessary - C-Style pointers serve as observers

#ifndef DU2_REFACTOREDV2_EDGE_H
#define DU2_REFACTOREDV2_EDGE_H

#include "Node.h"
#include "Array.h"

template<typename NData, typename EData>
class Edge{
    /**
     * This class is used to represent edge in the Graph class. First template argument is datatype of the node data in the graph and second is datatype of the edge data;
     */
    size_t id;
    Node<NData> * target;
    Node<NData> * source;
    EData data;
public:
    //Constructors
    Edge<NData,EData>(size_t id,EData data, Node<NData> * target, Node<NData> * source);
    Edge<NData,EData>() = default;
    //Basic access
    size_t getId() const;
    EData & getData();
    Node<NData> & getSource() const;
    Node<NData> & getTarget() const;
    //Printing
    template<typename ND,typename ED>
    friend std::ostream & operator<<(std::ostream & os, const Edge<ND,ED> & edge);
};

//region Constructor Implementation
template<typename NData, typename EData>
Edge<NData, EData>::Edge(size_t id, EData data, Node<NData> *target, Node<NData> *source) {
    this->id = id;
    this->data = data;
    this->target = target;
    this->source = source;
}
//endregion

//region Basic Access
template<typename NData, typename EData>
size_t Edge<NData,EData>::getId() const {
    return id;
}

template<typename NData, typename EData>
EData & Edge<NData,EData>::getData() {
    return data;
}

template<typename NData,typename EData>
Node<NData> & Edge<NData,EData>::getSource() const {
    return *source;
}

template<typename NData,typename EData>
Node<NData> & Edge<NData,EData>::getTarget() const {
    return *target;
}
//endregion

//region Printing
template<typename NData,typename EData>
std::ostream & operator<<(std::ostream & os, const Edge<NData,EData> & edge){
    os << "edge (" << edge.getSource().getId() <<
       ")-[" << edge.getId() << " {" << edge.data <<
       "}]->" << "(" << edge.getTarget().getId()<<")" << "\r\n";
    return os;
}
//endregion

#endif //DU2_REFACTOREDV2_EDGE_H
