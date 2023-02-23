
/*
 *   Author:  Aaron Carroll
 *   Email:   arncarroll@gmail.com
 *   Date:    2022
 *   File:
 *
 *   Program output
 *   --------------
 *   Copy of std::vector. Does not provide template for a specific allocator.
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
        typedef const iterator  const_iterator;
            
        // ctor's
        
        Vector();
        explicit Vector(size_t size);                       // create capacity_
        Vector(size_t size, value_type value);              // fill size with val                       
        Vector(std::initializer_list<T> init);              // initializer_list

        template <typename InputIterator>
        Vector(InputIterator first, InputIterator last);    // range
        Vector(const Vector& other);                        // copy
        Vector(Vector&& other);                             // move
        
        ~Vector() throw();
        Vector& operator=(Vector&& other);

        // accessors

        size_t getSize() const;
        size_t getCapacity() const;
        const_reference operator[](size_t index) const;
        const_reference front() const;
        const_reference back() const;
        const_iterator begin() const;
        const_iterator end() const;
        void print() const;
        
        // modifiers
        
        void pushBack(value_type value);
        void popBack();
        iterator erase(iterator position);
        reference operator[](size_t index);
        reference front();
        reference back();
        iterator begin();
        iterator end();

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

    // ------------------------------------------------------------------------
    // Iterator class interface 
    // ------------------------------------------------------------------------

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
        iterator(pointer ptr); 
        iterator(iterator&& other);
        //const iterator& operator=(const iterator& other);

        iterator& operator++();
        const iterator& operator++(int);
        iterator& operator--();
        const iterator& operator--(int);

        
     private:
        pointer iter_;
    };

    // ------------------------------------------------------------------------
    // Vector definitions
    // ------------------------------------------------------------------------



    /*
     *  constructors
     *  ------------
     */
    
    // default ctor

    template <typename T>                               
    Vector<T>::Vector() {
        ReAlloc(2);
    }

    // size ctor    

    template <typename T>                               
    Vector<T>::Vector(size_t size) {
        ReAlloc(size);
    }

    // fill size/generate ctor

    template <typename T>                               
    Vector<T>::Vector(size_t size, value_type value) {
        ReAlloc(size);
        std::generate(array_, array_ + size, [value](){return value;});
        size_ = size;
    }

    // initializer list ctor

    template <typename T>
    Vector<T>::Vector(std::initializer_list<T> init) {
        size_ = init.size();
        capacity_ = size_;
        array_ = new T[capacity_];
        std::copy(init.begin(), init.end(), array_);
    }

    // range ctor

    template <typename T>
    template <typename InputIterator>
    Vector<T>::Vector(InputIterator first, InputIterator last) {
        size_ = std::distance(first, last);
        capacity_ = size_;
        array_ = new value_type[capacity_];
        std::copy(first, last, array_);
    }    

    // copy ctor

    template <typename T>
    Vector<T>::Vector(const Vector& other) {
        pointer tmp = new value_type[other.capacity_];
        std::copy(other.array_, other.array_ + other.size_, tmp);
        Swap(tmp); 
    }
    
    // move ctor

    template <typename T>
    Vector<T>::Vector(Vector&& other) {
        Swap(other);
    }
    
    // operator=

    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector&& other) {
        if (this != &other) {
            Vector<T> tmp(std::move(other));
            Swap(tmp);
        }
        return *this;
    }
    
    // destructor

    template <typename T>                               
    Vector<T>::~Vector() throw() {
        // if not null
        if (array_)
            delete[] array_;
    }

    /*
     *  accessors
     *  ---------
     *  Const functions that do not change and data members value.
     */

    // getSize()
   
    template <typename T>                                   
    size_t
    Vector<T>::getSize() const {
        return size_;
    }
    
    // getCapacity()
    
    template <typename T>                               
    size_t
    Vector<T>::getCapacity() const {
        return capacity_;
    }
    
    // operator [] const
    
    template <typename T>                               
    Vector<T>::const_reference
    Vector<T>::operator[](size_t index) const {
        assert(index <= size_ && index >= 0);
        return array_[index];
    }

    // front() const
    
    template <typename T>                               
    Vector<T>::const_reference 
    Vector<T>::front() const {
        return array_;
    }

    // back() const
    
    template <typename T>
    Vector<T>::const_reference 
    Vector<T>::back() const {
        return array_ + size_ - 1;
    }
    
    /*
     *  begin() const
     *  -----------
     *  Should be a const copy iterator return type. Typedef found in Vector
     */
    
    template <typename T>
    Vector<T>::const_iterator 
    Vector<T>::begin() const {
        return const_iterator(array_);
    }
    
    
    /*
     *  end() const
     *  -----------
     *  Should be a const copy iterator return type. Typedef found in Vector
     */

    template <typename T>
    Vector<T>::const_iterator 
    Vector<T>::end() const {
        return const_iterator(array_ + size_);
    }

    // print() const
    
    template <typename T>                               
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

    // front()
    
    template <typename T>
    Vector<T>::reference 
    Vector<T>::front() {
        return array_[0];
    }

    // back()
   
    template <typename T>
    Vector<T>::reference 
    Vector<T>::back() {
        return array_[size_ - 1];
    }
    
    // operator[]
    
    template <typename T>
    Vector<T>::reference
    Vector<T>::operator[](size_t index) {
        assert(index <= size_ && index >= 0);
        return array_[index];
    }
    
    // pushBack()
    
    template <typename T>
    void 
    Vector<T>::pushBack(value_type value) {
        if (size_ >= capacity_)
            ReAlloc(capacity_ * 2 + 1);
        array_[size_] = value;
        ++size_;
    }
    
    // popBack()
    
    template <typename T>
    void 
    Vector<T>::popBack() {
        if(size_ > 0) {
            pointer element = &array_[size_-1];
            element->~T();
            --size_;
        }
    }

    /*
     *  begin() 
     *  -------
     *  Should not be pointer or reference rather the return should be a copy
     *  of the pointer to the begining of the array_ as to not modify the 
     *  array_ pointer its self. The iterator is only used to traverse the 
     *  array_
     */

    template <typename T>
    Vector<T>::iterator
    Vector<T>::begin() {
        return iterator(array_);
    }
    
     /*
     *  end() 
     *  -------
     *  Should not be pointer or reference rather the return should be a copy
     *  of the pointer to the end of the array_ as to not modify the 
     *  array_ end pointer its self. The iterator is only used to traverse 
     *  the array_
     */
    
    template <typename T>
    Vector<T>::iterator
    Vector<T>::end() {
        return iterator(array_ + size_);
    }


    // ------------------------------------------------------------------------
    // Vector private member functions -> helpers
    // ------------------------------------------------------------------------
    
    // ReAlloc()

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
    
    // Swap()
    template <typename T>
    void 
    Vector<T>::Swap(Vector<T>& other) {
        std::swap(array_, other.array_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // ------------------------------------------------------------------------
    // iterator class definitions
    // ------------------------------------------------------------------------

    
    /*
     *  iterator constructors
     *  ---------------------
     */
    
    template <typename T>
    Vector<T>::iterator::iterator() : iter_(0) {}
    
    template <typename T>
    Vector<T>::iterator::iterator(typename iterator::pointer ptr) : iter_(ptr)
    {}

    template <typename T>
    Vector<T>::iterator::iterator(typename Vector<T>::iterator&& other) 
        : iter_(std::move(other.iter_)) 
    {}
}

#endif
