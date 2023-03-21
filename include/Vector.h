/*
 *   File:         Vector.h
 *   Author:       Aaron Carroll
 *   Email:        arncarroll@gmail.com
 *   Created:      2023-02-12
 *   Modified:     2023-03-21
 *   License:      MIT License
 *   Copyright:    (C) 2023-03-21 Aaron Carroll
 *
 *   Dependencies
 *   ------------
 *
 *
 *   Program output
 *   --------------
 *   recreating the std::vector. Does not provide template for a specific 
 *   allocator.
 *
 */


#ifndef STL_IMPLEMENTATION_PRACTICE_VECTOR_H
#define STL_IMPLEMENTATION_PRACTICE_VECTOR_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <utility>

namespace Stl_Implementation_Practice { namespace Vector {

    template <typename T>
    class Vector {
     public:
        
        class iterator;
        class const_iterator;

        // typedef's
        typedef T                        value_type;
        typedef T*                       pointer;
        typedef const T*                 const_pointer;
        typedef T&                       reference;
        typedef const T&                 const_reference;
        typedef typename std::ptrdiff_t  difference_type;

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
        const_iterator cBegin() const;
        const_iterator cEnd() const;
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
        
        // friend class
        
        friend class Vector<T>;

        
        // Vector Qualified dependant typedefs
        
        typedef typename Vector<T>::value_type       value_type;
        typedef typename Vector<T>::pointer          pointer;
        typedef typename Vector<T>::const_pointer    const_pointer;
        typedef typename Vector<T>::reference        reference;
        typedef typename Vector<T>::const_reference  const_reference;
        typedef typename Vector<T>::difference_type  difference_type;

        // iterator typedefs
        
        typedef const iterator                       const_iterator;
        typedef iterator&                            iterator_reference;
        typedef const iterator&                      const_iterator_reference;
        
        // friend functions
        friend std::ostream& operator<<(std::ostream& os, 
                const_iterator_reference it); 
        
        // constructors -> we do not need a move ctor in for an iterator b/c
        // we are not moving resources but mearly viewing them.
        
        iterator();
        iterator(pointer ptr);
        // return type must not be const.
        iterator_reference operator=(const_iterator_reference other);

        // destructor
        
        ~iterator() = default;

        // access operators

        reference operator*();
        const_reference operator*() const;
        
        pointer operator->();
        const_pointer operator->() const;
        
        // increment and decrement operators

        iterator_reference operator++();
        const_iterator operator++(int);
        iterator_reference operator--();
        const_iterator operator--(int);
        
        // arithmatic operator 
        
        iterator operator+(size_t size) const; 
        iterator_reference operator+=(size_t size); 
        difference_type operator-(const_iterator_reference other) const; 
        iterator_reference operator-=(size_t size);
        iterator operator-(size_t size) const;

        // comparison operators
        
        bool operator==(const_iterator_reference other) const;
        bool operator!=(const_iterator_reference other) const;
        bool operator>(const_iterator_reference other) const;
        bool operator>=(const_iterator_reference other) const;
        bool operator<(const_iterator_reference other) const;
        bool operator<=(const_iterator_reference other) const;

        // subscript operator
        reference operator[](size_t size);

     private:
        pointer iter_;
    };
    
    //-------------------------------------------------------------------------
    // const iterator
    // ------------------------------------------------------------------------

    template <typename T>
    class Vector<T>::const_iterator : 
        public std::iterator<std::random_access_iterator_tag, const T> {
     public:
        
        // friend class
        
        friend class Vector<T>;

        // Vector qualified dependant typedefs
        
        typedef typename Vector<T>::value_type        value_type;
        typedef typename Vector<T>::const_pointer     const_pointer;
        typedef typename Vector<T>::const_reference   const_reference;
        typedef typename Vector<T>::difference_type   difference_type;

        // iterator typedefs
        
        typedef const_iterator&                       const_iterator_reference;
        
        // friend functions
        
        friend std::ostream& operator<<(std::ostream& os, 
                const_iterator_reference it); 

        // constructors
        
        const_iterator();
        const_iterator(const_pointer ptr);
        const_iterator(const iterator& other);

        // assignment operator
        const_iterator_reference operator=(const_iterator_reference other);

        // destructor
        
        ~const_iterator() = default;

        // access operators
        
        const_reference operator*() const;
        const_pointer operator->() const;

        // increment and decrement operators
        
        const_iterator_reference operator++();
        const_iterator operator++(int);
        const_iterator_reference operator--();
        const_iterator operator--(int);

        // arithmetic operators        
        
        const_iterator operator+(size_t size) const; 
        const_iterator_reference operator+=(size_t size); 
        difference_type operator-(const_iterator_reference other) const; 
        const_iterator_reference operator-=(size_t size);
        const_iterator operator-(size_t size) const;

        // comparison operators
        
        bool operator==(const_iterator_reference other) const;
        bool operator!=(const_iterator_reference other) const;
        bool operator>(const_iterator_reference other) const;
        bool operator>=(const_iterator_reference other) const;
        bool operator<(const_iterator_reference other) const;
        bool operator<=(const_iterator_reference other) const;

        // subscript operator
        
        const_reference operator[](size_t size) const;

     private:
        const_pointer iter_;
    };

// ****************************************************************************
// Vector definitions
// ****************************************************************************

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
        std::generate(array_, array_ + size, [](){return 0;});
        size_ = size;
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
        array_ = tmp;
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    


    /*
     *  move ctor
     *  ---------
     *  All we need here is Swap(other); This is able to work only because
     *  we defaulted the data members to the proper value for move semantic 
     *  like so:
     *  
     *  Default Values:
     *   pointer array_ = nullptr;
     *   size_t size_ = 0; 
     *   size_t capacity_ = 0;
     *
     */

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

    /*  ***********************************************************************
     *  accessors
     *  ***********************************************************************
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
    

    /*
     *  operator [] const
     *  -----------------
     *  DUMB misunderstanding learned here. You cannot write a unit test that
     *  and have a try and catch block to 
     */
  
    template <typename T>                               
    typename Vector<T>::const_reference
    Vector<T>::operator[](size_t index) const {
        if (size_ <= index || index < 0) 
            throw std::out_of_range("Subscript index out of range.");
        
        return array_[index];
    }

    // front() const
    
    template <typename T>                               
    typename Vector<T>::const_reference 
    Vector<T>::front() const {
        return *array_;
    }

    // back() const
    
    template <typename T>
    typename Vector<T>::const_reference 
    Vector<T>::back() const {
        return array_[size_ - 1];
    }
    
    /*
     *  begin() const
     *  -----------
     *  Should be a const copy iterator return type. Typedef found in Vector
     */
    
    template <typename T>
    typename Vector<T>::const_iterator 
    Vector<T>::cBegin() const {
        return const_iterator(array_);
    }
    
    // is this needed considering the issue #001
    template <typename T>
    typename Vector<T>::const_iterator 
    Vector<T>::begin() const {
        return const_iterator(array_);
    }

    /*
     *  end() const
     *  -----------
     *  Should be a const copy iterator return type. Typedef found in Vector
     */

    template <typename T>
    typename Vector<T>::const_iterator 
    Vector<T>::cEnd() const {
        return const_iterator(array_ + size_);
    }

    template <typename T>
    typename Vector<T>::const_iterator 
    Vector<T>::end() const {
        return const_iterator(array_ + size_);
    }



    // print() const
    
    template <typename T>                               
    void 
    Vector<T>::print() const {
        std::for_each(array_, array_ + size_,[](value_type element) {
                std::cout << element << " ";
        });
    }

    /*  ***********************************************************************
     *  modifiers
     *  ***********************************************************************
     */

    // front()
    
    template <typename T>
    typename Vector<T>::reference 
    Vector<T>::front() {
        return array_[0];
    }

    // back()
   
    template <typename T>
    typename Vector<T>::reference 
    Vector<T>::back() {
        return array_[size_ - 1];
    }
    
    // operator[]
    
    template <typename T>
    typename Vector<T>::reference
    Vector<T>::operator[](size_t index) {
        if (size_ <= index || index < 0) 
            throw std::out_of_range("Subscript index out of range.");

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

    template <typename T>
    typename Vector<T>::iterator 
    Vector<T>::erase(typename Vector<T>::iterator pos) {
        // testing if position is within the array_
        if (pos < begin() || pos >= end())
            throw std::out_of_range("Call to erase() with Invalid position");

        auto dist = std::distance(array_, &(*pos));
        
        // steps each element back by one after pos.
        // I had to fix operator+ overload for this bug.
        for (iterator index = pos; index != end() - 1; ++index) 
            *index = std::move(*(index + 1));
        
        --size_;
        return begin() + dist;    
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
    typename Vector<T>::iterator
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
     *  
     *  Remember to not attempt to dereference the end iterator. Use arithmatic
     *  overloaded operator to decrement by one to dereference the last valid
     *  element in the array. 
     */
    
    template <typename T>
    typename Vector<T>::iterator
    Vector<T>::end() {
        return iterator(array_ + size_);
    }
    

    /*
     *  comparison operators
     *  --------------------
     */

    template <typename T>
    bool 
    Vector<T>::operator==(const Vector& other) const {
        if (other.size_ != size_) 
            return false;

        if (this == &other)
            return true;

        return std::equal(array_, array_ + size_, other.array_);
    }

    template <typename T>
    bool 
    Vector<T>::operator!=(const Vector& other) const {
        return !operator==(other);
    }

    template <typename T>
    bool 
    Vector<T>::operator>(const Vector& other) const {
        return other < *this;
    }

    template <typename T>
    bool 
    Vector<T>::operator>=(const Vector& other) const {
        return !operator<(other);
    }

    template <typename T>
    bool 
    Vector<T>::operator<(const Vector& other) const {
        return std::lexicographical_compare(array_, array_ + size_, 
                other.array_, other.array_ + other.size_);
    }

    template <typename T>
    bool 
    Vector<T>::operator<=(const Vector& other) const {
        return !operator>(other);
    }


     
    /*   **********************************************************************
     *   Vector private member functions -> helpers            
     *   **********************************************************************
     */

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

// ****************************************************************************
// iterator class definitions
// ****************************************************************************
    
    // 
    template <typename T>
    std::ostream& 
    operator<<(std::ostream& os, 
            typename Vector<T>::iterator::const_iterator_reference it) {
        os << *it;
        return os;
    }

    
    /*
     *  iterator constructors
     *  ---------------------
     */
    
    template <typename T>
    Vector<T>::iterator::iterator() : iter_(nullptr) {}
    
    template <typename T>
    Vector<T>::iterator::iterator(typename iterator::pointer ptr) : iter_(ptr)
    {}
    
    // return type must not be const. WHY? CHAINING?
    template <typename T>
    typename Vector<T>::iterator::iterator_reference
    Vector<T>::iterator::operator=(
           typename Vector<T>::iterator::const_iterator_reference other) {
        if (this != &other) 
            iter_ = other.iter_;
        
        return *this;
    }
    

    /*
     *  iterator reference operators
     *  -----------------------------
     */
    
    // operator*
    template <typename T>
    typename Vector<T>::iterator::reference
    Vector<T>::iterator::operator*() {
        return *iter_;
    }
        
    // const operator*
    template <typename T>
    typename Vector<T>::iterator::const_reference
    Vector<T>::iterator::operator*() const {
        return *iter_;
    }
    
    // operator ->
    template <typename T>
    typename Vector<T>::iterator::pointer
    Vector<T>::iterator::operator->() {
        return iter_;
    }

    // const operator ->
    template <typename T>
    typename Vector<T>::iterator::const_pointer
    Vector<T>::iterator::operator->() const {
        return iter_;
    }
    

    /*
     *  iterator increment and decrement operators
     *  ------------------------------------------
     */

    // ++operator
    template <typename T>
    typename Vector<T>::iterator::iterator_reference
    Vector<T>::iterator::operator++() {
        ++iter_;
        return *this;
    }

    // operator++
    template <typename T>
    typename Vector<T>::iterator::const_iterator
    Vector<T>::iterator::operator++(int) {
        iterator temp(this->iter_);
        operator++();
        return temp;
    }
    
    // --operator
    template <typename T>
    typename Vector<T>::iterator::iterator_reference
    Vector<T>::iterator::operator--() {
        --iter_;
        return *this;
    }
    
    // operator--
    template <typename T>
    typename Vector<T>::iterator::const_iterator
    Vector<T>::iterator::operator--(int) {
        iterator temp(this->iter_);
        operator--();
        return temp;
    }
    
    /*
     *  iterator pointer arithmatic operators 
     *  -------------------------------------
     */

    // operator+
    template <typename T>
    typename Vector<T>::iterator
    Vector<T>::iterator::operator+(size_t size) const {
        return iterator(iter_ + size);
    }

    // Dont forget to use the compound operator +=
    // You forgot the = and this was a hard bug to find.
    template <typename T>
    typename Vector<T>::iterator::iterator_reference
    Vector<T>::iterator::operator+=(size_t size) {
        iter_ += size;
        return *this;
    }

    // operator- 
    // for pointer arithmatic and std::difference algo

    // NOTE ITERATOR_TRAITS NOT DEFINED AND BREAKS DLIST, QUEUE SO WE WONT 
    // USE STD::DISTANCE for our Vector class until we fix dlist.
    template <typename T>
    typename Vector<T>::iterator::difference_type
    Vector<T>::iterator::operator-(const_iterator_reference other) const{
        return iter_ - other.iter_;
    }
    
    // operator-
    // Dont forget to use the compound operator -=
    // You forgot the = and this was a hard bug to find.
    template <typename T>
    typename Vector<T>::iterator::iterator_reference
    Vector<T>::iterator::operator-=(size_t size) {
        iter_ -= size;
        return *this;
    }

    template <typename T>
    typename Vector<T>::iterator
    Vector<T>::iterator::operator-(size_t size) const {
        return iterator(iter_ - size);
    }
 
    /*
     *  iterator comparison operators
     *  -----------------------------
     *  Need to work with algorithms. They are comparing addresses not The
     *  value of the pointer. In this case address of iter_ not value of 
     *  *iter_
     */

    template <typename T>
    bool
    Vector<T>::iterator::operator==(
            typename Vector<T>::iterator::const_iterator_reference other) const {
        return iter_ == other.iter_;
    }

    template <typename T>
    bool
    Vector<T>::iterator::operator!=(
            typename Vector<T>::iterator::const_iterator_reference other) const {
        return !operator==(other);
    }
 
    template <typename T>
    bool
    Vector<T>::iterator::operator>(
           typename Vector<T>::iterator::const_iterator_reference other) const {
        return iter_ > other.iter_;
    }

    template <typename T>
    bool
    Vector<T>::iterator::operator>=(
            typename Vector<T>::iterator::const_iterator_reference other) const {
        return !operator<(other);
    }

    template <typename T>
    bool
    Vector<T>::iterator::operator<(
            typename Vector<T>::iterator::const_iterator_reference other) const {
        return other > *this;
    }

    template <typename T>
    bool
    Vector<T>::iterator::operator<=(
            typename Vector<T>::iterator::const_iterator_reference other) const {
        return !operator>(other);
    }

    // subscript operator
    // DANGEROUS can end up out of bounds. 
    template <typename T>
    typename Vector<T>::iterator::reference 
    Vector<T>::iterator::operator[](size_t size) {
        return *(iter_ + size);
    }
    

// ****************************************************************************
// const iterator
// ****************************************************************************
    
    template <typename T>
    std::ostream& 
    operator<<(std::ostream& os, 
            typename Vector<T>::const_iterator::const_iterator_reference it) {
        os << *it;
        return os;
    }

    /*
     *  const_iterator constructors
     *  ---------------------------
     */
    
    // default ctor
    template <typename T>
    Vector<T>::const_iterator::const_iterator() : iter_(nullptr) {}
    
    // explicit ctor
    template <typename T>
    Vector<T>::const_iterator::const_iterator(
            typename Vector<T>::const_iterator::const_pointer ptr) : iter_(ptr) 
    {}
    
    // assignment
    template <typename T>
    typename Vector<T>::const_iterator::const_iterator_reference
    Vector<T>::const_iterator::operator=(
           typename Vector<T>::const_iterator::const_iterator_reference other) {
        if (this != &other) 
            iter_ = other.iter_;
        
        return *this;
    }
    
    /*
     *  const_iterator reference operators
     *  ----------------------------------
     */
            
    // const operator*
    template <typename T>
    typename Vector<T>::const_iterator::const_reference
    Vector<T>::const_iterator::operator*() const {
        return *iter_;
    }
    
    // const operator ->
    template <typename T>
    typename Vector<T>::const_iterator::const_pointer
    Vector<T>::const_iterator::operator->() const {
        return iter_;
    }
    
    /*
     *  const iterator increment and decrement operators
     *  ------------------------------------------------
     */

    // const ++operator
    template <typename T>
    typename Vector<T>::const_iterator::const_iterator_reference
    Vector<T>::const_iterator::operator++() {
        ++iter_;
        return *this;
    }

    // const operator++
    template <typename T>
    typename Vector<T>::const_iterator::const_iterator
    Vector<T>::const_iterator::operator++(int) {
        const_iterator temp(this->iter_);
        operator++();
        return temp;
    }
    
    // const --operator
    template <typename T>
    typename Vector<T>::const_iterator::const_iterator_reference
    Vector<T>::const_iterator::operator--() {
        --iter_;
        return *this;
    }
    
    // const operator--
    template <typename T>
    typename Vector<T>::const_iterator::const_iterator
    Vector<T>::const_iterator::operator--(int) {
        const_iterator temp(this->iter_);
        operator--();
        return temp;
    }
    
    /*
     *  const iterator pointer arithmatic operators 
     *  -------------------------------------------
     */

    // const operator+
    template <typename T>
    typename Vector<T>::const_iterator
    Vector<T>::const_iterator::operator+(size_t size) const {
        return const_iterator(iter_ + size);
    }
    
    // const operator +=
    template <typename T>
    typename Vector<T>::const_iterator::const_iterator_reference
    Vector<T>::const_iterator::operator+=(size_t size) {
        iter_ += size;
        return *this;
    }

    // const operator- 
    // for pointer arithmatic and std::difference algo

    // NOTE ITERATOR_TRAITS NOT DEFINED AND BREAKS DLIST, QUEUE SO WE WONT 
    // USE STD::DISTANCE for our Vector class until we fix dlist.
    template <typename T>
    typename Vector<T>::const_iterator::difference_type
    Vector<T>::const_iterator::operator-(const_iterator_reference other) const{
        return iter_ - other.iter_;
    }
    
    // const operator-
    // Dont forget to use the compound operator -=
    // You forgot the = and this was a hard bug to find.
    template <typename T>
    typename Vector<T>::const_iterator::const_iterator_reference
    Vector<T>::const_iterator::operator-=(size_t size) {
        iter_ -= size;
        return *this;
    }

    template <typename T>
    typename Vector<T>::const_iterator
    Vector<T>::const_iterator::operator-(size_t size) const {
        return const_iterator(iter_ - size);
    }
 
    /*
     *  const iterator comparison operators
     *  ------------------------------------
     *  Need to work with algorithms. They are comparing addresses not The
     *  value of the pointer. In this case address of iter_ not value of 
     *  *iter_
     */

    template <typename T>
    bool
    Vector<T>::const_iterator::operator==(
            typename Vector<T>::const_iterator::const_iterator_reference other) const {
        return iter_ == other.iter_;
    }

    template <typename T>
    bool
    Vector<T>::const_iterator::operator!=(
            typename Vector<T>::const_iterator::const_iterator_reference other) const {
        return !operator==(other);
    }
 
    template <typename T>
    bool
    Vector<T>::const_iterator::operator>(
           typename Vector<T>::const_iterator::const_iterator_reference other) const {
        return iter_ > other.iter_;
    }

    template <typename T>
    bool
    Vector<T>::const_iterator::operator>=(
            typename Vector<T>::const_iterator::const_iterator_reference other) const {
        return !operator<(other);
    }

    template <typename T>
    bool
    Vector<T>::const_iterator::operator<(
            typename Vector<T>::const_iterator::const_iterator_reference other) const {
        return other > *this;
    }

    template <typename T>
    bool
    Vector<T>::const_iterator::operator<=(
            typename Vector<T>::const_iterator::const_iterator_reference other) const {
        return !operator>(other);
    }

    // const subscript operator
    // DANGEROUS can end up out of bounds. 
    template <typename T>
    typename Vector<T>::const_iterator::const_reference 
    Vector<T>::const_iterator::operator[](size_t size) const {
        return *(iter_ + size);
    }

}}

#endif
