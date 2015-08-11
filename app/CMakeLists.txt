CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(img2term_app)

FIND_PACKAGE(Boost REQUIRED COMPONENTS program_options)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include/")

ADD_EXECUTABLE(img2term_app register_grayscale.cxx register_color.cxx register_combined.cxx main.cpp)
SET_TARGET_PROPERTIES(img2term_app PROPERTIES OUTPUT_NAME img2term)
TARGET_LINK_LIBRARIES(img2term_app img2term ${VIGRA_IMPEX_LIBRARY} ${Boost_LIBRARIES})
INSTALL(TARGETS img2term_app RUNTIME DESTINATION bin)

