//
// Created by Vojtěch Pröschl on 25.02.2022.
//

//Note: Destructor isn't neccessary - all elements are self-destructible

#ifndef DU2_REFACTOREDV2_GRAPH_H
#define DU2_REFACTOREDV2_GRAPH_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Nodes.h"
#include "Edges.h"
#include "Utility.h"

//region Graph Declaration

template<typename NData, typename EData>
class Graph{
    /**
     * This class is an common abstract to DirectedGraph and UndirectedGraph classes.
     * First template argument is the datatype of the node data and second is the datatype of the edge data.
     */
public:
    //Constructors
    Graph();
    Graph(graph_type type);
    //Access
    virtual Nodes<NData,EData> & nodes() = 0;
    virtual Edges<NData,EData> & edges() = 0;
    //IO
    void import(std::istream & is = std::cin);
    void import(const std::string & filename);
    void print(std::ostream & os = std::cout) const;
    void print(const std::string & filename) const;
protected:
    Nodes<NData,EData> nodes_data;
    Edges<NData,EData> edges_data;
};

//endregion

//region Graph Implementation
template<typename NData,typename EData>
std::ostream & operator<<(std::ostream & os,const Graph<NData,EData> & graph){
    graph.print(os);
    return os;
}

template<typename NData, typename EData>
Graph<NData, EData>::Graph(graph_type type) : edges_data(type) {
    this->nodes_data = Nodes<NData,EData>();
    this->nodes_data.set_pointer(&edges_data);
    this->edges_data.set_pointer(&nodes_data);
}
template<typename NData, typename EData>
Graph<NData, EData>::Graph() : edges_data(graph_type::unoriented) {
    this->nodes_data = Nodes<NData,EData>();
    this->nodes_data.set_pointer(&edges_data);
    this->edges_data.set_pointer(&nodes_data);
}
template<typename NData, typename EData>
void Graph<NData, EData>::import(std::istream &is) {
    std::string line;
    while(std::getline(is,line)){
        if(line.substr(0,4)=="node"){
            size_t node_id;
            NData node_data;
            string_to_node_components<NData>(line,node_id,node_data);
            this->nodes_data.add(node_id,node_data);
        }
        else if(line.substr(0,4) == "edge"){
            size_t edge_id,source_id,target_id;
            EData edge_data;
            string_to_edge_components<EData>(line,edge_id,source_id,target_id,edge_data);
            this->edges_data.add(edge_id,source_id,target_id,edge_data);
        }
    }
}

template<typename NData, typename EData>
void Graph<NData, EData>::import(const std::string &filename) {
    std::fstream file;
    try {
        file.open(filename, std::fstream::in);
    }
    catch(...){
        throw FileProcessingException::cant_open_input(filename);
    }
    if(!file.is_open()) {
        throw FileProcessingException::cant_open_input(filename);
    }
    else{
        import(file);
        file.close();
    }
}

template<typename NData, typename EData>
void Graph<NData, EData>::print(std::ostream &os) const {
    os << this->nodes_data;
    os << this->edges_data;
}

template<typename NData, typename EData>
void Graph<NData, EData>::print(const std::string &filename) const {
    std::fstream file;
    try {
        file.open(filename, std::fstream::out);
    }
    catch(...){
        throw FileProcessingException::cant_open_input(filename);
    }
    if(!file.is_open()) {
        throw FileProcessingException::cant_open_output(filename) ;
    }
    else{
        this->print(file);
        file.close();
    }
}
//endregion

//region DirectedGraph Declaration
template<typename NData, typename EData>
class DirectedGraph : public Graph<NData,EData>{
public:
    /**
    * This class is an class used to represent directed graph.
    * First template argument is the datatype of the node data and second is the datatype of the edge data.
    */
    //Constructor
    DirectedGraph();
    //Access
    virtual Nodes<NData,EData> & nodes();
    virtual Edges<NData,EData> & edges();
    //Move/copy constructor/assignment
    DirectedGraph(const DirectedGraph<NData,EData> & other);//copy constructor
    DirectedGraph(DirectedGraph<NData,EData> && other);//move constructor
    DirectedGraph<NData,EData> & operator=(const DirectedGraph<NData,EData> & other);//copy assignment
    DirectedGraph<NData,EData> & operator=(DirectedGraph<NData,EData>&& other) noexcept;//move assignment
};
//endregion

//region DirectedGraph Implementation
template<typename NData, typename EData>
DirectedGraph<NData,EData>::DirectedGraph() : Graph<NData,EData>(graph_type::oriented){

}

template<typename NData, typename EData>
Nodes<NData, EData> &DirectedGraph<NData, EData>::nodes() {
    return this->nodes_data;
}

template<typename NData, typename EData>
Edges<NData, EData> &DirectedGraph<NData, EData>::edges() {
    return this->edges_data;
}

template<typename NData, typename EData>
DirectedGraph<NData, EData>::DirectedGraph(const DirectedGraph<NData, EData> &other) {
    this->edges_data = other.edges_data;
    this->nodes_data = other.nodes_data;
    this->edges_data.set_pointer(&(this->nodes_data));
    this->nodes_data.set_pointer(&(this->edges_data));
}

template<typename NData, typename EData>
DirectedGraph<NData, EData>::DirectedGraph(DirectedGraph<NData, EData> &&other) {
    this->edges_data = std::move(other.edges_data);
    this->nodes_data = std::move(other.nodes_data);
    this->edges_data.set_pointer(&(this->nodes_data));
    this->nodes_data.set_pointer(&(this->edges_data));
}

template<typename NData, typename EData>
DirectedGraph<NData, EData> &DirectedGraph<NData, EData>::operator=(const DirectedGraph<NData, EData> &other) {
    this->edges_data = other.edges_data;
    this->nodes_data = other.nodes_data;
    this->edges_data.set_pointer(&(this->nodes_data));
    this->nodes_data.set_pointer(&(this->edges_data));
    return *this;
}

template<typename NData, typename EData>
DirectedGraph<NData, EData> &DirectedGraph<NData, EData>::operator=(DirectedGraph<NData, EData> &&other) noexcept {
    this->edges_data = std::move(other.edges_data);
    this->nodes_data = std::move(other.nodes_data);
    this->edges_data.set_pointer(&(this->nodes_data));
    this->nodes_data.set_pointer(&(this->edges_data));
    return *this;
}

//endregion

//region UndirectedGraph Declaration
template<typename NData, typename EData>
class UndirectedGraph : public Graph<NData,EData>{
public:
    /**
    * This class is an class used to represent undirected graph.
    * First template argument is the datatype of the node data and second is the datatype of the edge data.
    */
    UndirectedGraph();
    virtual Nodes<NData,EData> & nodes();
    virtual Edges<NData,EData> & edges();
    UndirectedGraph(const UndirectedGraph<NData,EData> & other);//copy constructor
    UndirectedGraph(UndirectedGraph<NData,EData> && other);//move constructor
    UndirectedGraph<NData,EData> & operator=(const UndirectedGraph<NData,EData> & other);//copy assignment
    UndirectedGraph<NData,EData> & operator=(UndirectedGraph<NData,EData>&& other) noexcept;//move assignment
};
//endregion

//region UndirectedGraph Implementation
template<typename NData, typename EData>
UndirectedGraph<NData,EData>::UndirectedGraph() : Graph<NData,EData>(graph_type::unoriented){

}

template<typename NData, typename EData>
Nodes<NData, EData> &UndirectedGraph<NData, EData>::nodes() {
    return this->nodes_data;
}

template<typename NData, typename EData>
Edges<NData, EData> &UndirectedGraph<NData, EData>::edges() {
    return this->edges_data;
}

template<typename NData, typename EData>
UndirectedGraph<NData, EData>::UndirectedGraph(const UndirectedGraph<NData, EData> &other) {
    this->edges_data = other.edges_data;
    this->nodes_data = other.nodes_data;
    this->edges_data.set_pointer(&(this->nodes_data));
    this->nodes_data.set_pointer(&(this->edges_data));
}

template<typename NData, typename EData>
UndirectedGraph<NData, EData>::UndirectedGraph(UndirectedGraph<NData, EData> &&other) {
    this->edges_data = std::move(other.edges_data);
    this->nodes_data = std::move(other.nodes_data);
    this->edges_data.set_pointer(&(this->nodes_data));
    this->nodes_data.set_pointer(&(this->edges_data));
}

template<typename NData, typename EData>
UndirectedGraph<NData, EData> &UndirectedGraph<NData, EData>::operator=(const UndirectedGraph<NData, EData> &other) {
    this->edges_data = other.edges_data;
    this->nodes_data = other.nodes_data;
    this->edges_data.set_pointer(&(this->nodes_data));
    this->nodes_data.set_pointer(&(this->edges_data));
    return *this;
}

template<typename NData, typename EData>
UndirectedGraph<NData, EData> &UndirectedGraph<NData, EData>::operator=(UndirectedGraph<NData, EData> &&other) noexcept {
    this->edges_data = std::move(other.edges_data);
    this->nodes_data = std::move(other.nodes_data);
    this->edges_data.set_pointer(&(this->nodes_data));
    this->nodes_data.set_pointer(&(this->edges_data));
    return *this;
}
//endregion

#endif //DU2_REFACTOREDV2_GRAPH_H
