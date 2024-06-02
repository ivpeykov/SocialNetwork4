#pragma once
#include <stdexcept>
#include <iostream>

template<typename T>
class Vector { //TODO: make methods const where  they can be

public:
    Vector() : capacity(3), size(0), data(nullptr) {

      data = new T[capacity];
       
    }

    Vector(const size_t capacity) : size(0), data(nullptr) {
       
        if (capacity == 0) {
            this->capacity = capacity;
            data = nullptr;
        }

        this->capacity = capacity;

        data = new T[capacity];
    }

    Vector(const Vector<T>& other) : data(nullptr), size(other.size), capacity(other.capacity + 3) {

        resize(capacity);

        for (size_t i = 0; i < other.size; i++) {
            data[i] = other.data[i];
        }
    }


    ~Vector() {
        delete[] data;
    }

    void pushBack(const T& element) {

        if (size == capacity) {

            if (size == 1 || capacity == 0) {
                resize(3);
            }

            else {
                resize(capacity + capacity / 2);
            }
        }
        data[size++] = element;
    }

    void resize(const size_t new_capacity) {

        if (new_capacity == 0) {
            throw std::invalid_argument("Cannot resize vector with new capacity equal to 0");
        }
        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    void erase(const size_t index) 
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    void popBack()
    {
        if (size == 0) {
            throw std::out_of_range("Pop back attempted on an empty vector");
        }
        delete[] data[size];
        --size;
    }

    void clear() {

        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;  
    }

    void printVectorToConsole() {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << std::endl;
        }
    }

    const T& operator[](const size_t index) const {

        if (index >= size) {
            throw std::out_of_range("Index out of bounds in operator[]");
        }
        return data[index];
    }
    
    T& operator[](const size_t index) {

        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    bool operator==(const Vector<T>& rhs) const 
    {
        if (size != rhs.size) {
            return false;
        }

        for (size_t i = 0; i < size; i++) {
            if (data[i] != rhs.data[i])
                return false;
        }

        return true;
    }

    bool operator!=(const Vector& rhs) const
    {
        return !(*this == rhs);
    }


    Vector& operator=(const Vector& rhs)
    {
        if (this != &rhs) {

            if (rhs.size == 0) {
                this->clear();
                data = new T[1];
                capacity = 1;
                return *this;
            }

            else {
                delete[] data;

                capacity = rhs.capacity;
                size = rhs.size;
                data = new T[capacity];

                for (size_t i = 0; i < rhs.size; ++i) {
                    data[i] = rhs.data[i];
                }
            }
        }
        return *this;    
    }

    T& front() const
    {
        return data[0];
    }

    T& back() const
    {
        if (size == 0)
            return data[0];

        return data[size - 1];
    }


    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

private:
    T* data;
    size_t capacity;
    size_t size; // Number of elements currently stored
};

