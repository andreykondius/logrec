# Logger of Records (LogRec)

Welcome to the Logger of Records ! 

## Introduction

**Logger of Records** is a cross platform logger (Linux and Windows).

## Why use the Logger of Records

Logger of Records enables you to get the simple and reliable solution for logger into your application
on such languages as C++ or C.

## Installation

The Logger of Records does not need to be installed.
 
## Embedding

Put the folder logrec into main folder your application.

## Configuring

Configure your CMakeLists.txt as like below:


	set(LOGREC_LIB logrec_lib)

	add_subdirectory(logrec)

	target_link_libraries(${you_app}
		PUBLIC
		${LOGREC_LIB}
	)

## Including

Include into you cpp file as like below.

	#include "logrec/putlog.hpp"

## Using

Use the Logger of Records into you code as like below:

	Putlog(LOG_MESSAGE,"Some text 1 ", "Some text 2 ","Some text 3 ","Some text 4 ","Some text 5 ");
	Putlog(LOG_MESSAGE,"Some text 1 ");
	Putlog(LOG_ERROR,"Some text 1 ");

## License

[MIT License](LICENSE)
