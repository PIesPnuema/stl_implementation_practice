
/*****************************************************************************
 * * Author:  Aaron Carroll, U09258362 
 * * Email:   arncarroll@gmail.com
 * * For:     C/C++ Programming IV
 * * Date:    Nov 9, 2022
 * * File:	  dlsit.h
 * * OS:      Linux, POP OS
 * * Editor:  NeoVim
 * *
 * * Program output:
 *
 *				- dlist is a doubly link list.
 *
 *				- dlist contains various c++ conventions to follow
 *					- move semantics (described below)
 *					- Iterator overloads with <bidirectional_iterator_tag>
 *					  attibutes
 *					- return "value initialization" technique used in insert
 *					  and erase 
 *					   e.g:
 *
 *					   return iterator(pNode);
 *
 *					- operator==() in the node. Was necessary for proper use of 
 *					  iteration operator==() in turn necessary for all other 
 *					  comparison operators 
 *
 *
 *				**** MOVE SEMANTICS ****
 *				------------------------
 *				Inside dlist copy constructor and assignment operator we use a 
 *				helper function "Swap()". Swap replaces the current value of 
 *				this with the new temp value created from the other.dlist.
 *				because there is a temp dlist created and then swapped the 
 *				destruction of the old "this" value happens once the assignment
 *				or copy constructors are finished and temp goes out of scope.
 *				There was no need to call any delete functions and then assign
 *				"this" to the new value. It was all handled by our already 
 *				created destructor. This technique has a special name 
 *				MOVE SEMANTICS. 
 *
 * **************************************************************************/


#ifndef AARONCARROLL_DLIST_H
#define AARONCARROLL_DLIST_H

#include <algorithm>
#include <cassert>
#include <iterator>

#include <iostream>

namespace AaronCarroll { namespace Project2
{
	/*
	 * dlist class:
	 * dlist class is a double linked list. With a head and a tail.
	 * destruction is handled by the erase() function for explicit destruction
	 * and the destructor ~dlist() for implicit deconstruction.
	 * ************************************************************************
	 */

	template <typename T>
	class dlist
	{
	 public:
		
		// Types
		class iterator;
		typedef size_t size_type;
		typedef T value_type;
		typedef const T const_reference;

		//constructors
		dlist();					// Default 
		dlist(const dlist &other);	// Copy 
		
		// constructs from only a curtain range 
		template <typename InputIterator> 
		dlist(InputIterator first, InputIterator last);
		
		// Destructor
		~dlist();

		// Copy assginment operator
		dlist &operator=(const dlist &other);

		// empty() & size()
		bool empty() const;
		size_type size() const;

		// front() & back()
		T &front();
		const T &front() const;
		T &back();
		const T &back() const;

		// Modifiers
		void push_front(const T &value);
		void pop_front();
		void push_back(const T &value);
		void pop_back();
		iterator insert(iterator iter, const T &value);
		iterator erase(iterator iter);

		// Comparison
		bool operator==(const dlist &other) const;
		bool operator!=(const dlist &other) const;
		bool operator<(const dlist &other) const;
		bool operator<=(const dlist &other) const;
		bool operator>(const dlist &other) const;
		bool operator>=(const dlist &other) const;

		// Iterator
		iterator begin();
		const iterator begin() const;
		iterator end();
		const iterator end() const;
		
		void getNode()
	    {
			std::cout << head_node_ << "  " << &*head_node_;
	    }
	 private:
		
		struct node
	    {
	      explicit node(const T &value) : value_(value), pNext_(0), pPrev_(0) {}

	      bool operator==(const node &other)
	      {
				return value_ == other.value_
					&& pNext_ == other.pNext_
					&& pPrev_ == other.pPrev_;
	      }

	      T value_;
	      node *pNext_;
	      node *pPrev_;
		};

		void initialize() throw();
		void swap(dlist &) throw();

		node *head_node_;	// type dlist<T>::node_* everywhere else
		node *tail_node_;

		size_type size_;
        
	};
	
	/*
	 * class iterator:
	 * iterator is a compostion of dlist. when dlist goes out of scope iterator
	 * dies. 
	 * ************************************************************************
	 */
	
	template <typename T>
	class dlist<T>::iterator : 
		public std::iterator<std::bidirectional_iterator_tag, T>
	{	

		friend class dlist<T>;

	 public:

		// Types
		typedef const T const_reference;

		// Constructors
		iterator();
		explicit iterator(typename dlist<T>::node *pNode);

		// Comparison
		bool operator==(const iterator &other) const;
		bool operator!=(const iterator &other) const;

		// Reference operators
		T &operator*();
		const T &operator*() const;

		// access operators
		T *operator->();
		const T *operator->() const;
		
		// increment and decrement operators  
		iterator &operator++();
		const iterator operator++(int);
		iterator &operator--();
		const iterator operator--(int);

	 private:
		typename dlist<T>::node *pNode_;
	};


	/**************************************************************************
			
		dlist Implimintation
		--------------------	
		anywhere dlist<T>:: is used you do not need to add dlist<T>:: to 
		initialize either an iterator or a node. 

	**************************************************************************/
	
		template <typename T>
		void 
		dlist<T>::initialize() throw()
		{
			head_node_ = tail_node_ = new dlist<T>::node(T());
			size_ = 0;
		}

		/* 
			Default constructor
			-------------------
		*/
		
		template <typename T>
		dlist<T>::dlist() : size_(0)
		{
			initialize();
		}

		/* 
			copy constructor
			----------------
			copy constructor calls range constructor. Uses full range of 
			the "other" dlist<T> to be copied

			can be optimized by not deleting all lists if some lists exist 
			already. iterate through both list locations equally and only 
			change the dlist<T>::node value_. If the size_ of this is less then 
			the size_ of other we will have to push_back() any additional list
			nodes. If list is longer we will have to pop_back() the remaineder.
		*/
		
		template <typename T>
		dlist<T>::dlist(const dlist<T> &other)
		{	
			// deletion of *this happens after swap. Temp will == *this
			// and be destroyed once out of scope.

			initialize();	
			dlist<T> temp(other.begin(), other.end());	// can throw
			swap(temp);
		}

		/* 
			range constructor
			-----------------
		*/	
		
		template <typename T>
		template <typename InputIterator> 
		dlist<T>::dlist(InputIterator first, InputIterator last)
		{	
			initialize();
			while(first != last)
				push_back(*first++);
		}
		

		/* 
			Destructor
			----------
		*/	

		template <typename T>
		dlist<T>::~dlist()
		{
			node *pNext;
			while (head_node_ != 0)
			{
				pNext = head_node_->pNext_;
				delete head_node_;
				head_node_ = pNext;
			}
		}


		/* 
			dlist operator=
			---------------
			**** MOVE SEMANTICS ****
			------------------------
			creates a temp by calling the copy constructor which calls the 
			range constructor. This is then swapped. destruction of old "this"
			values happen after end of function scope because the old value 
			gets assigned to temp. 
		*/	

		template <typename T>
		dlist<T> &
		dlist<T>::operator=(const dlist<T> &other)
		{
			dlist<T> temp(other);
			swap(temp);
			return *this;
		}


		/* 
			dlist empty()
			-------------
		*/	

		template <typename T>
		bool 
		dlist<T>::empty() const
		{
			return size_ == 0;
		}
	

		/* 
			dlist size()
			------------
		*/	
		
		template <typename T>
		typename dlist<T>::size_type 
		dlist<T>::size() const
		{	
			return size_;
		}
		

		/* 
			dlist front()
			-------------
			l-value

			if no assert the user could be accessing parts of memory we dont 
			want them accessing.
		*/	

		template <typename T>
		T &
		dlist<T>::front()
		{
			assert(size() > 0);

			return *begin();
		}

		/* 
			dlist front()
			-------------
			r-value

			if no assert the user could be accessing parts of memory we dont 
			want them accessing.

		*/	

		template <typename T>
		const T &
		dlist<T>::front() const
		{
			assert(size() > 0);

			return *begin();
		}


		/* 
			dlist back()
			------------
			if no assert the user could be accessing parts of memory we dont 
			want them accessing.
		*/	
		
		template <typename T>
		T & 
		dlist<T>::back()
		{
			assert(size() > 0);
			
			return *(--end());
		}


		/* 
			dlist const back()
			------------------
		*/	

		template <typename T>
		const T &
		dlist<T>::back() const
		{
			assert(size() > 0);
			return *(--end());
		}


		/* 
			dlist push_front()
			------------------
			NULL <-> newNode <-> old head_pNode_
		*/	
		
		template <typename T>
		void 
		dlist<T>::push_front(const T &value)
		{
			insert(begin(), value);	
		}


		/* 
			dlist pop_front()
			-----------------
		*/	
		
		template <typename T>
		void 
		dlist<T>::pop_front()
		{
			erase(begin());			
		}


		/* 
			dlist push_back()
			-----------------
			because insert() inserts to the back of the passed iterator we
			do not need to decrement the end(). 

			tail_Node_->pPrev_ <-> newNode <-> end()(aka tail_Node_)
		*/	

		template <typename T>
		void 
		dlist<T>::push_back(const T &value)
		{
			 insert(end(), value);
		}
		

		/* 
			dlist pop_back()
			----------------
			end() returns a iterator to the tail_pNode_. Using "--" allows 
			access to the iterator.pPrev_ value which is our actual last node.
			This iterator is then sent to erase.

		*/	

		template <typename T>
		void 
		dlist<T>::pop_back()
		{
			erase(--end());
		}


		/* 
			dlist insert()
			--------------
			inserts node before dlist<T>::iterator "iter"
			
			note we are able to access the iterator private member pNode_
			using the "." operator.
		*/	
		
		template <typename T>
		typename dlist<T>::iterator 
		dlist<T>::insert(typename dlist<T>::iterator iter, const T &value)
		{
			// Insert new node
			node *pNode = new node(value);
			pNode->pNext_ = iter.pNode_;
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


		/* 
			dlist erase()
			-------------
			returns iterator with location being erased node pNext_.
		*/	

		template <typename T>
		typename dlist<T>::iterator 
		dlist<T>::erase(typename dlist<T>::iterator iter)
		{
			assert (!empty());
			
			// Get pointers to nodes to erase and return
			node *pErase = iter.pNode_;
			node *pReturn = pErase->pNext_;

			// Disconnect node
			pErase->pNext_->pPrev_ = pErase->pPrev_;
			if (pErase->pPrev_ == 0)
				head_node_ = pErase->pNext_;
			else
				pErase->pPrev_->pNext_ = pErase->pNext_;

			// Decrement size
			--size_;

			// Erase and return
			delete pErase;
			return iterator(pReturn);	// returned by value
		}
	
		/* 
			dlist operator==
			----------------
			uses equal() algorithm Compares the elements in the range 
			[first1,last1) with those in the range beginning at first2, and 
			returns true if all of the elements in both ranges match.

		*/	
		template <typename T>
		bool 
		dlist<T>::operator==(const dlist<T> &other) const
		{
			return size_ == other.size_ && equal(begin(), end(), other.begin());
		}

		/* 
			dlist operator!=
			----------------
		*/	
		template <typename T>
		bool 
		dlist<T>::operator!=(const dlist<T> &other) const
		{
			return !operator==(other);
		}

		/* 
			dlist operator<
			---------------
			standard library algorithm. Lexicographical less-than comparison
			Returns true if the range [first1,last1) compares 
			lexicographically less than the range [first2,last2).			
		*/	
		template <typename T>
		bool 
		dlist<T>::operator<(const dlist<T> &other) const
		{	
			return lexicographical_compare(begin(), end(), other.begin(), 
					other.end());
		}

		/* 
			dlist operator<=
			----------------
		*/	
		template <typename T>
		bool 
		dlist<T>::operator<=(const dlist<T> &other) const
		{
			return operator<(other) || operator==(other);
		}

		/* 
			dlist operator>
			---------------
		*/	
		template <typename T>
		bool 
		dlist<T>::operator>(const dlist<T> &other) const
		{
			return !operator<(other) && !operator==(other);
		}


		/* 
			dlist operator>=
			----------------
		*/	
		template <typename T>
		bool 
		dlist<T>::operator>=(const dlist<T> &other) const
		{
			return !operator<(other);
		}

		
		/* 
			dlist begin()
			-------------
			TODO return as iterator(head_node_) not iter.
		*/	

		template <typename T>
		typename dlist<T>::iterator 
		dlist<T>::begin()
		{
			return iterator(head_node_);
		}


		/* 
			dlist const begin()
			-------------------
			TODO same as above
		*/	

		template <typename T>
		const typename dlist<T>::iterator 
		dlist<T>::begin() const
		{
			return iterator(head_node_);
		}


		/* 
			dlist end()
			-----------
		*/	

		template <typename T>
		typename dlist<T>::iterator 
		dlist<T>::end()
		{
			return iterator(tail_node_);
		}


		/* 
			dlist const end()
			-----------------
		*/	

		template <typename T>
		const typename dlist<T>::iterator 
		dlist<T>::end() const
		{
			return iterator(tail_node_);
		}


		/**********************************************************************
			
			dlist helper functions
			----------------------
		 
		 *********************************************************************/
		/*
			swap
			----
			uses algorithm swap. meant to be used each iteration of a range
			while(true) ==> swap
		*/
		template <typename T>
		void 
		dlist<T>::swap(dlist<T> &other) throw()
		{
			std::swap(head_node_, other.head_node_);
			std::swap(tail_node_, other.tail_node_);
			std::swap(size_, other.size_);
		}

	/**************************************************************************
			
		dlist<T>::iterator Implimintation		
		---------------------------------

	**************************************************************************/
	
		/* 
			iterator default constructor
			----------------------------
		*/	
		template <typename T>
		dlist<T>::iterator::iterator() : pNode_(0) {}

		/* 
			iterator explicit constructor
			-----------------------------
		*/	
		template <typename T>
		dlist<T>::iterator::iterator(typename dlist<T>::node *pNode)
				: pNode_(pNode) 
		{}
		
		/* 
			iterator operator==
			-------------------
		*/	
		template <typename T>
		bool 
		dlist<T>::iterator::operator==(const typename dlist<T>::iterator 
				&other) const
		{
			return pNode_ == other.pNode_;	// no need for parentheses
		}
		
		/* 
			iterator operator!=
			-------------------
		*/	
		template <typename T>
		bool 
		dlist<T>::iterator::operator!=(const typename dlist<T>::iterator 
				&other) const
		{
			return !operator==(other);
		}
		
		/* 
			iterator operator*
			------------------
			l-value
		*/	
		template <typename T>
		T &
		dlist<T>::iterator::operator*()
		{
			return pNode_->value_;
		}
		
		/* 
			iterator const operator*
			------------------------
			r-value (returns addressed stored in 
		*/	
		template <typename T>
		const T &
		dlist<T>::iterator::operator*() const
		{
			return pNode_->value_;
		}
		
		/* 
			iterator operator->
			-------------------
			l-value (pNode_->someMember)
		*/	
		template <typename T>
		T *
		dlist<T>::iterator::operator->()
		{
			return &pNode_->value_;
		}
		
		/* 
			iterator const operator->
			-------------------------
			r-value (pNode_->someMember) 
		*/	
		template <typename T>
		const T *
		dlist<T>::iterator::operator->() const
		{
			return &pNode_->value_;
		}
			
		/* 
			iterator operator++
			-------------------
			pre increment
		*/	 
		template <typename T>
		typename dlist<T>::iterator &
		dlist<T>::iterator::operator++()
		{		
			pNode_ = pNode_->pNext_;
			return *this;	
		}
		
		/* 
			iterator operator++
			-------------------
			post increment
		*/	
		template <typename T>
		const typename dlist<T>::iterator		
		dlist<T>::iterator::operator++(int)
		{	
			iterator temp(*this);
			operator++();
			return temp;
		}
		
		/* 
			iterator operator--
			-------------------
			pre decrement
		*/	
		template <typename T>
		typename dlist<T>::iterator &
		dlist<T>::iterator::operator--()
		{
			pNode_ = pNode_->pPrev_;
			return *this;
		}
			
		/* 
			iterator operator--
			-------------------
			post decrement
		*/	
		template <typename T>
		const typename dlist<T>::iterator		
		dlist<T>::iterator::operator--(int)
		{
			iterator temp(*this);
			operator--();	
			return temp;
		}

}}

#endif

