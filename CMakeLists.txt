cmake_minimum_required(VERSION 3.25)
project(textdb)

set(BOOST_ROOT lib/boost_1_82_0)
set(BOOST_INCLUDEDIR lib/boost_1_82_0)
set(BOOST_LIBRARYDIR lib/boost_1_82_0/lib)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.82.0 REQUIRED COMPONENTS log log_setup system filesystem date_time thread chrono)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini COPYONLY)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(textdb src/main.cpp src/util/config.cpp src/util/config.h src/util/log.cpp src/util/log.h src/common.h src/db/table.cpp src/db/table.h src/core/dberror.h src/db/io.cpp src/db/columns.cpp src/db/rows.cpp)
target_link_libraries(textdb ${Boost_LIBRARIES})