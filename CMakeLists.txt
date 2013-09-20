SET(CMAKE_C_COMPILER "clang")
SET(CMAKE_CXX_COMPILER "clang++")
project (webpp-demo)
set (webpp_VERSION_MAJOR 1)
set (webpp_VERSION_MINOR 0)
cmake_minimum_required (VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/webpp/cmake/Modules/" "${CMAKE_SOURCE_DIR}/webpp/xmlrenderer/cmake/Modules/" "${CMAKE_SOURCE_DIR}/webpp/soci/cmake")

add_subdirectory(webpp)

add_definitions(
	-Wall 
	-Wextra
	-std=c++11
)


set(AllHeaders src/config.hpp src/pages.hpp src/application.hpp src/entities.hpp)

include_directories(${webpp-demo_SOURCE_DIR}/webpp ${webpp-demo_SOURCE_DIR}/webpp/webpp-common ${webpp-demo_SOURCE_DIR}/webpp/xmlrenderer)

add_executable(demo-cgi src/main_cgi.cpp ${AllHeaders})
add_executable(demo-fcgi src/main_fcgi.cpp ${AllHeaders})

set(CommonLibs ${Boost_LIBRARIES} webpp-common ${LibXML++_LIBRARIES} ${SociLibs} xmlrenderer cgicc webpp ${pthread_library} fcgi)

target_link_libraries(demo-cgi ${CommonLibs})
target_link_libraries(demo-fcgi ${CommonLibs})

ENABLE_TESTING()

add_definitions(
    -DBOOST_TEST_DYN_LINK
)

#add_executable(qm-test tests/query_matcher.cpp src/query_matcher.cpp src/http_error.cpp)
#target_link_libraries(qm-test ${CommonLibs})
#add_test(response-test response-test)
