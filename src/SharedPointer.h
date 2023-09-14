#include <iostream>
#include <utility>
#include <cstddef>

using namespace std;


template <typename T>
class SharedPointer {
    std::size_t* cnt;
    T* ptr;

    void copy(const SharedPointer<T>& oth) {
        this->ptr = oth.ptr;
        this->cnt = oth.cnt;

        *this->cnt += 1;
    }

    void move_obj(T&& obj) {
        ptr = &obj;
        cnt = new size_t(1);
    }

    void move(SharedPointer<T>&& oth) {
        this->ptr = oth.ptr;
        this->cnt = oth.cnt;

        oth.ptr = nullptr;
        oth.cnt = nullptr;
    }

    void destruct() {
        *this->cnt -= 1;

        if (*this->cnt == 0) {
            delete[] this->ptr;
            delete this->cnt;
        }
    }


public:
    constexp SharedPointer() noexcept {
        cnt = nullptr;
        ptr = nullptr;
    }

    SharedPointer(T& obj) {
        ptr = *obj;
        cnt = new size_t(1);
    }

    SharedPointer(T* obj) {
        ptr = obj;
        cnt = new size_t(1);
    }

    SharedPointer(T&& obj) {
        this->move_obj(obj);
    }

    SharedPointer(const SharedPointer<T>& oth) {
        this->copy(oth);
    }

    SharedPointer(SharedPointer<T>&& oth) {
        this->move(oth);
    }

    SharedPointer& operator=(const SharedPointer<T>& oth) {
        this->destruct();

        if (&this != oth) {
            copy(oth);
        };

        return this;
    }

    SharedPointer& operator=(SharedPointer<T>&& oth) {
        *this->cnt -= 1;
        move(oth);

        return this;
    }

    SharedPointer& operator=(T&& oth) {
        this->move(oth);
    }

    ~SharedPointer() {
        this->destruct();
    }

    T& operator*() const {
        return *(this->ptr);
    }

    T* operator->() const {
        return this->ptr;
    }

    size_t get_count() const {
        return *this->cnt;
    }

    size_t get() const {
        return this->ptr;
    }
};