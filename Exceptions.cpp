//
// Created by Vojtěch Pröschl on 21.02.2022.
//

#include "Exceptions.h"

//region NonexistingItemException Implementation
std::string & NonexistingItemException::what() {
    return message;
}

NonexistingItemException NonexistingItemException::non_existent_node(size_t id, size_t size) {
    NonexistingItemException e;
    e.message = "Attempting to access a nonexisting node with identifier " +
                std::to_string(id) +
                ", only " +
                std::to_string(size)+
                " nodes are available";
    return e;
}

NonexistingItemException NonexistingItemException::non_existent_edge(size_t id, size_t size) {
    NonexistingItemException e;
    e.message = "Attempting to access a nonexisting edge with identifier " +
                std::to_string(id) +
                ", only " +
                std::to_string(size) +
                " edges are available";
    return e;
}

NonexistingItemException NonexistingItemException::non_existent_pair_edge(size_t source, size_t target) {
    NonexistingItemException e;
    e.message = "Attempting to access a nonexisting edge between a pair of nodes with identifiers " +
                std::to_string(source) +
                " and " +
                std::to_string(target);
    return e;
}

NonexistingItemException NonexistingItemException::non_existnet_pair_nodes(size_t source, size_t target, size_t size) {
    NonexistingItemException e;
    e.message = "Attempting to access an edge between a nonexisting pair of nodes with identifiers " +
                std::to_string(source) +
                " and " +
                std::to_string(target) +
                ", only " +
                std::to_string(size) +
                " nodes are available";
    return e;
}

NonexistingItemException NonexistingItemException::non_existent_pair_nodes_test(size_t source, size_t target,size_t size) {
    NonexistingItemException e;
    e.message = "Attempting to test the existence of an edge between a nonexisting pair of nodes with identifiers " +
                std::to_string(source) +
                " and " +
                std::to_string(target) +
                ", only " +
                std::to_string(size) +
                " nodes are available";
    return e;
}

NonexistingItemException NonexistingItemException::non_existent_source(size_t source, size_t size) {
    NonexistingItemException e;
    e.message = "Attempting to access an edge outgoing from a nonexisting source node with identifier " +
                std::to_string(source) +
                ", only " +
                std::to_string(size) +
                " nodes are available";
    return e;
}

NonexistingItemException NonexistingItemException::non_existent_target(size_t target, size_t size) {
    NonexistingItemException e;
    e.message = "Attempting to access an edge incoming to a nonexisting target node with identifier " +
                std::to_string(target) +
                ", only " +
                std::to_string(size) +
                " nodes are available";
    return e;
}

NonexistingItemException NonexistingItemException::non_existent_pair_adding_edge(size_t source, size_t target,
                                                                                 size_t size) {
    NonexistingItemException e;
    e.message = "Attempting to add a new edge between a nonexisting pair of nodes with identifiers " +
                std::to_string(source) +
                " and " +
                std::to_string(target) +
                ", only " +
                std::to_string(size) +
                " nodes are available";
    return e;
}
//endregion

//region InvalidIdentifierException
std::string & InvalidIdentifierException::what() {
    return message;
}

InvalidIdentifierException InvalidIdentifierException::wrong_id(size_t id, size_t size) {
    InvalidIdentifierException e;
    e.message = "Attempting to add a new node with invalid identifier " +
                std::to_string(id) +
                ", expected " +
                std::to_string(size) +
                " instead";
    return e;
}

InvalidIdentifierException InvalidIdentifierException::wrong_id_edge(size_t id, size_t size) {
    InvalidIdentifierException e;
    e.message = "Attempting to add a new edge with invalid identifier " +
                std::to_string(id) +
                ", expected " +
                std::to_string(size) +
                " instead";
    return e;
}
//endregion

//region ConflictingItemException
std::string & ConflictingItemException::what(){
    return message;
}

ConflictingItemException ConflictingItemException::already_taken_id(size_t id){
    ConflictingItemException e;
    e.message = "Attempting to add a new node with identifier " +
                std::to_string(id) +
                " which already is associated with another existing node";
    return e;
}

ConflictingItemException ConflictingItemException::already_taken_id_edge(size_t id) {
    ConflictingItemException e;
    e.message = "Attempting to add a new edge with identifier " +
                std::to_string(id) +
                " which already is associated with another existing edge";
    return e;
}

ConflictingItemException ConflictingItemException::already_taken_pair(size_t source, size_t target) {
    ConflictingItemException e;
    e.message = "Attempting to add a new edge between a pair of nodes with identifiers " +
                std::to_string(source) +
                " and " +
                std::to_string(target) +
                " which already are connected with another existing edge";
    return e;
}

//endregion

//region UnavailableMemoryException
std::string & UnavailableMemoryException::what(){
    return message;
}

UnavailableMemoryException UnavailableMemoryException::cant_insert_to_container() {
    UnavailableMemoryException e;
    e.message = "Unable to insert a new node record into the underlying container of nodes";
    return e;
}

UnavailableMemoryException UnavailableMemoryException::cant_insert_edge_to_container() {
    UnavailableMemoryException e;
    e.message = "Unable to insert a new edge record into the underlying container of edges";
    return e;
}

UnavailableMemoryException UnavailableMemoryException::cant_extent_adjacency() {
    UnavailableMemoryException e;
    e.message = "Unable to extend the underlying adjacency matrix container for edges";
    return e;
}
//endregion

//region FileProcessingException
std::string & FileProcessingException::what(){
    return message;
}

FileProcessingException FileProcessingException::cant_open_input(const std::string & filename) {
    FileProcessingException e;
    e.message = "Unable to open an input file " + filename;
    return e;
}

FileProcessingException FileProcessingException::cant_open_output(const std::string &filename) {
    FileProcessingException e;
    e.message = "Unable to open an output file " + filename;
    return e;
}
//endregion

