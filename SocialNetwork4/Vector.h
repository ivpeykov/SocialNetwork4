#pragma once
#include <stdexcept>
#include <iostream>


template<typename T>
class Vector {

public:
    Vector() : capacity(3), size(0) {

        data = new T[capacity];
    }

    Vector(const size_t capacity) : size(0) {


        if (capacity <= 0) {
            throw std::bad_alloc();
        }

        this->capacity = capacity;

        data = new T[capacity];
    }

    Vector(const T& other)
        :size(other.size), capacity(other.capacity + 3) {

        resize(capacity);

        for (int i = 0; i < other.size; i++) {
            data[i] = other.data[i];
        }
    }


    ~Vector() {
        delete[] data;
    }

    void pushBack(const T& element) {

        if (size == capacity) {

            if (size == 1) {
                resize(3);
            }

            else {
                resize(capacity + capacity / 2);
            }
        }
        data[size++] = element;
    }

    void resize(const size_t new_capacity) {

        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    void erase(const int index)
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        for (int i = index; i < size - 1; i++) {
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
        //data = nullptr; ?
        data = new T[1];
        size = 0;
        capacity = 1;
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

    bool operator==(const Vector& rhs) const
    {
        if (size != rhs.size) {
            return false;
        }

        for (int i = 0; i < size; i++) {
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
            if (rhs.size > size) {

                capacity = rhs.size + 3;
                resize(capacity);
            }

            for (int i = 0; i < rhs.size; i++) {
                data[i] = rhs.data[i];
            }

            size = rhs.size;
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