# Weighted Directed Graph

An example of directed weighted graph implementation.

## Before Build
!!!NOTE!!! I tried this in MacOS only so if you can find similar Linux commands also it  will works.
You need to following packages

```bash
$ brew install cmake
$ brew install lcov
```

In the project root directory you should get googletest by following command

```bash
$ git clone https://github.com/google/googletest
```

and then add "set(GOOGLETEST_VERSION 1.9.0)" to file googletest-master/googletest/CMakeLists.txt before GOOGLETEST_VERSION is used.

## Build and Run Unit Tests

From projects root directory
```bash
$ cd build
$ cmake ..
$ make
$ ./WDG-UnitTests
```

## Get Code Coverage Results

From projects root directory
```bash
$ cd build/CMakeFiles/WDG-UnitTests.dir
$ lcov -c --directory . --output-file main_coverage.info
$ genhtml main_coverage.info --output-directory out  
```
Then open the file build/CMakeFiles/WDG-UnitTests.dir/out/index.html to see code coverage results.