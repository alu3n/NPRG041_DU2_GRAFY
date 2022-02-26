//
// Created by Vojtěch Pröschl on 25.02.2022.
//

//Note: Destructor isn't neccessary - all elements are self-destructible. C-Style pointer serves as observer.

#ifndef DU2_REFACTOREDV2_NODES_H
#define DU2_REFACTOREDV2_NODES_H

#include <vector>
#include <iostream>
#include "Node.h"
#include "Edge.h"
#include "Array.h"
#include "Exceptions.h"

//region Nodes definition
template<typename NData, typename EData>
class Edges;

template<typename NData, typename EData>
class Nodes{
    /**
    * This class is used to represent the node component in the graph class. First template argument is the datatype of the node data and second is the datatype of the edge data.
    * Edges and nodes have to be declared in tandem and linked together using the set_point method in order for them to work due to the operations cross dependency.
    */
    Array<Node<NData>> data;
    Edges<NData,EData> * edges;
    std::vector<std::vector<Edge<NData,EData>>> * adjacency_matrix;
public:
    //Adding nodes
    Node<NData> & add(size_t id, NData data);
    Node<NData> & add(NData data);
    //Access to nodes
    size_t size() const;
    bool exists(size_t id);
    Node<NData> & get(size_t id) const;
    Node<NData> & operator[](size_t id) const;
    //Iterators
    typename Array<Node<NData>>::iterator begin() const;
    typename Array<Node<NData>>::iterator end() const;
    //Utility
    void print(std::ostream & os = std::cout) const;
    void set_pointer(Edges<NData,EData> * edges);
};
//endregion

//region Adding nodes implementation

template<typename NData, typename EData>
Node<NData> & Nodes<NData,EData>::add(NData data) {
    return add(size(),data);
}

template<typename NData, typename EData>
Node<NData> & Nodes<NData,EData>::add(size_t id, NData data){
    if(id > size()){
        throw InvalidIdentifierException::wrong_id(id,size());
    }
    else if(id < size()){
        throw ConflictingItemException::already_taken_id(id);
    }

    Node<NData> temp(id,data);
    try{
        this->data.push_back(temp);
    }
    catch(...){
        throw UnavailableMemoryException::cant_insert_to_container();
    }
    try{
        edges->increase_adjacency_size();
    }
    catch(...){
        this->data.pop_back();
        throw UnavailableMemoryException::cant_extent_adjacency();
    }
    return this->data.at(size()-1);
}

//endregion

//region Access to nodes implementation
template<typename NData, typename EData>
size_t Nodes<NData,EData>::size() const {
    return data.size();
}

template<typename NData, typename EData>
bool Nodes<NData,EData>::exists(size_t id) {
    if(this->size()>id) {
        return true;
    }
    else{
        return false;
    }
}

template<typename NData, typename EData>
Node<NData> & Nodes<NData,EData>::get(size_t id) const {
    if(id>=this->size()){
        throw NonexistingItemException::non_existent_node(id,this->size());
    }
    else{
        return data.at(id);
    }
}

template<typename NData, typename EData>
Node<NData> & Nodes<NData,EData>::operator[](size_t id) const {
    return this->get(id);
}

//endregion

//region Iterators implementation
template<typename NData, typename EData>
typename  Array<Node<NData>>::iterator Nodes<NData,EData>::begin() const{
    return this->data.begin();
}

template<typename NData, typename EData>
typename  Array<Node<NData>>::iterator Nodes<NData,EData>::end() const{
    return this->data.end();
}
//endregion

//region Utility Implementation
template<typename NData, typename EData>
void Nodes<NData,EData>::print(std::ostream & os) const{
    for(auto && x : this->data){
        os << x;
    }
}

template<typename NData, typename EData>
std::ostream & operator<<(std::ostream & os, const Nodes<NData,EData> nodes){
    nodes.print(os);
    return os;
}

template<typename NData, typename EData>
void Nodes<NData, EData>::set_pointer(Edges<NData, EData> *edges) {
    this->edges = edges;
}

//endregion

#endif //DU2_REFACTOREDV2_NODES_H
