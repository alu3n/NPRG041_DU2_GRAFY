//
// Created by Vojtěch Pröschl on 25.02.2022.
//

#ifndef DU2_REFACTOREDV2_EXCEPTIONS_H
#define DU2_REFACTOREDV2_EXCEPTIONS_H

#include <string>

class Exception{
public:
    /**
     * This class is an abstract ancestor to all exceptions used in this program.
     */
    virtual std::string & what() = 0;
protected:
    std::string message;
};

class NonexistingItemException : public Exception{
public:
    /**
     * This class is used to report exceptions related to missing items.
     */
    std::string & what() override;
    static NonexistingItemException non_existent_node(size_t id,size_t size);
    static NonexistingItemException non_existent_edge(size_t id,size_t size);
    static NonexistingItemException non_existnet_pair_nodes(size_t source, size_t target, size_t size);
    static NonexistingItemException non_existent_pair_edge(size_t source, size_t target);
    static NonexistingItemException non_existent_pair_nodes_test(size_t source, size_t target, size_t size);
    static NonexistingItemException non_existent_source(size_t source, size_t size);
    static NonexistingItemException non_existent_target(size_t target, size_t size);
    static NonexistingItemException non_existent_pair_adding_edge(size_t source, size_t target, size_t size);
};

class ConflictingItemException : public Exception{
public:
    /**
    * This class is used to report exceptions related to item conflicts (i.e. reporting repeated addition of already existing item).
    */
    std::string & what() override;
    static ConflictingItemException already_taken_id(size_t id);
    static ConflictingItemException already_taken_id_edge(size_t id);
    static ConflictingItemException already_taken_pair(size_t source, size_t target);
};

class InvalidIdentifierException : public Exception{
public:
    /**
    * This class is used to report exceptions related to addition of items with invalid identifiers.
    */
    std::string & what() override;
    static InvalidIdentifierException wrong_id(size_t id, size_t size);
    static InvalidIdentifierException wrong_id_edge(size_t id, size_t size);
};

class UnavailableMemoryException : public Exception{
public:
    /**
    * This class is used to report exceptions related to problems with adding/editing datastructures storing items.
    */
    std::string & what() override;
    static UnavailableMemoryException cant_insert_to_container();
    static UnavailableMemoryException cant_insert_edge_to_container();
    static UnavailableMemoryException cant_extent_adjacency();
};

class FileProcessingException : public Exception{
public:
    /**
    * This class is used to report exceptions related to file i/o.
    */
    std::string & what() override;
    static FileProcessingException cant_open_output(const std::string & filename);
    static FileProcessingException cant_open_input(const std::string & filename);
};

#endif //DU2_REFACTOREDV2_EXCEPTIONS_H
