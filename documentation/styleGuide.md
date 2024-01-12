# Style Guide

This document is meant to provide a rough outline for the code style in this project, mainly focusing on naming conventions, and things to avoid

## sources

Influence was drawn from the following sources:

- provided API code
- [Google c++ style guide](https://google.github.io/styleguide/cppguide.html)
- [CppCon 2014: Jeff Preshing "How Ubisoft Develops Games for Multicore - Before and After C++11"](https://www.youtube.com/watch?v=X1T3IQ4N-3g)
- [CppCon 2014: Nicolas Fleury "C++ in Huge AAA Games"](https://www.youtube.com/watch?v=qYN6eduU06s)

## formatting

use automatic formatting with `Visual Studio` selected as the formatting rules

## naming

### type names

class, struct, typedef, using, and enum should use `CapitalizedCamelCase`

### function names

should use `CapitalizedCamelCase`

### class member variables

should use camel case with a leading "m_", for example: `m_exampleVariable`

### common variables

any other variable should use `camelCase`

### constants

content variables should use `CAPITALIZED_SNAKE_CASE`

### enum members

should use `CAPITALIZED_SNAKE_CASE`

## comments

comments should only be used when the purpose of code is not apparent on its own, but in general, first try to refactor code to make its purpose obvious rather then relying on comments

### functions

almost every function declaration in a .h file should have a comment before it.

some important things to mention in this comment are

- inputs/outputs
- if an object uses references/pointers arguments beyond the scope of the function
- behavior of pointer argument when they are null
- state changes
- important performance implications

### files

each .cpp file should start with

```c++
//-----------------------------------------------------------------------------
// FileName.cpp
// Description of file
//-----------------------------------------------------------------------------
```

## header guards

each .h file should include a header guard with the following format

```c++
#ifndef PROJECT_PATH_FILE_H_
#define PROJECT_PATH_FILE_H_

...

#endif  // PROJECT_PATH_FILE_H_
```