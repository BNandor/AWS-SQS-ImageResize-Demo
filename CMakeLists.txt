cmake_minimum_required(VERSION 3.2)
project( ImageResize )
set (CMAKE_CXX_STANDARD 11)

find_package(AWSSDK REQUIRED COMPONENTS sqs)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} include)
add_executable( resize main.cpp  include/base64.cpp )
target_link_libraries( resize ${OpenCV_LIBS} ${AWSSDK_LINK_LIBRARIES})
