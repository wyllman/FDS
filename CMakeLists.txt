cmake_minimum_required (VERSION 3.0)

project(FDS)

set (CMAKE_BUILD_TYPE DEBUG)
set (CMAKE_C_COMPÎLER clang)
set (CMAKE_CXX_COMPILER clang++)
list (APPEND CMAKE_CXX_FLAGS -std=c++14)

find_package(Boost REQUIRED)
if (Boost_FOUND)
        include_directories (${Boost_INCLUDE_DIRS})
        set (BOOST_SYSTEM_LIB ${Boost_LIBRARY_DIRS}/libboost_system.so)
        set (BOOST_IOSTREAM_LIB ${Boost_LIBRARY_DIRS}/libboost_iostreams.so)
endif (Boost_FOUND)

include_directories(include)

add_executable(FDS src/Test.cpp src/Deposit.cpp src/Valve.cpp main.cpp)

target_link_libraries (
	FDS
	${BOOST_SYSTEM_LIB}
	${BOOST_IOSTREAM_LIB}
)

install(TARGETS FDS RUNTIME DESTINATION bin)
