#pragma once

#include "utility.h"
#include "control_block.h"
#include "shared_pointer.h"

template<typename T> 
class WeakPointer_ {
    template<typename U>
    friend class WeakPointer_;

    template<typename U>
    friend class SharedPointer_;

protected:
    T* ptr;
    ControlBlock_* controlBlock;

private:
    void _copy(const WeakPointer_<T>& oth) noexcept {
        this->ptr = oth.ptr;
        this->controlBlock = oth.controlBlock;

        this->controlBlock->add_weak();
    }

    void _move(WeakPointer_<T>&& oth) {
        this->ptr = oth.ptr;
        this->controlBlock = oth.controlBlock;

        oth.ptr = nullptr;
        oth.controlBlock = nullptr;
    }

    void _destruct() {
        if (this->controlBlock == nullptr) {
            return;
        }

        this->controlBlock->remove_weak();

        if (this->controlBlock->get_weak() == 0) {
            delete this->controlBlock;
        }
    }


public:
    constexpr WeakPointer_() noexcept : 
        ptr(nullptr), controlBlock(nullptr) {}

    constexpr WeakPointer_(nullptr_t_) noexcept : 
        ptr(nullptr), controlBlock(nullptr) {}

    WeakPointer_(const WeakPointer_<T>& oth) noexcept {
        this->_copy(oth);
    }

    WeakPointer_(WeakPointer_<T>&& oth) noexcept{
        this->_move(move_(oth));
    }

    WeakPointer_(const SharedPointer_<T>& oth) noexcept {
        this->ptr = oth.ptr;
        this->controlBlock = oth.controlBlock;

        this->controlBlock->add_weak();
    }

    WeakPointer_& operator=(const WeakPointer_<T>& oth) noexcept {
        if (this != &oth) {
            this->_destruct();
            this->_copy(oth);
        };

        return *this;
    }

    WeakPointer_& operator=(WeakPointer_<T>&& oth) {
        this->_destruct();
        this->_move(move_(oth));

        return *this;
    }

    ~WeakPointer_() noexcept {
        this->_destruct();
    }

    bool expired() const noexcept {
        return this->controlBlock->get_shared() == 0;
    }

    SharedPointer_<T> lock() const {//?!
        if (this->expired()) {
            throw("WeakPointer_ used when expired.");
        }

        return SharedPointer_<T>(*this);
    }

public: //for testing
    size_t_ _get_count() const noexcept {
        return this->controlBlock->get_weak();
    }
};