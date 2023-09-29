#pragma once

#include "utility.h"

class ControlBlock_ {
    size_t_ shared_counter;
    size_t_ weak_counter;

    void _destruct() noexcept {}

public:
    constexpr ControlBlock_() noexcept : 
        shared_counter(0), weak_counter(0) {
            this->add_shared();
        }

    ~ControlBlock_() noexcept {
        _destruct();
    }
        
    ControlBlock_(const ControlBlock_& oth)             = delete;
    ControlBlock_(ControlBlock_&& oth)                  = delete;
    ControlBlock_& operator=(const ControlBlock_& oth)  = delete;
    ControlBlock_& operator=(ControlBlock_&& oth)       = delete;

    void add_shared() noexcept {
        this->shared_counter += 1;
        this->weak_counter += 1;
    }  
    
    void remove_shared() noexcept {
        this->shared_counter -= 1;
        this->weak_counter -= 1;
    }

    void add_weak() noexcept {
        this->weak_counter += 1;
    }

    void remove_weak() noexcept {
        this->weak_counter -= 1;
    }

public: //for testing
    size_t_ get_shared() const noexcept {
        return this->shared_counter;
    }

    size_t_ get_weak() const noexcept {
        return this->weak_counter;
    }
};