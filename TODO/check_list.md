# Check List    

Sections: [Vector](#vector) | [dlist](#dlist) | [Queue](#queue)

----

## Vector
[Vector<T>](https://github.com/PIesPnuema/stl_implemetation_practice/blob/main/TODO/check_list.md#vector-1) | [Vector<T> iterator](https://github.com/PIesPnuema/stl_implemetation_practice/blob/main/TODO/check_list.md#vector-iterator) | [Vector<T> const_iterator](https://github.com/PIesPnuema/stl_implemetation_practice/blob/main/TODO/check_list.md#vector-const_iterator)

Check list is based upon interface for vector.h
  
### Vector<T>
- [ ] Write TEST_SUITS for test sections of the vector class 
- [ ] Vector<T> Finished
  
| Defined Member Functions | Written Unit Tests |
| --- | --- |
| [ x ] defaultCtor() | [ x ] TEST(DefaultConstructor) |
| [ x ] fillValueCtor() | [ x ] TEST(FillValueCtor) |
| [ x ] fillCtor() | [ x ] TEST(FillCtor) |
| [ x ] initializerCtor() | [ x ] TEST(InitializerListCtor) |
| [ x ] rangeCtor() | [ x ] TEST(RangeCtor) |
| [ x ] copyCtor() | [ x ] TEST(CopyCtor) |
| [ x ] moveCtor() | [ x ] TEST(MoveCtor) |
| [ x ] operator=() | [ x ] TEST(OperatorEqual) |
| [ x ] ~destructor() | [ x ] TEST(Destructor) |
| [ x ] getSize() | [ x ] TEST(getSize) |
| [ x ] getCapacity() | [ x ] TEST(getCapacity) |
| [ x ] operator[]()const | [ x ] TEST(SubScriptConst) |
| [ x ] front() | [ x ] TEST(FrontConst) |
| [ x ] back() | [ x ] TEST(BackConst) |
| [ x ]cBegin() | [  ] TEST(cBegin) |
| [ x ] cEnd() | [  ] TEST(cEnd) |
| [ x ] print() | [ x ] TEST(print) |
| [ x ] pushBack() | [ x ] TEST(ReAllocPushBack) |
| [ x ] popBack() | [ x ] TEST(PopBack) |
| [ x ] erase() | [ x ] TEST(Erase) |
| [ x ] operator[]() | [ x ] TEST(SubScript) |
| [ x ] front() | [ x ] TEST(Front) |
| [ x ] back() | [ x ] TEST(Back) |
| [ x ] begin() | [ x ] TEST(BeginAndEnd) |
| [ x ] end() | [ x ] TEST(BeginAndEnd) |
| [ x ] operator==() | [ x ] TEST(VeccOperatorEqual) |
| [ x ] operator!=() | [ x ] TEST(VecOperatorNotEqual) |
| [ x ] operator>() | [ x ] TEST(VecOperatorGreaterThan) |
| [ x ] operator>=() | [ x ] TEST(VecOperatorGreaterThanOrEqual) |
| [ x ] operator<() | [ x ] TEST(VecOperatorLessThan) |
| [ x ] operator<=() | [ x ] TEST(VecOperatorLessThanOrEqual) |
| [ x ] Swap() | [ x ] TEST(Swap) |
| [ x ] ReAlloc() | [ x ] TEST(ReAlloc) |

### Vector<T> iterator
 
- [ ] Vector<T>::iterator

| Defined Member Functions | Written Unit Tests |
| --- | --- |
| [ x ] defaultCtor() | [ x ] TEST(IteratorDefaultCtor) |
| [ x ] explicitCtor() | [ x ] TEST(iteratorExplicitCtor) |
| [ x ] operator=() | [ x ] TEST(iteratorOperatorEqual) |
| [ x ] ~destructor() | [  ] TEST() |
| [ x ] operator*() const | [  ] TEST(IteratorDereferenceOperatorConst) |
| [ x ] operator->() const | [  ] TEST(IteratorArrowOperatorConst) |
| [ x ] operator*() | [  ] TEST(IteratorDereferenceOperator) |
| [ x ] operator->() | [  ] TEST(IteratorArrowOperator) |
| [ x ] operator++() pre | [  ] TEST(IteratorPreIncrementOperator) |
| [ x ] operator++(int) post | [  ] TEST(IteratorPostIncrementOperator) |
| [ x ] operator--() pre | [  ] TEST(IteratorPreDecrementOperator) |
| [ x ] operator--(int) post | [  ] TEST(IteratorPostDecrementOperator) |
| [ x ] operator+=() | [  ] TEST(IteratorPlusArithmaticOperator) |
| [ x ] operator+() | [  ] TEST(IteratorPlusArithmaticOperator) |
| [ x ] operator-(other) | [  ] TEST(IteratorDifferenceOperator) |
| [ x ] operator-=() | [  ] TEST(IteratorMinusArithmaticOperator) |
| [ x ] operator-() | [  ] TEST(IteratorMinusArithmaticOperator) |
| [ x ] operator==() | [ x ] TEST(IteratorOperatorEqual) |
| [ x ] operator!=() | [ x ] TEST(IteratorOperatorNotEqual) |
| [ x ] operator>() | [ x ] TEST(IteratorOperatorGreaterThan) |
| [ x ] operator>=() | [ x ] TEST(IteratorOperatorGreaterThenOrEqual) |
| [ x ] operator<() | [ x ] TEST(IteratorOperatorLessThan) |
| [ x ] operator<=() | [ x ] TEST(IteratorOperatorLessThanOrEqual) |
| [ x ] operator[]() | [ x ] TEST(IteratorSubscriptOperator) |

### Vector<T> const_iterator 
 TODO: To become truly const correct I need to make a whole seperate const_iterator class
  
- [ ] Vector<T>::const_iterator finished

| Defined Member Functions | Written Unit Tests |
| --- | --- |
| [  ] defaultCtor() | [  ] TEST(IteratorDefaultCtor) |
| [  ] explicitCtor() | [  ] TEST(iteratorExplicitCtor) |
| [  ] operator=() | [  ] TEST(iteratorOperatorEqual) |
| [  ] ~destructor() | [  ] TEST() |
| [  ] operator*() const | [  ] TEST(IteratorDereferenceOperatorConst) |
| [  ] operator->() const | [  ] TEST(IteratorArrowOperatorConst) |
| [  ] operator*() | [  ] TEST(IteratorDereferenceOperator) |
| [  ] operator->() | [  ] TEST(IteratorArrowOperator) |
| [  ] operator++() pre | [  ] TEST(IteratorPreIncrementOperator) |
| [  ] operator++(int) post | [  ] TEST(IteratorPostIncrementOperator) |
| [  ] operator--() pre | [  ] TEST(IteratorPreDecrementOperator) |
| [  ] operator--(int) post | [  ] TEST(IteratorPostDecrementOperator) |
| [  ] operator+=() | [  ] TEST(IteratorPlusArithmaticOperator) |
| [  ] operator+() | [  ] TEST(IteratorPlusArithmaticOperator) |
| [  ] operator-(other) | [  ] TEST(IteratorDifferenceOperator) |
| [  ] operator-=() | [  ] TEST(IteratorMinusArithmaticOperator) |
| [  ] operator-() | [  ] TEST(IteratorMinusArithmaticOperator) |
| [  ] operator==() | [  ] TEST(IteratorOperatorEqual) |
| [  ] operator!=() | [  ] TEST(IteratorOperatorNotEqual) |
| [  ] operator>() | [  ] TEST(IteratorOperatorGreaterThan) |
| [  ] operator>=() | [  ] TEST(IteratorOperatorGreaterThenOrEqual) |
| [  ] operator<() | [  ] TEST(IteratorOperatorLessThan) |
| [  ] operator<=() | [  ] TEST(IteratorOperatorLessThanOrEqual) |
| [  ] operator[]() | [  ] TEST(IteratorSubscriptOperator) |

----

## dlist

| Defined Member Functions | Written Unit Tests |
| --- | --- |
| [  ] function_name() | [  ] TEST() |
| [  ] function_name() | [  ] TEST() |
| [  ] function_name() | [  ] TEST() |
| [  ] function_name() | [  ] TEST() |
| [  ] function_name() | [  ] TEST() |

----
  
## Queue

| Defined Member Functions | Written Unit Tests |
| --- | --- |
| [  ] function_name() | [  ] TEST() |
| [  ] function_name() | [  ] TEST() |
| [  ] function_name() | [  ] TEST() |
| [  ] function_name() | [  ] TEST() |
| [  ] function_name() | [  ] TEST() |

