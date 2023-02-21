
## double linked list

This project is my own implementation of a doubly linked list name dlist.

## what did I learn?

    - If a class is a friend to another class then class member functions that is the friend can access private members using the "." operator
      of a class passed as a parameter "other" but "other" needs to be passed by value.
            e.g access node from class we are friends with
    
                    // notice "iter" is passed by value
                    template <typename T>
                    typename dlist<T>::iterator
                    dlist<T>::insert(typename dlist<T>::iterator iter, const T &value)
                    {
                            // Insert new node
                            node *pNode = new node(value);
                            pNode->pNext_ = iter.pNode_;            // HERE WE ARE ACCESSING A PRIVATE MEMBER USING "." OPERATOR FROM ANOTHER CLASS THAT IS ITS FRIEND
                            pNode->pPrev_ = iter.pNode_->pPrev_;
                            iter.pNode_->pPrev_ = pNode;
                            if (pNode->pPrev_ == 0)
                                    head_node_ = pNode;
                            else
                                    pNode->pPrev_->pNext_ = pNode;
    
                            // Increment size
                            ++size_;
    
                            // Return iterator to new node
                            return iterator(pNode);
                    }
    
    - You can call member functions within its self without the need to write *this->
            e.g
    
                    template <typename T>
                    dlist<T> &
                    dlist<T>::operator=(const dlist<T> &other)
                    {
                            dlist<T> temp(other);   // HERE WE CALL THE COPY CONSTUCTOR INSIDE OPERATOR=
                            swap(temp);
                            return *this;
                    }
    
    - The magic was in the overloads in the iterator class
            - You must make these work first in order to use algorithms on them
                    - pay close attention to the use of the overloads ==, != inside iterator
                     and then the == overload in node struct
            - without these no algorithm would work because you could not compare properly or iterate through the list

