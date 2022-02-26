//
// Created by Vojtěch Pröschl on 25.02.2022.
//

#ifndef DU2_REFACTOREDV2_EDGES_H
#define DU2_REFACTOREDV2_EDGES_H

#include <iostream>
#include <vector>
#include "Edge.h"
#include "Array.h"
#include "Exceptions.h"

enum class graph_type{
    oriented,
    unoriented
};

template<typename NData, typename EData>
class Nodes;

template<typename NData, typename EData>
class Edges{
    /**
     * This class is used to represent the edge component in the graph class. First template argument is the datatype of the node data and second is the datatype of the edge data.
     * Edges and nodes have to be declared in tandem and linked together using the set_point method in order for them to work due to the operations cross dependency.
     */
    Nodes<NData,EData> * nodes;
    Array<Edge<NData,EData>> data;
    std::vector<std::vector<Edge<NData,EData>*>> adjacency_matrix{};
    //Double bracket access
    struct double_bracket_trick{
        /**
         * This struct is used to enable programmer to acces edge using chained brackets (i.e. edges[i][j]).
         */
        Edges<NData,EData> * parent;
        size_t source;
        double_bracket_trick(Edges<NData,EData> * edges, size_t source);
        double_bracket_trick() = default;
        Edge<NData,EData> & operator[](size_t target);
    };
    double_bracket_trick temp;
    friend Edge<NData, EData> &double_bracket_trick::operator[](size_t index);
public:
    void repair_adjacency_matrix();
    graph_type graph_t;
    //Constructor
    Edges(graph_type graph_t);
    //Adding edges
    Edge<NData,EData> & add(size_t id, size_t source, size_t target, EData data);
    Edge<NData,EData> & add(size_t source, size_t target, EData data);
    //Access to edges
    size_t size() const;
    bool exists(size_t id) const;
    bool exists(size_t source, size_t target) const;
    Edge<NData, EData>& get(size_t id) const;
    Edge<NData, EData>& get(size_t source, size_t target) const;
    double_bracket_trick & operator[](size_t source);
    //Iterators
    typename Array<Edge<NData,EData>>::iterator begin() const;
    typename Array<Edge<NData,EData>>::iterator end() const;
    //Utility
    void print(std::ostream & os = std::cout) const;
    void printMatrix(std::ostream & os = std::cout);
    void set_pointer(Nodes<NData,EData> * nodes);
    void increase_adjacency_size();
    //Copy/move constructors/assignments
    Edges(const Edges<NData,EData> & other); //copy constructor
    Edges(Edges<NData,EData> && other); //move constructor
    Edges & operator=(const Edges<NData,EData> & other); //copy assignment
    Edges & operator=(Edges<NData,EData> && other) noexcept; //move assignment
};




template<typename NData, typename EData>
std::ostream & operator<<(std::ostream & os, const Edges<NData,EData> edges){
    edges.print(os);
    return os;
}
//region Double Bracket Trick Implementation
template<typename NData, typename EData>
Edges<NData, EData>::double_bracket_trick::double_bracket_trick(Edges<NData, EData> *edges, size_t source) {
    this->parent = edges;
    this->source = source;
}

template<typename NData, typename EData>
Edge<NData, EData> &Edges<NData, EData>::double_bracket_trick::operator[](size_t target) {
    if(target >= parent->nodes->size()){
        throw NonexistingItemException::non_existent_target(target,this->parent->nodes->size());
    }
    else{
        return this->parent->get(source,target);
    }
}

//endregion

//region Constructor
template<typename NData, typename EData>
Edges<NData, EData>::Edges(graph_type graph_t) {
    this->graph_t = graph_t;
}

//endregion

//region Adding edges implementation
template<typename NData, typename EData>
Edge<NData, EData> &Edges<NData, EData>::add(size_t id, size_t source, size_t target, EData data) {
    if(this->size()<id){
        throw InvalidIdentifierException::wrong_id_edge(id,this->size());
    }
    else if(this->size()>id){
        throw ConflictingItemException::already_taken_id_edge(id);
    }
    else if(nodes->size()<=source || nodes->size()<=target){
        throw NonexistingItemException::non_existent_pair_adding_edge(source,target,this->nodes->size());
    }
    else if(adjacency_matrix[source][target] != NULL){
        throw ConflictingItemException::already_taken_pair(source,target);
    }
    try {
        Edge<NData, EData> temp(id, data, &(nodes->get(target)), &(nodes->get(source)));
        this->data.push_back(temp);
        this->adjacency_matrix[source][target] = &this->data[id];
        if (graph_t == graph_type::unoriented) {
            this->adjacency_matrix[target][source] = &this->data[id];
        }
//        this->nodes->
        return this->data[id];
    }
    catch(...){
        throw UnavailableMemoryException::cant_insert_edge_to_container();
    }
}

template<typename NData, typename EData>
Edge<NData, EData> &Edges<NData, EData>::add(size_t source, size_t target, EData data) {
    return this->add(this->size(),source,target,data);
}
//endregion

//region Access to edges implementation
template<typename NData, typename EData>
bool Edges<NData, EData>::exists(size_t id) const {
    if(this->size() > id){
        return true;
    }
    return false;
}

template<typename NData, typename EData>
bool Edges<NData, EData>::exists(size_t source, size_t target) const {
    if(nodes->size() <= source || nodes->size() <= target) {
        throw NonexistingItemException::non_existent_pair_nodes_test(source,target,nodes->size());
    }
    if(adjacency_matrix[source][target]==NULL){
        return false;
    }
    else{
        return true;
    }
}

template<typename NData, typename EData>
Edge<NData, EData> &Edges<NData, EData>::get(size_t id) const {
    if(this->size() <= id){
        throw NonexistingItemException::non_existent_edge(id,this->size());
    }
    else{
        return data[id];
    }
}

template<typename NData, typename EData>
Edge<NData, EData> & Edges<NData, EData>::get(size_t source, size_t target) const {
    if(nodes->size() <= source || nodes->size() <= target){
        throw NonexistingItemException::non_existnet_pair_nodes(source,target,nodes->size());
    }
    else if(this->adjacency_matrix[source][target] == NULL){
        throw NonexistingItemException::non_existent_pair_edge(source,target);
    }
    else{
        return *adjacency_matrix[source][target];
    }
}

template<typename NData, typename EData>
typename Edges<NData,EData>::double_bracket_trick & Edges<NData, EData>::operator[](size_t source) {
    if(source >= nodes->size()){
        throw NonexistingItemException::non_existent_source(source,nodes->size());
    }
    else{
        temp = double_bracket_trick(this,source);
        return temp;
    }
}

//endregion

//region Iterators implementation
template<typename NData, typename EData>
typename Array<Edge<NData, EData>>::iterator Edges<NData, EData>::begin() const {
    return data.begin();
}

template<typename NData, typename EData>
typename Array<Edge<NData, EData>>::iterator Edges<NData, EData>::end() const {
    return data.end();
}
//endregion

//region Utility implementation
template<typename NData, typename EData>
void Edges<NData, EData>::set_pointer(Nodes<NData, EData> *nodes) {
    this->nodes = nodes;
}

template<typename NData, typename EData>
void Edges<NData, EData>::increase_adjacency_size() {
    size_t size = adjacency_matrix.size() +1;
    std::vector<Edge<NData,EData>*> tmp;
    for(size_t i = 0; i < size; i++){
        tmp.push_back(NULL);
    }
    for(auto && x : adjacency_matrix){
        x.push_back(NULL);
    }
    this->adjacency_matrix.push_back(tmp);
}

template<typename NData, typename EData>
size_t Edges<NData, EData>::size() const {
    return this->data.size();
}

template<typename NData, typename EData>
void Edges<NData, EData>::print(std::ostream &os) const {
    for(auto && x : this->data){
        os << x;
    }
}

template<typename NData, typename EData>
void Edges<NData, EData>::printMatrix(std::ostream &os) {
    for(auto && x : adjacency_matrix){
        bool first = true;
        for(auto && y : x){
            if(!first){
                os<< "|";
            }
            if(y == NULL){
                os << "-";
            }
            else{
                os << y->getId();
            }
            first=false;
        }
        os << "\r\n";
    }
}

template<typename NData, typename EData>
void Edges<NData, EData>::repair_adjacency_matrix() {
    //Todo: finish implementation
    size_t size = this->adjacency_matrix.size();
    adjacency_matrix.clear();
    std::vector<Edge<NData,EData>*> tmp;
    for(size_t i = 0; i < size; i++){
        tmp.push_back(NULL);
    }
    for(size_t i = 0; i < size; i++){
        adjacency_matrix.push_back(tmp);
    }
    for(auto && x : this->data){
        adjacency_matrix[x.getSource().getId()][x.getTarget().getId()] = &x;
        if(graph_t == graph_type::unoriented){
            adjacency_matrix[x.getTarget().getId()][x.getSource().getId()] = &x;
        }
    }
}

//endregion

//region Rule of Five implementation
template<typename NData, typename EData>
Edges<NData, EData>::Edges(const Edges<NData, EData> &other) {
    this->graph_t = other.graph_t;
    this->nodes = other.nodes;
    this->data = other.data;
    this->adjacency_matrix = other.adjacency_matrix;
    this->repair_adjacency_matrix();
}

template<typename NData, typename EData>
Edges<NData, EData>::Edges(Edges<NData, EData> &&other) {
    this->graph_t = other.graph_t;
    this->nodes = other.nodes;
    this->data = std::move(other.data);
    this->adjacency_matrix = other.adjacency_matrix;
    other.adjacency_matrix.clear();
    other.data = Array<Edge<NData,EData>>();
}

template<typename NData, typename EData>
Edges<NData,EData> &Edges<NData, EData>::operator=(const Edges<NData, EData> &other) {
    this->graph_t = other.graph_t;
    this->nodes = other.nodes;
    this->data = other.data;
    this->adjacency_matrix = other.adjacency_matrix;
    this->repair_adjacency_matrix();
    return *this;
}

template<typename NData, typename EData>
Edges<NData,EData> &Edges<NData, EData>::operator=(Edges<NData, EData> &&other) noexcept {
    this->graph_t = other.graph_t;
    this->nodes = other.nodes;
    this->data = std::move(other.data);
    this->adjacency_matrix = other.adjacency_matrix;
    other.adjacency_matrix.clear();
    other.data = Array<Edge<NData,EData>>();
    return *this;
}

//endregion

#endif //DU2_REFACTOREDV2_EDGES_H
