

/*
 *   Author:  Aaron Carroll
 *   Email:   arncarroll@gmail.com
 *   Date:    2022
 *   File:
 *
 *   Program output
 *   --------------
 *   - Contains all unitTests for Vector.h
 *   - Runs all tests for Vector.h at bottom of page inside int main() {}.
 *
 */

#include <algorithm>
#include <exception>
#include <iostream>
#include <utility>

#include "vector.h"
using namespace AaronCarroll;

#include "UnitTest++.h"
using namespace UnitTest;

#include "test_constants.h"
using namespace VectorTestConstants;

// Tests printed values of arrays.
#define PRINT_VALUES_ 0 
// Tests compiler error for attempting to assign a value to a const object.
#define TEST_CONST_COMPILE_TIME_ERRORS_ 0

// Vector ---------------------------------------------------------------------

TEST(DefaultConstructor) {
    Vector<int> myVectorInt;

    CHECK_EQUAL(myVectorInt.getCapacity(), 2);
    CHECK_EQUAL(myVectorInt.getSize(), 0);

    Vector<std::string> myVectorStr;

    CHECK_EQUAL(myVectorStr.getCapacity(), 2);
    CHECK_EQUAL(myVectorStr.getSize(), 0);
}

TEST(FillCtor) {
    
    Vector<double> myVec(SIZE);
    CHECK_EQUAL(myVec.getCapacity(), SIZE);
    CHECK_EQUAL(myVec.getSize(), SIZE);
    
    std::generate(myVec.begin(), myVec.end(), [](){return DOUBLEVALUE;});

    CHECK_EQUAL(std::all_of(myVec.begin(), myVec.end(), [](auto element) {
        return element == DOUBLEVALUE;
    }), 1);
}

TEST(FillValueCtor) {
    
    Vector<double> myVectorDouble(SIZE, DOUBLEVALUE);

    CHECK_EQUAL(myVectorDouble.getCapacity(), SIZE);
    CHECK_EQUAL(myVectorDouble.getSize(), SIZE);
    CHECK_EQUAL(myVectorDouble[1], DOUBLEVALUE);

    CHECK_EQUAL(std::all_of(myVectorDouble.begin(), myVectorDouble.end(), 
    [&](auto element) {
        return element == DOUBLEVALUE;
    }), 1);     
    
    // string test
    Vector<std::string> myVectorStr(SIZE, STRINGVALUE);

    CHECK_EQUAL(myVectorStr.getCapacity(), SIZE);
    CHECK_EQUAL(myVectorStr.getSize(), SIZE);

    CHECK_EQUAL(std::all_of(myVectorStr.begin(), myVectorStr.end(), 
    [&](std::string str) { 
            return str.compare(STRINGVALUE) == 0 ? 1 : 0;
    }), 1);
}

TEST(InitializerListCtor) {
    const Vector<int> myVecConst = {0,1,2,3,4,5,6,7,8};
    CHECK_EQUAL(myVecConst[2], 2);
}

TEST(RangeCtor) {
    Vector<int> myVec = {0,1,2,3,4,5,6,7,8,9,10};
    Vector<int>::iterator first = myVec.begin();
    Vector<int>::iterator last = myVec.end();
    Vector<int> rangeVec(first, last);

#if PRINT_VALUES_  
    rangeVec.print();
    printf(" -> Range constructor values 0-10 SUCCESSFUL\n");
#endif 

    CHECK(myVec == rangeVec);
}



TEST(CopyCtor) {
    Vector<int> myVec1(SIZE, INTVALUE);
    Vector<int> myVec2(myVec1);
    
    CHECK_EQUAL(myVec2.getSize(), SIZE);
    CHECK(std::all_of(myVec2.begin(), myVec2.end(), [&](auto element) {
        return element == INTVALUE;
    }));
}
TEST(MoveCtor) {
    Vector<int> myVec1(SIZE, INTVALUE);
    Vector<int> myVec2(std::move(myVec1));

    CHECK_EQUAL(std::all_of(myVec2.begin(), myVec2.end(), [&](auto element) {
        return element == INTVALUE;
    }), 1);
}

TEST(OperatorEqual) {
    Vector<int> myVec1(SIZE, INTVALUE);
    Vector<int> myVec2 = myVec1;

    CHECK_EQUAL(std::all_of(myVec2.begin(), myVec2.end(), [&](auto element) {
        return element == INTVALUE;
    }), 1);
    
    CHECK_EQUAL(std::all_of(myVec1.begin(), myVec1.end(), [&](auto element) {
        return element == INTVALUE;
    }), 1);
}

// valgrind ./STLPROJECT to check for leaks and proper destructor call.
TEST(Destructor) {
    Vector<int> myVec1(SIZE, INTVALUE);
    Vector<int> myVec2(myVec1);
    
    CHECK_EQUAL(myVec2.getSize(), SIZE); 
    CHECK(std::all_of(myVec2.begin(), myVec2.end(), [&](auto element) {
        return element == INTVALUE;
    }));
}

TEST(getSize) {
    Vector<std::string> myVec(SIZE);
    CHECK_EQUAL(myVec.getSize(), SIZE);
}

TEST(getCapacity) {
    Vector<std::string> myVec(SIZE);
    CHECK_EQUAL(myVec.getCapacity(), SIZE);
}

TEST(SubScriptConst) {
    const Vector<int> myVecConst = {0,1,2,3,4,5,6,7,8};
    
    // myVecConst[2] = 4; // This will throw an exception
  
    CHECK_EQUAL(myVecConst[2], 2);
}

TEST(FrontConst) {
    const Vector<int> myVec = {0,1,2,3,4,5};
    CHECK_EQUAL(myVec.front(), 0);

#if TEST_CONST_COMPILE_TIME_ERRORS_
    CHECK_EQUAL(myVec.front() = 5, 5);   // will SUCCESSFULLY FAIL
#endif
}

TEST(BackConst) {
    const Vector<int> myVec = {0,1,2,3,4,5};
    CHECK_EQUAL(myVec.back(), 5);

#if TEST_CONST_COMPILE_TIME_ERRORS_
    CHECK_EQUAL(myVec.back() = 3, 3);    // will SUCCESSFULLY FAIL
#endif
}

/*
 * Need to write the const iterator class for this to work correctly

TEST(cBegin) {
    Vector<int> myVec = {0,1,2,3,4};
    auto it = myVec.cBegin();
    CHECK_EQUAL(*it, 0);
}

// end should not be dereferenced --it to access valid element
TEST(cEnd) {
    Vector<int> myVec = {0,1,2,3,4};
    auto it = myVec.cEnd();
    CHECK_EQUAL(*(it - 1), 4); 
}
*/

#if PRINT_VALUES_ 
TEST(print) {
    Vector<int> myVec = {0,1,2,3,4,5};
    myVec.print();
    std::cout << "Print() SUCCESSFUL\n";
}
#endif

TEST(PopBack) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE);
    myVec.popBack();
    CHECK_EQUAL(myVec.getSize(), 1);
    myVec.popBack();
    myVec.popBack();
    CHECK_EQUAL(myVec.getSize(), 0);

    Vector<std::string> myVecStr;
    myVecStr.pushBack(STRINGVALUE);
    myVecStr.pushBack(STRINGVALUE);
    myVecStr.popBack();
    CHECK_EQUAL(myVecStr.getSize(), 1);
}

/* Need to implement function in vector.h
TEST(Erase) {

}
*/ 

TEST(SubScript) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE + 2);
    myVec.pushBack(INTVALUE + 3);
    CHECK(myVec[0] == INTVALUE && myVec[1] == INTVALUE + 2 && 
            myVec[2] == INTVALUE + 3);
}

TEST(Front) {
    Vector<int> myVec = {0,1,2,3,4,5};
    CHECK_EQUAL(myVec.front(), 0);
    CHECK_EQUAL(myVec.front() = 5, 5);
}

TEST(Back) {
    Vector<int> myVec = {0,1,2,3,4,5};
    CHECK_EQUAL(myVec.back(), 5);
    CHECK_EQUAL(myVec.back() = 3, 3);
}

TEST(BeginAndEnd) {
    Vector<int> myVec(SIZE, INTVALUE);
    Vector<int>::iterator first = myVec.begin();
    Vector<int>::iterator last = myVec.end();
    CHECK_EQUAL(last - first, SIZE);
}

TEST(VecOperatorEqual) {
    Vector<int> vec1 = {0,1,2,3};
    Vector<int> vec2 = {0,1,2,3};
    Vector<int> vec3 = {3,2,1,0};
    Vector<std::string> vecStr1 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr2 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr3 = {"people", "you are fabulous", "hello"};

    CHECK(vec1 == vec2);
    CHECK(vec1 == vec1);
    CHECK(!(vec1 == vec3));
    CHECK(vecStr1 == vecStr2);
    CHECK(!(vecStr2 == vecStr3));
}


TEST(VecOperatorNotEqual) {
 Vector<int> vec1 = {0,1,2,3};
    Vector<int> vec2 = {0,1,2,3};
    Vector<int> vec3 = {3,2,1,0};
    Vector<std::string> vecStr1 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr2 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr3 = {"people", "you are fabulous", "hello"};

    CHECK(!(vec1 != vec2));
    CHECK(vec1 != vec3);
    CHECK(!(vecStr1 != vecStr2));
    CHECK(vecStr2 != vecStr3);
}

TEST(VecOperatorGreaterThan) {
    Vector<int> vec1 = {0,1,2,3};
    Vector<int> vec2 = {0,1,2,3};
    Vector<int> vec3 = {3,2,1,0};
    Vector<std::string> vecStr1 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr2 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr3 = {"people", "you are fabulous", "hello"};

    CHECK(!(vec1 > vec2));
    CHECK(!(vec1 > vec3));
    CHECK(vec3 > vec1);

    CHECK(vecStr3 > vecStr2);
    CHECK(!(vecStr2 > vecStr3));
}


TEST(VecOperatorGreaterThanOrEqual) {
    Vector<int> vec1 = {0,1,2,3};
    Vector<int> vec2 = {0,1,2,3};
    Vector<int> vec3 = {3,2,1,0};
    Vector<std::string> vecStr1 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr2 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr3 = {"people", "you are fabulous", "hello"};

    CHECK(vec1 >= vec2);
    CHECK(!(vec1 >= vec3));
    CHECK(vec3 >= vec1);

    CHECK(vecStr3 >= vecStr2);
    CHECK(!(vecStr2 >= vecStr3));
    CHECK(vecStr1 >= vecStr2);
}

TEST(VecOperatorLessThan) {
    Vector<int> vec1 = {0,1,2,3};
    Vector<int> vec2 = {0,1,2,3};
    Vector<int> vec3 = {3,2,1,0};
    Vector<std::string> vecStr1 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr2 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr3 = {"people", "you are fabulous", "hello"};

    CHECK(!(vec1 < vec2));
    CHECK(vec1 < vec3);
    CHECK(!(vec3 < vec1));

    CHECK(!(vecStr3 < vecStr2));
    CHECK(vecStr2 < vecStr3);

}

TEST(VecOperatorLessThanOrEqual) {
    Vector<int> vec1 = {0,1,2,3};
    Vector<int> vec2 = {0,1,2,3};
    Vector<int> vec3 = {3,2,1,0};
    Vector<std::string> vecStr1 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr2 = {"hello", "people", "you are fabulous"};
    Vector<std::string> vecStr3 = {"people", "you are fabulous", "hello"};

    CHECK(vec1 <= vec2);
    CHECK(vec1 <= vec3);
    CHECK(!(vec3 <= vec1));

    CHECK(!(vecStr3 <= vecStr2));
    CHECK(vecStr2 <= vecStr3);
    CHECK(vecStr1 <= vecStr2);
}


// same as move b/c we know it calls swap. Kinda pointless
TEST(Swap) {
    Vector<int> myVec1(SIZE, INTVALUE);
    Vector<int> myVec2(std::move(myVec1));

    CHECK_EQUAL(std::all_of(myVec2.begin(), myVec2.end(), [&](auto element) {
        return element == INTVALUE;
    }), 1);
}

TEST(ReAllocPushBack) {

    // capacity formula = ReAlloc(capacity_ * 2 + 1)

    Vector<double> myVec;          // capacity = 2 size = 0
                            
    myVec.pushBack(DOUBLEVALUE);   // capacity = 2 size = 1
    myVec.pushBack(DOUBLEVALUE);   // capacity = 2 size = 2
    myVec.pushBack(DOUBLEVALUE);   // capacity = 5 size = 3
    myVec.pushBack(DOUBLEVALUE);   // capacity = 5 size = 4
    myVec.pushBack(DOUBLEVALUE);   // capacity = 5 size = 5
    myVec.pushBack(DOUBLEVALUE);   // capacity = 11 size = 6
    myVec.pushBack(DOUBLEVALUE);   // capacity = 11 size = 7
    myVec.pushBack(DOUBLEVALUE);   // capacity = 11 size = 8
    myVec.pushBack(DOUBLEVALUE);   // capacity = 11 size = 9
    myVec.pushBack(DOUBLEVALUE);   // capacity = 11 size = 10
    myVec.pushBack(DOUBLEVALUE);   // capacity = 11 size = 11
    myVec.pushBack(DOUBLEVALUE);   // capacity = 23 size = 12

    CHECK_EQUAL(myVec.getCapacity(), CAP_AFTER_11_PUSHBACKS);
    CHECK_EQUAL(myVec.getSize(), SIZE_AFTER_11_PUSHBACKS);

    CHECK_EQUAL(std::all_of(myVec.begin(), myVec.end(), [&](auto element) {
        return element == DOUBLEVALUE;
    }), 1);
}

// Vector Iterator tests ------------------------------------------------------

TEST(IteratorDefaultCtor) {
    Vector<int> myVec = {0,1,2,3};
    Vector<int>::iterator first;

    first = myVec.begin();
    
    CHECK_EQUAL(first[0], 0);
}


TEST(iteratorExplicitCtor) {
    Vector<int> myVec = {0,1,2,3};
    Vector<int>::iterator first = myVec.begin();
    CHECK_EQUAL(*first, *myVec.begin());
}

/*
TEST(IteratorDereferenceOperatorConst) {

}
TEST(IteratorArrowOperatorConst) {

}
TEST(IteratorDereferenceOperator) {

}
TEST(IteratorArrowOperator) {

}
TEST(IteratorPreIncrementOperator) {

}
TEST(IteratorPostIncrementOperator) {

}
TEST(IteratorPreDecrementOperator) {

}
TEST(IteratorPostDecrementOperator) {

}
TEST(IteratorPlusArithmaticOperator) {

}
TEST(IteratorDifferenceOperator) {

}

TEST(IteratorMinusArithmaticOperator) {

}
*/ 

TEST(IteratorOperatorEqual) {
    Vector<int> myVec = {0,1,2,3};
    Vector<int>::iterator first = myVec.begin();
    Vector<int>::iterator last = myVec.end();
    CHECK(!(first == last));
    CHECK(last == last);
    CHECK(first == first);
}

TEST(IteratorOperatorNotEqual) {
    Vector<int> myVec = {0,1,2,3};
    Vector<int>::iterator first = myVec.begin();
    Vector<int>::iterator last = myVec.end();
    CHECK(first != last);
    CHECK(!(last != last));
    CHECK(!(first != first));
}

TEST(IteratorOperatorGreaterThan) {
    Vector<int> myVec = {0,1,2,3};
    Vector<int>::iterator first = myVec.begin();
    Vector<int>::iterator last = myVec.end();
    CHECK(!(first > last));
    CHECK(last > first);
    CHECK(!(first > first));
}

TEST(IteratorOperatorGreaterThenOrEqual) {
    Vector<int> myVec = {0,1,2,3};
    Vector<int>::iterator first = myVec.begin();
    Vector<int>::iterator last = myVec.end();
    CHECK(!(first >= last));
    CHECK(first >= first);
    CHECK(last >= first);
}


TEST(IteratorOperatorLessThan) {
    Vector<int> myVec = {0,1,2,3};
    Vector<int>::iterator first = myVec.begin();
    Vector<int>::iterator last = myVec.end();
    CHECK(first < last);
    CHECK(!(last < first));
    CHECK(!(first < first));
}

TEST(IteratorOperatorLessThanOrEqual) {
    Vector<int> myVec = {0,1,2,3};
    Vector<int>::iterator first = myVec.begin();
    Vector<int>::iterator last = myVec.end();
    CHECK(first <= last);
    CHECK(first <= first);
    CHECK(!(last <= first));
}


TEST(IteratorSubscriptOperator) {
    Vector<int> myVec = {0,1,2,3};
    Vector<int>::iterator first = myVec.begin();
    Vector<int>::iterator last = myVec.end();
    CHECK_EQUAL(first[0], 0);
    CHECK_EQUAL(first[1], 1);
    CHECK_EQUAL(first[2], 2);
    CHECK_EQUAL(first[3], 3);

}

/*
TEST(test) {

}
*/


