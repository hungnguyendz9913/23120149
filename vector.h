#ifndef VECTOR
#define VECTOR

#include <stdexcept>
#include <algorithm>
#include <iostream>
using namespace std;

template<typename T>
class vectorh {
private:
    T* data;
    int sz;
    int cap;

    void resize(int new_cap) {
        T* new_data = new T[new_cap];
        for (int i = 0; i < sz; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

    int partition(T* data, int low, int high, bool (*cmp)(const T&, const T&)) {
        T pivot = data[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (cmp(data[j], pivot)) {
                i++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i + 1], data[high]);
        return i + 1;
    }

    void quicksort(T* data, int low, int high, bool (*cmp)(const T&, const T&)) {
        if (low < high) {
            int pi = partition(data, low, high, cmp);

            quicksort(data, low, pi - 1, cmp);
            quicksort(data, pi + 1, high, cmp);
        }
    }

    void quicksort(T* data, int size, bool (*cmp)(const T&, const T&)) {
        quicksort(data, 0, size - 1, cmp);
    }

public:
    vectorh() : data(nullptr), sz(0), cap(0) {}

    int size() const {
        return sz;
    }

    int capacity() const {
        return cap;
    }

    bool empty() const {
        return sz == 0;
    }

    T& operator[](int index) {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& at(int index) {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("error");
        }
        return data[index];
    }

    const T& at(int index) const {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("error");
        }
        return data[index];
    }

    void push_back(const T& value) {
        if (sz == cap) {
            resize((cap == 0) ? 1 : 2 * cap);
        }
        data[sz++] = value;
    }

    void push_back(T&& value) {
        if (sz == cap) {
            resize((cap == 0) ? 1 : 2 * cap);
        }
        data[sz++] = std::move(value);
    }

    void pop_back() {
        if (sz > 0) {
            --sz;
        }
    }

    void clear() {
        delete[] data;
        sz = 0;
        cap = 0;
    }

    void reserve(int new_cap) {
        if (new_cap > cap) {
            resize(new_cap);
        }
    }

    void shrink_to_fit() {
        if (sz < cap) {
            resize(sz);
        }
    }

    T* begin() {
        return data;
    }

    const T* begin() const {
        return data;
    }

    T* end() {
        return data + sz;
    }

    const T* end() const {
        return data + sz;
    }

    void sort(bool (*cmp)(const T&, const T&)) {
        quicksort(data, sz, cmp);
    }
};

#endif
