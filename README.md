
# stl_implementation_practice

This repo is all about recreating the std::containers and learning along the way. Take a look around. All the container templates can be found inside the [include](https://github.com/PIesPnuema/stl_implementation_practice/tree/main/include) directory. 

#### Sections: [Test](#test) | [Project_File_Structure](#project_file_structure) | [TODO](#todo)

#### Test
Unit Tests are included for each container on the repo. Any contribution should make sure each new feature works and has a UnitTest before pushing the addtions to github. The following is instructions on how to run the UnitTests.

1. From root directory of repo; Create build directory and cd into that build directory:
```bash
mkdir build && cd build
```
2. inside the build directory configure the project for your computer via the following command:
```bash
cmake ..
```
3. building the project inside the "build" directory to obtain the executable. 
```bash
cmake --build . 
```
4. The executable is called STLPROJECT. To run the tests you just need to run the executable:
```bash
./STLPROJECT
```

### Project_File_Structure
```
.
├── CMakeLists.txt
├── README.md
├── TODO
│   └── check_list.md
├── UnitTest++
│   └── src
│       ├── UnitTest.h
│       └── ...
├── docs
│   ├── dlist_doc.md
│   └── vector_doc.md
├── include
│   ├── CMakeLists.txt
│   ├── README.md
│   ├── dlist.h
│   ├── test_constants.h
│   └── vector.h
├── src
│   └── main.cpp
└── tests
    ├── DListTests.cpp
    ├── TODO.md
    └── VectorTests.cpp
```

### TODO 
Visit the [checklist](https://github.com/PIesPnuema/stl_implementation_practice/blob/main/TODO/check_list.md) for a detailed list of TODO's.
- [ ] Finish Vector.h / add more tests
- [ ] Check Vector.h for exception safety and refine algorithms
- [ ] Add features to dlist.h
- [ ] Create Queue
- [ ] Create Deque
- [ ] Create Maps
- [ ] Create docs
