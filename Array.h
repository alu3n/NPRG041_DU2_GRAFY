//
// Created by Vojtěch Pröschl on 25.02.2022.
//

//Note: Destructor isn't necessary due to the use of the smart pointers

#ifndef DU2_REFACTOREDV2_ARRAY_H
#define DU2_REFACTOREDV2_ARRAY_H

#include <memory>
#include <array>
#include <vector>

template<typename T>
class Array{
    /**
     * This class is an custom container which does not invalidate location of its elements during its entire lifetime.
     */
public:
    size_t block_size{10};
    size_t element_count{0};
    std::vector<std::unique_ptr<T[]>> data;
public:
    //Constructors
    Array<T>() = default;
    explicit Array<T>(size_t);
    //Basic container methods
    size_t size() const;
    void push_back(const T &);
    void pop_back();
    T& at(size_t) const;
    T& operator[](size_t) const;
    //Copy/move constructors/assignments
    Array(const Array<T> & other); //Copy constructor
    Array(Array<T> && other) noexcept; //Move constructor
    Array<T> & operator=(const Array<T> & other); //Copy assignment
    Array<T> & operator=(Array<T> && other) noexcept; //Move assignment

    struct iterator{
        /**
         * This struct is an forward iterator for the Array class. Changes to the array don't affect validity of the iterator.
         */
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;

        iterator(size_t index, size_t block_size, const std::vector<std::unique_ptr<T[]>> * data);

        T& operator*() const;
        T* operator->();

        iterator& operator++();
        iterator operator++(int);

        friend bool operator==(const iterator & a, const iterator & b){
            if(a.index == b.index) {
                return true;
            }
            else{
                return false;
            }
        }
        friend bool operator!=(const iterator & a, const iterator & b){
            if(a.index == b.index) {
                return false;
            }
            else{
                return true;
            }
        }
    private:
        const std::vector<std::unique_ptr<T[]>> * data;
        size_t index;
        size_t array_size;
    };

    Array<T>::iterator begin() const;
    Array<T>::iterator end() const;
};

//region Constructor/destructor Implmentation
template<typename T>
Array<T>::Array(size_t block_size) {
    this->block_size = block_size;
}

//endregion

//region Basic Container Methods

template<typename T>
size_t Array<T>::size() const{
    return element_count;
}

template<typename T>
void Array<T>::push_back(const T & item) {
    if(element_count % block_size == 0){
        data.push_back(std::make_unique<T[]>(block_size));
        data[element_count / block_size][0] = item;
    }
    else{
        data[element_count / block_size][element_count % block_size] = item;
    }
    element_count++;
}

template<typename T>
void Array<T>::pop_back(){
    if(element_count == 0) {
        throw std::domain_error("You cannot pop element from an empty array!");
        return;
    }
    if(element_count % block_size == 0){
        data.pop_back();
    }
    element_count--;
}

template<typename T>
T & Array<T>::at(size_t index) const {
    if(index > element_count){
        throw std::range_error("This element isn't defined in the array!");
    }
    return data[index / block_size][index % block_size];
}

template<typename T>
T& Array<T>::operator[](size_t index) const {
    return this->at(index);
}

//endregion

//region Copy/move constructors/assignments

//Copy constructor
template<typename T>
Array<T>::Array(const Array<T> &other) {
    block_size = other.block_size;
    element_count = other.element_count;
    for(auto && x : other.data){
        data.push_back(std::make_unique<T[]>(block_size));
        for(size_t i = 0; i < block_size; i++) data.back()[i] = x[i];
    }
}

//Move constructor
template<typename T>
Array<T>::Array(Array<T> && other) noexcept {
    block_size = other.block_size;
    element_count = other.element_count;
    data = std::move(other.data);
    other.element_count = 0;
    other.data.clear();
}

//Copy assignment
template<typename T>
Array<T> & Array<T>::operator=(const Array<T> & other){
    element_count = other.element_count;
    block_size = other.block_size;
    data.clear();
    for(auto && x : other.data){
        data.push_back(std::make_unique<T[]>(block_size));
        for(size_t i = 0; i < block_size; i++) data.back()[i] = x[i];
    }
    return *this;
}

//Move assignment
template<typename T>
Array<T> & Array<T>::operator=(Array<T> && other) noexcept{
    this->block_size = other.block_size;
    this->element_count = other.element_count;
    this->data = std::move(other.data);
    other.element_count = 0;
    other.data.clear();
    return *this;
}

template<typename T>
typename Array<T>::iterator Array<T>::begin() const {
//    return InflatableArray<T>::iterator
    return Array<T>::iterator(0, block_size, &data);
}

template<typename T>
typename Array<T>::iterator Array<T>::end() const{
//    return InflatableArray<T>::iterator
    return Array<T>::iterator(element_count, block_size, &data);
}



//endregion

//region Iterator implementation


template<typename T>
T &Array<T>::iterator::operator*() const {
    return data->at(index / array_size)[index%array_size];
    //return data[index / array_size][index % array_size];
}

template<typename T>
T* Array<T>::iterator::operator->() {
    return &(data[index / array_size][index % array_size]);
}

template<typename T>
typename Array<T>::iterator & Array<T>::iterator::operator++() {
    index++;
    return *this;
}

template<typename T>
typename Array<T>::iterator Array<T>::iterator::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
Array<T>::iterator::iterator(size_t index, size_t block_size, const std::vector<std::unique_ptr<T[]>> * data) {
    this->index = index;
    this->array_size = block_size;
    this->data = data;
}

//endregion

#endif //DU2_REFACTOREDV2_ARRAY_H
