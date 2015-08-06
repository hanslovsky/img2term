CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfatal-errors -std=c++14 -pedantic -pthread" CACHE STRING "CXX Flags for all builds")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0" CACHE STRING "CXX Flags debug specific")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Werror -DNDEBUG" CACHE STRING "CXX Flags release specific")

PROJECT(img2term)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include/")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_extensions/)
FIND_PACKAGE(VIGRA REQUIRED)
if (VIGRA_FOUND)
   MESSAGE("--   > vigra found!")
   INCLUDE_DIRECTORIES(${VIGRA_INCLUDE_DIR})
   LINK_DIRECTORIES( ${VIGRA_IMPEX_LIBRARY_DIR})
endif()
FIND_PACKAGE(Boost REQUIRED COMPONENTS program_options)

FIND_PACKAGE(GTEST REQUIRED)
if (GTEST_FOUND)
    MESSAGE("--   > gtest found!")
    INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIR})
    LINK_DIRECTORIES(${GTEST_LIBRARY_DIR})
endif(GTEST_FOUND)


set(WITH_PYTHON "0" CACHE BOOL "Build python libraries.")
if (WITH_PYTHON)
  ADD_SUBDIRECTORY( src/python )
endif(WITH_PYTHON)

# FILE(GLOB LIB_CXX "src/lib/line*.cxx" "src/lib/modifier*.cxx" "src/lib/transformer*" "src/lib/color*cxx" "src/lib/averager*cxx" 
# "src/lib/matching*.cxx" "src/lib/distance*cxx")
# ADD_LIBRARY(img2term SHARED ${LIB_CXX})
# ADD_EXECUTABLE(img2term_app2 src/bin/img2term_app2.cxx)
ADD_EXECUTABLE(img2term main.cpp)
TARGET_LINK_LIBRARIES(img2term ${VIGRA_IMPEX_LIBRARY} ${Boost_LIBRARIES})
# SET_TARGET_PROPERTIES(img2term_app2 PROPERTIES OUTPUT_NAME img2term2)
# 
# TARGET_LINK_LIBRARIES(img2term ${Boost_LIBRARIES})
# TARGET_LINK_LIBRARIES(img2term_app2 img2term ${VIGRA_IMPEX_LIBRARY})

# INSTALL(TARGETS img2term LIBRARY DESTINATION lib)
# INSTALL(TARGETS img2term_app RUNTIME DESTINATION bin)

# ENABLE_TESTING()
# 
# ADD_SUBDIRECTORY( test )

# install(TARGETS img2term_refactor RUNTIME DESTINATION bin)
