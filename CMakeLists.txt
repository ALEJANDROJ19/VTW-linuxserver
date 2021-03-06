cmake_minimum_required(VERSION 3.6)
project(VTW_Server_Linux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(X11 REQUIRED)
find_package(Qt4 4.4.3 REQUIRED QtGui QtXml)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

set(SOURCE_FILES
        MainCore.cpp
        udpServer/UDPReceiver.cpp
        udpServer/UDPReceiver.h
        mouseController/CoordinatesXY.cpp
        mouseController/CoordinatesXY.h
        mouseController/CoordinatesXYZ.cpp
        mouseController/CoordinatesXYZ.h
        mouseController/controlmodule.cpp
        mouseController/controlmodule.h
        mouseController/controller.cpp
        mouseController/controller.h
        mouseController/stdafx.cpp
        mouseController/stdafx.h
        mouseController/translate.cpp
        mouseController/translate.h tcpServer/JsonHandler.cpp tcpServer/JsonHandler.h Portocol/HeaderDef.h tcpServer/TcpServer.cpp tcpServer/TcpServer.h startApp/startApp.cpp startApp/startApp.h Threads/Thread.h Threads/UdpThread.cpp Threads/UdpThread.h Threads/ForkThread.cpp Threads/ForkThread.h Threads/TcpThread.cpp Threads/TcpThread.h tcpServer/Callbacks.h)

add_executable(VTW_Server_Linux ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(VTW_Server_Linux json-c Qt4::QtGui Qt4::QtXml)

