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



#FIND_PACKAGE(flex)
#FIND_PACKAGE(bison)


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
			src/arrayaccess.cpp
			src/array.cpp
            src/assigbiope.cpp			
            src/assignment.cpp
			src/assignmentarray.cpp
            src/bioperator.cpp			
            src/block.cpp					
            src/boolean.cpp				
            src/codegencontext.cpp		
            src/comparasionope.cpp		
            src/conditional.cpp			
            src/double.cpp				
            src/exprstatement.cpp
			src/errors.cpp
            src/forloop.cpp				
            src/function.cpp				
            src/identifier.cpp			
            src/integer.cpp				
            src/lexer.l					
            src/logicope.cpp				
            src/methodcall.cpp
			src/msg.cpp
            src/nativefn.cpp				
            src/parser.y				
            src/return.cpp				
            src/scope.cpp					
            src/string.cpp				
            src/unaryope.cpp				
            src/vardeclaration.cpp		
            src/vardeclarationdeduce.cpp
			src/arrayaddelement.cpp
            parser.cpp
            lexer.cpp	
            main.cpp					
   )

set(HEADER_COMMON
			include/arrayaccess.hpp
			include/array.hpp
            include/assigbiope.hpp			
            include/assignment.hpp
			include/assignmentarray.hpp
            include/bioperator.hpp			
            include/block.hpp					
            include/boolean.hpp				
            include/codegenblock.hpp		
            include/codegencontext.hpp		
            include/comparasionope.hpp		
            include/conditional.hpp			
            include/double.hpp				
            include/errors.hpp			
            include/expression.hpp			
            include/exprstatement.hpp			
            include/forloop.hpp				
            include/function.hpp				
            include/identifier.hpp			
            include/integer.hpp				
            include/logicope.hpp				
            include/methodcall.hpp	
			include/msg.hpp	
            include/nativefn.hpp			
            include/node.hpp			
            include/return.hpp				
            include/scope.hpp					
            include/statement.hpp					
            include/string.hpp				
            include/unaryope.hpp				
            include/vardeclaration.hpp		
            include/vardeclarationdeduce.hpp
			include/arrayaddelement.hpp
            parser.h
   )

if(MSVC)
    source_group(Header\ Files FILES ${HEADER_COMMON})
    source_group(Source\ Files FILES ${SOURCE_COMMON})
endif()

#BISON_TARGET(Parser src/parser.y src/parser.cpp)
#FLEX_TARGET(Scanner src/lexer.l src/lexer.cpp )
#ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

FIND_PACKAGE(LLVM REQUIRED CONFIG)

MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

INCLUDE_DIRECTORIES(${LLVM_INCLUDE_DIRS})
ADD_DEFINITIONS(${LLVM_DEFINITIONS})

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

if( CMAKE_SYSTEM_NAME MATCHES Linux )
    set(LLVM_ROOT "/usr/llvm" CACHE PATH "Root of LLVM installation.")
elseif( CMAKE_SYSTEM_NAME MATCHES Windows )
    set(LLVM_ROOT "C:/Users/kenshin urashima/Desktop/Tesis/llvm-3.8.0_x64" CACHE PATH "Root of LLVM installation.")
else()
    set(LLVM_ROOT "" CACHE PATH "Root of LLVM install.")
endif()
if( NOT EXISTS ${LLVM_ROOT} )
    message(FATAL_ERROR "Invalid setup for LLVM installation in ${LLVM_ROOT}. Set the LLVM_ROOT first and then re-run.")
endif()

# A bit of a sanity check:
if( NOT EXISTS ${LLVM_ROOT}/include/llvm )
    message(FATAL_ERROR "LLVM_ROOT (${LLVM_ROOT}) is not a valid LLVM install")
endif()

if( EXISTS ${LLVM_ROOT}/share/llvm/cmake )
	# LLVM 3.8 uses this.
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_ROOT}/share/llvm/cmake")
else()
    message(FATAL_ERROR "LLVM: can't find the cmake support files. Abort!")
endif()

include(LLVMConfig)

message(STATUS "Found LLVM Package Version:${LLVM_PACKAGE_VERSION}")

string(REGEX MATCH "[0-9]+\\.[0-9]+" LLVM_VER ${LLVM_PACKAGE_VERSION} )
if(${LLVM_VER} VERSION_LESS "3.8" )
    message(FATAL_ERROR "LLVM version before 3.8 are not supported. Abort!")
endif()

if(MSVC)
    if(NOT CMAKE_CL_64)
        message(FATAL_ERROR "Currently only 64bit compilation is supported!")
    else()
        message("Is 64 bits!")
    endif()
endif()

# Add the compiler definitions of LLVM
target_compile_definitions(april PRIVATE ${LLVM_DEFINITIONS})

# Now set the header and library paths:
include_directories( ${LLVM_ROOT}/include )
link_directories( ${LLVM_ROOT}/lib )

# Let's suppose we want to build a JIT compiler with support for
# binary code :
llvm_map_components_to_libnames(REQ_LLVM_LIBRARIES mcjit interpreter native ipo)


if(NOT LLVM_ENABLE_RTTI)
    target_compile_definitions(april PRIVATE april_NO_RTTI)
    if(MSVC)
        target_compile_options(april PRIVATE /GR-)
    else()
        target_compile_options(april PRIVATE -fno-rtti)
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

# Finally, we link the LLVM libraries to our executable:
target_link_libraries(april ${REQ_LLVM_LIBRARIES})