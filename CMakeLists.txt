cmake_minimum_required(VERSION 3.12)
project(Berry3D)
set(CMAKE_CXX_FLAGS "-O0")

set(CMAKE_CXX_STANDARD 17)
set(HEADERS /usr/local/include)
set(GLFW_LINK /usr/local/lib/libglfw3.a)
set(FRAMEWORKS_1 /System/Library/Frameworks/Cocoa.framework)
set(FRAMEWORKS_2 /System/Library/Frameworks/OpenGL.framework)
set(FRAMEWORKS_3 /System/Library/Frameworks/GLUT.framework)
set(FRAMEWORKS_4 /System/Library/Frameworks/CoreVideo.framework)
set(FRAMEWORKS_5 /System/Library/Frameworks/IOKit.framework)

include_directories(${HEADERS})
aux_source_directory(Berry3D src)

link_libraries(${GLFW_LINK} ${FRAMEWORKS_1} ${FRAMEWORKS_2} ${FRAMEWORKS_3} ${FRAMEWORKS_4} ${FRAMEWORKS_5})

add_executable(Berry3D main.cpp src/math.cpp include/math.h src/Berry3D.cpp include/Berry3D.h src/camera.cpp include/camera.h src/scene.cpp include/scene.h src/item.cpp include/item.h include/cube.h include/timestamp.h src/loader.cpp include/loader.h src/objLoader.cpp include/objLoader.h include/shader.h include/draws.h include/plane.h)