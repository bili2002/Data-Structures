#include "utility.h"

template<typename T>
class Vector_ {
protected:
    size_t_ _size;
    size_t_ _capacity;
    T* _data;

private: 
    void _copy(const Vector_<T>& oth) noexcept {
        this->_size = oth._size;
        this->_capacity = oth._capacity;

        this->_data = new T[this->_capacity];
        for (size_t_ i=0; i<this->_size; i++) {
            this->_data[i] = oth._data[i];
        }
    }

    void _move(Vector_<T>&& oth) noexcept {
        this->_size = oth._size;
        this->_capacity = oth._capacity;
        this->_data = oth._data;

        oth._data = nullptr;
    } 

    void _destruct() noexcept {
        if (_data == nullptr) {
            return;
        }

        delete[] _data;
    } 

    void _expand() noexcept {
        this->_capacity *= 2;
        
        T* temp_data = new T[this->_capacity];
        for (size_t_ i=0; i<this->_size; i++) {
            temp_data[i] = move_(this->_data[i]);
        }

        swap(temp_data, this->_data);
        delete[] temp_data;
    }

    void _may_expand() noexcept {
        if (this->_size == this->_capacity) {
            this->_expand();
        }
    }

public:
    constexpr Vector_() noexcept :
        _size(0), _capacity(1), _data(new T[1]) {}
    
    Vector_(const Vector_<T>& oth) noexcept {
        this->_copy(oth);
    }

    Vector_(Vector_&& oth) noexcept {
        this->_move(move_(oth));
    } 

    Vector_<T>& operator=(const Vector_& oth) noexcept {
        if (this != *oth) {
            this->_destruct();
            this->_copy(oth);
        }

        return *this;
    }

    Vector_<T>& operator=(Vector_&& oth) noexcept {
        this->_destruct();
        this->_move(move_(oth));

        return *this;
    }

    constexpr Vector_(size_t_ _size, const T& value) noexcept :
     _size(_size), _capacity(_size), _data(new T[_size]) {
        for (size_t_ i=0; i<this->_size; i++) {
            this->_data[i] = value;
        }
    }
    
    ~Vector_() {
        this->_destruct();
    }

    constexpr size_t_ size() const noexcept {
        return this->_size;
    }

    void push_back(const T& value) noexcept {
        this->_may_expand();
        this->_data[this->_size++] = value;
    }

    constexpr T& operator[](size_t_ idx) noexcept {
        return this->_data[idx];
    }

    constexpr T* begin() noexcept {
        return this->_data;
    }

    constexpr T* end() noexcept {
        return this->_data + this->_size;
    }

    constexpr const T* cbegin() const noexcept {
        return this->_data;
    }

    constexpr const T* cend() const noexcept {
        return this->_data + this->_size; 
    }
};
