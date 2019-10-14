cmake_minimum_required(VERSION 3.15)
project(StrangeCalc)

find_package(wxWidgets COMPONENTS core base REQUIRED)

include( "${wxWidgets_USE_FILE}" )

set(CMAKE_CXX_STANDARD 17)

add_executable(StrangeCalc main.cpp)

target_link_libraries(StrangeCalc ${wxWidgets_LIBRARIES})