cmake_minimum_required(VERSION 3.5)

project(stu_asm LANGUAGES C CXX)
ENABLE_LANGUAGE(ASM_NASM) #ASM

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#INCLUDE(cmake/FindSSE.cmake)
#FindSSE()
#IF(SSE3_FOUND)
#    IF(SSSE3_FOUND)
#            SET(CXX_DFLAGS -msse3 -mssse3)
#    ENDIF(SSSE3_FOUND)
#ENDIF(SSE3_FOUND)

#IF(SSE4_2_FOUND)
#        SET(CXX_DFLAGS -msse4.2)
#ENDIF(SSE4_2_FOUND)
#ADD_DEFINITIONS(${CXX_DFLAGS})

if(NOT APPLE)
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-as-needed")
endif()

set_property(SOURCE main.cpp APPEND_STRING PROPERTY COMPILE_FLAGS
    "-march=native -mssse3 -msse3 -msse4.2 -mavx -mavx2 -mavx512f -mavx512dq -mavx512vl ")
add_executable(stu_asm main.cpp)


