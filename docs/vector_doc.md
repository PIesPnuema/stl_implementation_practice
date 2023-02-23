
## Important reminders

### What should be returned by value?

- **Begin() / end()**
    - Const or non const these should always be returned by ***value*** 
    of, and not a ***reference*** or a ***pointer*** of. This is to allow the 
    iterator to change but not effect the originating value the container itself 
    may be pointing to.

### what should be returned by reference or pointer?

TODO: write best practices to answer this

### Other

- std::initializer allows you to take bracket { } style assignment. The behavior
is that of an object with an iterator so you can call init.size(), init.begin() and init.end().

- std::distance finds the distance between iterators regardless of container type.

- obvious but if you have a pointer to an arrray and it is the same size of another
array you can use the std::algorithms like std::copy to fill the array using the pointer.

- always think about the initial check that may need to be performed to prevent 
issues like derefferencing a nullptr and add a assert, or conditional statement
to verify safe operation.
    - ex `if (this != other)` or `if (array_)` // That one checks not null

- if statements that has a nullptr as the test condition like so `if (array_)`
will evaluate to false and not create undefined behavior its self. No idea 
what checking it is doing behind the scene. you could be more explicit by writting
`if (array_ != nullptr)` but it is not necessary.



