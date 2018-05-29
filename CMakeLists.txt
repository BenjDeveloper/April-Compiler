cmake_minimum_required(VERSION 3.10)

project(april)

message(STATUS "==================")
message(STATUS "CONFIGURING April")
message(STATUS "==================")

macro(replace_flags flag newflag)
    FOREACH(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
        IF(${flag_var} MATCHES ${flag})
            STRING(REGEX REPLACE "${flag}" "${newflag}" ${flag_var} "${${flag_var}}")
        ENDIF()
    ENDFOREACH(flag_var)
endmacro()

# Setup the make environment. #
################################

SET(CMAKE_BUILD_TYPE Debug CACHE STRING "default to debug" FORCE)

# Setup the cmake directory containing numerous cmake scripts and macros.
set(CMAKE_MODULE_PATH "${april_SOURCE_DIR}/cmake")

# Allow else() and endif() constructs (with empty parentheses)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

# Activate very verbose makefiles.
set(CMAKE_VERBOSE_MAKEFILE ON)

# Disallow in-source builds. #
##############################
EXECUTE_PROCESS(COMMAND pwd OUTPUT_VARIABLE CURR_DIR)
if("${CURR_DIR}" STREQUAL "${april_SOURCE_DIR}\n")
    message(FATAL_ERROR "In-source-builds are not allowed to build the liquid. Please go into the \"build\" directory and type \"ccmake ..\" there.\nThank you.")
endif()


message("lib: ${CMAKE_CURRENT_BINARY_DIR}")

# Put all source files into one variable. #
##########################################

set(SOURCES_COMMON
			src/assigbioperator.cpp
			src/assignment.cpp
            src/assignmentlist.cpp
            src/binaryope.cpp
            src/block.cpp
            src/boolean.cpp
            src/booleancmp.cpp
            src/break.cpp
            src/codegencontext.cpp
            src/double.cpp
            src/exprstatement.cpp
            src/for.cpp
            src/foriteration.cpp
            src/funclist.cpp
            src/function.cpp
            src/identifier.cpp
            src/if.cpp
            src/integer.cpp
            src/list.cpp
            src/listaccess.cpp
            src/methodcall.cpp
            src/methodhandlecast.cpp
            src/methodhandlefile.cpp
            src/methodhandleio.cpp
            src/methodhandlelist.cpp
            src/methodhandlestring.cpp
            src/methodstruct.cpp
            src/not.cpp
            src/return.cpp
            src/scope.cpp
            src/string.cpp
            src/stringarray.cpp
            src/symbol.cpp
            src/vardeclaration.cpp
            src/varDeclarationDeduce.cpp
            src/vardeclarationglobal.cpp
            parser.cpp
            lexer.cpp	
            main.cpp					
   )

set(HEADER_COMMON
			headers/assigbioperator.hpp
			headers/assignment.hpp
            headers/assignmentlist.hpp
            headers/binaryope.hpp
            headers/block.hpp
            headers/boolean.hpp
            headers/booleancmp.hpp
            headers/break.hpp
            headers/codegencontext.hpp
            headers/double.hpp
            headers/expression.hpp
            headers/exprstatement.hpp
            headers/for.hpp
            headers/foriteration.hpp
            headers/funclist.hpp
            headers/function.hpp
            headers/identifier.hpp
            headers/if.hpp
            headers/integer.hpp
            headers/list.hpp
            headers/listaccess.hpp
            headers/methodcall.hpp
            headers/methodhandlecast.hpp
            headers/methodhandlefile.hpp
            headers/methodhandleio.hpp
            headers/methodhandlelist.hpp
            headers/methodhandlestring.hpp
            headers/methodstruct.hpp
            headers/node.hpp
            headers/not.hpp
            headers/return.hpp
            headers/scope.hpp
            headers/statement.hpp
            headers/string.hpp
            headers/stringarray.hpp
            headers/symbol.hpp
            headers/vardeclaration.hpp
            headers/varDeclarationDeduce.hpp
            headers/vardeclarationglobal.hpp
            parser.h
   )

if(MSVC)
    source_group(Header\ Files FILES ${HEADER_COMMON})
    source_group(Source\ Files FILES ${SOURCE_COMMON})
endif()

add_executable(april ${SOURCES_COMMON} ${HEADER_COMMON})

# Check for various language-stuff and compiler versions #
##########################################################

# Compiler-dependent and build-depended flags:
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(april PRIVATE -Wall)
elseif(MSVC)
    target_compile_definitions(april PRIVATE YY_NO_UNISTD_H)
    target_compile_definitions(april PRIVATE _SCL_SECURE_NO_WARNINGS)
    target_compile_definitions(april PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(april PRIVATE __STDC_VERSION__=199901L) #flex/bison to avoid redefinition of int types.
endif()

# Debug or release ?
target_compile_definitions(april PRIVATE $<$<CONFIG:Debug>:_DEBUG>)

# Search for the different needed libs. #
#########################################

# We incorporate the CMake features provided by LLVM:

if(MSVC)
    if(NOT CMAKE_CL_64)
        message(FATAL_ERROR "Currently only 64bit compilation is supported!")
    else()
        message("Is 64 bits!")
    endif()
endif()

#enables C++ Exception
if(MSVC)
    # Don't remove C++ exception for MSVC since they are needed.
    target_compile_options(april PRIVATE /EHsc)
endif()
if(LLVM_ENABLE_EH AND CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(april PRIVATE -fexceptions)
endif()

set(VER_MAJ 0)
set(VER_MIN 2)
set(VER_REV 0)

configure_file(config.in ${april_SOURCE_DIR}/config.h)

# The compiling process. #
##########################

# Add additional include search directories.
target_include_directories(april PRIVATE ${april_SOURCE_DIR})
target_include_directories(april PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
message(${april_SOURCE_DIR})
message(${CMAKE_CURRENT_BINARY_DIR})

set_property(TARGET april PROPERTY CXX_STANDARD 14)
set_property(TARGET april PROPERTY CXX_STANDARD_REQUIRED ON)
