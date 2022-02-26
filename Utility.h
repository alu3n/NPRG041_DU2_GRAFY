//
// Created by Vojtěch Pröschl on 26.02.2022.
//

#ifndef DU2_REFACTOREDV2_UTILITY_H
#define DU2_REFACTOREDV2_UTILITY_H

#include <sstream>
#include "Node.h"
#include "Edge.h"

template<typename NData>
void string_to_node_components(const std::string & line, size_t & node_id, NData & node_data){
    /**
     * This function is for argument extraction for the Node constructor. It's necessary for the datatype in Node to implement >> operator.
     */
    std::istringstream line_stream(line);
    line_stream.seekg(6);
    line_stream >> node_id;
    line_stream.seekg(2,std::ios::cur);

    char letter_buffer = line_stream.get();
    std::string data_buffer;
    while(letter_buffer!='}'){
        data_buffer.push_back(letter_buffer);
        letter_buffer = line_stream.get();
    }

    std::istringstream data_stream(data_buffer);
    data_stream >> node_data;
}

template<typename EData>
void string_to_edge_components(const std::string & line, size_t & edge_id, size_t & source_id, size_t & target_id, EData & edge_data){
    /**
    This function is for argument extraction for the Edge constructor. It's necessary for the datatype in Edge to implement >> operator.
    */
    std::istringstream line_stream(line);
    line_stream.seekg(6);

    line_stream >> source_id;
    line_stream.seekg(3,std::ios::cur);

    line_stream >> edge_id;
    line_stream.seekg(2,std::ios::cur);

    char letter_buffer = line_stream.get();
    std::string data_buffer;
    while(letter_buffer!='}'){
        data_buffer.push_back(letter_buffer);
        letter_buffer = line_stream.get();
    }

    std::istringstream data_stream(data_buffer);
    data_stream >> edge_data;
    line_stream.seekg(4,std::ios::cur);

    line_stream >> target_id;
}

#endif //DU2_REFACTOREDV2_UTILITY_H
