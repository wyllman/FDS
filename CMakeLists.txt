cmake_minimum_required (VERSION 2.8)

project(FDS)

set (CMAKE_BUILD_TYPE DEBUG)
set (CMAKE_CXX_COMPILER clang++-3.6)

find_package(Boost REQUIRED)
if (Boost_FOUND)
        include_directories (${Boost_INCLUDE_DIRS})
        set (BOOST_SYSTEM_LIB ${Boost_LIBRARY_DIRS}/x86_64-linux-gnu/libboost_system.so)
        set (BOOST_IOSTREAM_LIB ${Boost_LIBRARY_DIRS}/x86_64-linux-gnu/libboost_iostreams.so)
endif (Boost_FOUND)

add_executable(FDS Test.cpp Deposit.cpp Valve.cpp main.cpp)

target_link_libraries (
	FDS
	${BOOST_SYSTEM_LIB}
	${BOOST_IOSTREAM_LIB}
)

install(TARGETS FDS RUNTIME DESTINATION bin)
