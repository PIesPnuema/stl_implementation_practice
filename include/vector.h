
/*
 *   Author:  Aaron Carroll
 *   Email:   arncarroll@gmail.com
 *   Date:    2022
 *   File:
 *
 *   Program output
 *   --------------
 *
 *
 */


#ifndef AARONCARROLL_VECTOR_H
#define AARONCARROLL_VECTOR_H

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cassert>

namespace AaronCarroll {

template <typename T>
class Vector {
 public:
    
    class iterator;

    // typedef's
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
        
    // ctor's
    Vector();
    explicit Vector(size_t size);                       // create capacity_
    Vector(size_t size, value_type value);              // fill size with val
                                                
    template <typename InputIterator>
    Vector(InputIterator first, InputIterator last);    // range
    Vector(const Vector& other);                        // copy
    Vector(const Vector&& other);                       // move
    
    ~Vector() throw();
    Vector& operator=(const Vector&& other);

    // accessors
    size_t getSize() const;
    size_t getCapacity() const;
    const_reference operator[](size_t index) const;
    const_reference front() const;
    const_reference back() const;
    const iterator& begin() const;
    const iterator& end() const;
    void print() const;
    
    // modifiers
    void pushBack(value_type value);
    void popBack();
    iterator erase(iterator position);
    reference operator[](size_t index);
    reference front();
    reference back();
    iterator& begin();
    iterator& end();

    // overloads
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    bool operator>(const Vector& other) const;
    bool operator>=(const Vector& other) const;
    bool operator<(const Vector& other) const;
    bool operator<=(const Vector& other) const;

 private:
    void Swap(Vector<T>& other);
    void ReAlloc(size_t n);

    pointer array_ = nullptr;
    size_t size_ = 0; 
    size_t capacity_ = 0;
};

// ----------------------------------------------------------------------------
// Iterator class interface 
// ----------------------------------------------------------------------------

template <typename T>
class Vector<T>::iterator : std::iterator<std::random_access_iterator_tag, T> {
 public:
    
    friend class Vector<T>;
    
    // typedef's
    typedef Vector<T>::value_type       value_type;
    typedef Vector<T>::pointer          pointer;
    typedef Vector<T>::const_pointer    const_pointer;
    typedef Vector<T>::reference        reference;
    typedef Vector<T>::const_reference  const_reference; 

    iterator();
    iterator(pointer element); 
    iterator(const iterator& other);
    const iterator& operator=(const iterator& other);

    iterator& operator++();
    const iterator& operator++(int);
    iterator& operator--();
    const iterator& operator--(int);

    
 private:
    pointer iter_;
};

// ----------------------------------------------------------------------------
// Vector definitions
// ----------------------------------------------------------------------------



/*
 *  constructors
 *  ------------
 */

template <typename T>                               // default ctor
Vector<T>::Vector() {
    ReAlloc(2);
}

template <typename T>                               // size ctor
Vector<T>::Vector(size_t size) {
    ReAlloc(size);
}

template <typename T>                               // size/generate ctor
Vector<T>::Vector(size_t size, value_type value) {
    ReAlloc(size);
    std::generate(array_, array_ + size, [value](){return value;});
    size_ = size;
}

template <typename T>                               // destructor
Vector<T>::~Vector() throw() {
    delete[] array_;
}


/*
 *  accessors
 *  ---------
 *  Const functions that do not change and data members value.
 */

template <typename T>                               // getSize()
size_t
Vector<T>::getSize() const {
    return size_;
}

template <typename T>                               // getCapacity()
size_t
Vector<T>::getCapacity() const {
    return capacity_;
}

template <typename T>                               // operator[] const
Vector<T>::const_reference
Vector<T>::operator[](size_t index) const {
    assert(index <= size_ && index >= 0);
    return array_[index];
}

template <typename T>                               // front() const
Vector<T>::const_reference 
Vector<T>::front() const {
    return array_;
}

template <typename T>
Vector<T>::const_reference 
Vector<T>::back() const {
    return array_ + size_ - 1;
}

template <typename T>                               // print()
void 
Vector<T>::print() const {
    std::for_each(array_, array_ + size_,[](value_type element) {
            std::cout << element << ", ";
    });
    std::cout << "\n";
}


/*
 *  modifiers
 *  ---------
 *  Functions that change the value of the data memebers. 
 */

template <typename T>
Vector<T>::reference 
Vector<T>::front() {
    return array_[0];
}

template <typename T>
Vector<T>::reference 
Vector<T>::back() {
    return array_[size_ - 1];
}

template <typename T>
Vector<T>::reference
Vector<T>::operator[](size_t index) {
    assert(index <= size_ && index >= 0);
    return array_[index];
}

template <typename T>
void 
Vector<T>::pushBack(value_type value) {
    if (size_ >= capacity_)
        ReAlloc(capacity_ * 2 + 1);
    array_[size_] = value;
    ++size_;
}

template <typename T>
void 
Vector<T>::popBack() {
    if(size_ > 0) {
        pointer element = &array_[size_-1];
        element->~T();
        --size_;
    }
}

// ----------------------------------------------------------------------------
// Vector private member functions -> helpers
// ----------------------------------------------------------------------------
template <typename T>
void
Vector<T>::ReAlloc(size_t newCapacity) {
    
    pointer temp = new Vector::value_type[newCapacity];

    // shrink only
    if (newCapacity < size_)
        size_ = newCapacity;
    
    for (size_t index = 0; index < size_; ++index) 
        temp[index] = std::move(array_[index]);
    delete[] array_;
    array_ = temp;
    capacity_ = newCapacity;
}

template <typename T>
void
Vector<T>::Swap(Vector<T>& other) {
    std::swap(array_, other->array_);
    std::swap(size_, other->size_);
    std::swap(capacity_, other->capacity_);
}



}

#endif
