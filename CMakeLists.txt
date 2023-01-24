cmake_minimum_required(VERSION 3.10)
project(guiHannah)

find_package(X11)

add_executable(guiHannah helloworld.cpp)

target_link_libraries(guiHannah 
	${X11_LIBRARIES}
	)
