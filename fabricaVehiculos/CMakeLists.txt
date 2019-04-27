cmake_minimum_required(VERSION 3.13)
project(interfaz_Procesos)

find_package (PkgConfig REQUIRED)
find_package(Threads)
SET ( FOOBAR_LIBS ${GTK2_LIBRARIES} )

pkg_check_modules (GTK2 REQUIRED gtk+-3.0)

include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK_LIBRARY_DIRS})
add_executable (interfaz_Procesos main.cpp
        Lista.h
        Nodo.h)

target_link_libraries (interfaz_Procesos ${GTK2_LIBRARIES})
target_link_libraries (interfaz_Procesos ${CMAKE_THREAD_LIBS_INIT})
add_definitions (${GTK_CFLAGS_OTHER})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")