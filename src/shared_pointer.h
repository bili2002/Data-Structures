#pragma once

#include "utility.h"
#include "control_block.h"
#include "weak_pointer.h"


template <typename T> //TO ADD DELETER, ALLOCATOR
class SharedPointer_ {
    template <typename U>
    friend class WeakPointer_;

    template <typename U>
    friend class SharedPointer_;

protected:
    T* ptr;
    ControlBlock_* controlBlock;

private:
    void _copy(const SharedPointer_<T>& oth) noexcept {
        this->ptr = oth.ptr;
        this->controlBlock = oth.controlBlock;

        this->controlBlock->add_shared();
    }

    void _move(SharedPointer_<T>&& oth) {
        this->ptr = oth.ptr;
        this->controlBlock = oth.controlBlock;

        oth.ptr = nullptr;
        oth.controlBlock = nullptr;
    }

    void _destruct() {
        if (this->controlBlock == nullptr) {
            return;
        }
        
        this->controlBlock->remove_shared();

        if (this->controlBlock->get_shared() == 0) {
            delete this->ptr;
            this->ptr = nullptr;

            if (this->controlBlock->get_weak() == 0) {
                delete this->controlBlock;
            }
        }
    }


public:
    constexpr SharedPointer_() noexcept : 
        ptr(nullptr), controlBlock(nullptr) {}

    constexpr SharedPointer_(nullptr_t_) noexcept : 
        ptr(nullptr), controlBlock(nullptr) {}

    SharedPointer_(T* obj) noexcept :
        ptr(obj), controlBlock(new ControlBlock_()) {}

    SharedPointer_(const SharedPointer_<T>& oth) noexcept {
        this->_copy(oth);
    }

    SharedPointer_(SharedPointer_<T>&& oth) noexcept {
        this->_move(move_(oth));
    }

    SharedPointer_(const WeakPointer_<T>& weak_ptr) noexcept {
        this->ptr = weak_ptr.ptr;
        this->controlBlock = weak_ptr.controlBlock;

        this->controlBlock->add_shared();
    }

    SharedPointer_& operator=(const SharedPointer_<T>& oth) noexcept {
        if (this != &oth) {
            this->_destruct();
            this->_copy(oth);
        };

        return *this;
    }

    SharedPointer_& operator=(SharedPointer_<T>&& oth) {
        this->_destruct();
        this->_move(move_(oth));

        return *this;
    }

    ~SharedPointer_() noexcept {
        this->_destruct();
    }

    T& operator*() const noexcept {
        return *(this->ptr);
    }

    T* operator->() const noexcept {
        return this->ptr;
    }

    size_t get() const noexcept {
        return this->ptr;
    }


public: //for testing
    size_t_ _get_count() const noexcept {
        return this->controlBlock->get_shared();
    }
};