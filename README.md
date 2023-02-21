
# stl_implimitation_practice

Recreating the std::containers and learning along the way. 

#### Sections: [Test](#test) | [Project_File_Structure](#project_file_structure) | [TODO](#todo)

#### Test
I have included a empty build directory for a place to build the tests.

1. from root directory cd into the build directory:
```bash
cd build
```
2. inside the build directory configure the project for your computer via the following command:
```bash
cmake ..
```
3. build the project to obtain the executable. 
```bash
cmake --build . 
```
4. The executable is called STLPROJECT. To run the tests you just need to run the executable:
```bash
./STLPROJECT
```

If all configurations from UnitTest++ go well. All tests should pass.

### Project_File_Structure
```
root_repo/ stl_implimitation_practice
├── CMakeLists.txt
├── README.md
├── UnitTest++
│   └── src
│       ├── UnitTest++.h
├── build
├── include
│   ├── CMakeLists.txt
│   ├── README.md
│   ├── constants.h
│   ├── dlist.h
│   ├── dlist_README.md
│   └── vector.h
├── src
│   └── main.cpp
└── tests
    ├── DListTests.cpp
    ├── TODO.md
    └── VectorTests.cpp
```

### TODO
- [ ] Add UnitTest++ that has windows/ mac/ vscode configs
- [ ] Finish Vector.h / add more tests
- [ ] Check Vector.h for exception safety and refine algorithms
- [ ] Add features to dlist.h
- [ ] Create Queue
- [ ] Create Deque
- [ ] Create Maps
- [ ] Create docs
