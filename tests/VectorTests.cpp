

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

#include <iostream>

#include "vector.h"
using namespace AaronCarroll;

#include "UnitTest++.h"
using namespace UnitTest;

#include "test_constants.h"
using namespace VectorTestConstants;

TEST(Test1DefaultConstructor) {

    Vector<int> myVectorInt;
    CHECK_EQUAL(myVectorInt.getCapacity(), 2);
    CHECK_EQUAL(myVectorInt.getSize(), 0);

    Vector<std::string> myVectorStr;
    CHECK_EQUAL(myVectorStr.getCapacity(), 2);
    CHECK_EQUAL(myVectorStr.getSize(), 0);
}

TEST(test2allocateNSizeEmptyVector) {
    
    Vector<double> myVectorDouble(SIZE);
    CHECK_EQUAL(myVectorDouble.getCapacity(), SIZE);
    CHECK_EQUAL(myVectorDouble.getSize(), 0);
    
    //std::cout << "test2 double. Expected value = \" \": ";
    //myVectorDouble.print();
    //std::cout << "\n";
}

TEST(test3FillCtor) {
    
    Vector<double> myVectorDouble(SIZE, DOUBLEVALUE);
    CHECK_EQUAL(myVectorDouble.getCapacity(), SIZE);
    CHECK_EQUAL(myVectorDouble.getSize(), SIZE);
    CHECK_EQUAL(myVectorDouble[1], DOUBLEVALUE);
    CHECK_EQUAL(myVectorDouble[SIZE -1], DOUBLEVALUE);
    
    Vector<std::string> myVectorStr(SIZE, STRINGVALUE);
    CHECK_EQUAL(myVectorStr.getCapacity(), SIZE);
    CHECK_EQUAL(myVectorStr.getSize(), SIZE);
    CHECK(myVectorStr[SIZE-1].compare(STRINGVALUE) == 0);
}

TEST(testPushBack) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    CHECK_EQUAL(myVec[0], INTVALUE);
}

TEST(testReAlloc) {

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
}

TEST(testPopBack) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE);
    myVec.popBack();
    CHECK_EQUAL(myVec.getSize(), 1);

    Vector<std::string> myVecStr;
    myVecStr.pushBack(STRINGVALUE);
    myVecStr.pushBack(STRINGVALUE);
    myVecStr.popBack();
    CHECK_EQUAL(myVecStr.getSize(), 1);
}

TEST(testFront) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE + 2);
    myVec.pushBack(INTVALUE + 3);
    CHECK_EQUAL(myVec.front(), INTVALUE);
    CHECK_EQUAL(myVec.front() = INTVALUE + 5, INTVALUE + 5);
}

TEST(testBack) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE + 2);
    myVec.pushBack(INTVALUE + 3);
    CHECK_EQUAL(myVec.back(), INTVALUE + 3);
    CHECK_EQUAL(myVec.back() = INTVALUE, INTVALUE);
}
TEST(testSubScript) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE + 2);
    myVec.pushBack(INTVALUE + 3);
    CHECK(myVec[0] == INTVALUE && myVec[1] == INTVALUE + 2 && 
            myVec[2] == INTVALUE + 3);
    
    // check const subscript.
    const Vector<int> myVecConst = {0,1,2,3,4,5,6,7,8};
    CHECK_EQUAL(myVecConst[2], 2);
}
/*

TEST(testIteratorDefaultCtor) {
    
}

TEST(testIteratorExplicitCtor) {

}
TEST(testIteratorMoveCtor) {

}

TEST(testBegin) {

}


TEST(testEnd) {

}


TEST(testConstBegin) {

}



TEST(testConstEnd) {

}
TEST(test) {

}
TEST(test) {

}
TEST(test) {

}
TEST(test) {

}
TEST(test) {

}
TEST(test) {

}

 

*/


