# This module finds an installed Vigra package.
#
# It sets the following variables:
#  GTEST_FOUND              - Set to false, or undefined, if vigra isn't found.
#  GTEST_INCLUDE_DIR        - gtest include directory.
#  GTEST_LIBRARY            - gtest library
#  GTEST_MAIN_LIBRARY       - gtest main library
#  GTEST_LIBRARIES          - both libraries

# look for gtest.h
FIND_PATH(GTEST_INCLUDE_DIR gtest/gtest.h PATHS $ENV{GTEST_ROOT}/include ENV CPLUS_INCLUDE_PATH)
FIND_LIBRARY(GTEST_LIBRARY gtest PATHS $ENV{GTEST_ROOT} $ENV{GTEST_ROOT}/lib ENV LD_LIBRARY_PATH ENV LIBRARY_PATH)
GET_FILENAME_COMPONENT(GTEST_LIBRARY_PATH ${GTEST_LIBRARY} PATH)
FIND_LIBRARY(GTEST_MAIN_LIBRARY gtest_main PATHS $ENV{GTEST_RPPT} $ENV{GTEST_ROOT}/lib ENV LD_LIBRARY_PATH ENV LIBRARY_PATH)
SET(GTEST_LIBRARIES "${GTEST_LIBRARY}" "${GTEST_MAIN_LIBRARY}")
SET(GTEST_LIBRARY_DIR ${GTEST_LIBRARY_PATH} CACHE PATH "Path to gtest library.")

# handle the QUIETLY and REQUIRED arguments and set GTEST_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GTEST DEFAULT_MSG GTEST_LIBRARY GTEST_MAIN_LIBRARY GTEST_INCLUDE_DIR GTEST_LIBRARIES)
IF(GTEST_FOUND)
    IF (NOT Vigra_FIND_QUIETLY)
      MESSAGE(STATUS "  > includes:               ${GTEST_INCLUDE_DIR}")
      MESSAGE(STATUS "  > gtest library dir:      ${GTEST_LIBRARY_DIR}")
      MESSAGE(STATUS "  > gtest library:          ${GTEST_LIBRARY}")
      MESSAGE(STATUS "  > gtest main library:     ${GTEST_MAIN_LIBRARY}")
      MESSAGE(STATUS "  > gtest libraries:        ${GTEST_LIBRARIES}")
    ENDIF()
ENDIF()


MARK_AS_ADVANCED( GTEST_INCLUDE_DIR GTEST_LIBRARY GTEST_MAIN_LIBRARY GTEST_LIBRARY_DIR GTEST_LIBRARIES )
