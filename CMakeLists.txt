cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(rtsp_server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0) 
pkg_check_modules(GSTRTSP REQUIRED gstreamer-rtsp-server-1.0)

include_directories(${GSTREAMER_INCLUDE_DIRS})
include_directories(${GSTRTSP_INCLUDE_DIRS})

file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_executable(${PROJECT_NAME}
    ${CPP_SOURCES}
)

target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES}) 
target_link_libraries(${PROJECT_NAME} ${GSTRTSP_LIBRARIES})