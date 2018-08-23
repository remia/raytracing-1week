project (RayTracing)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")
set(CMAKE_CXX_FLAGS "-fcolor-diagnostics -Wall -Werror -Wfatal-errors")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(SOURCES
    main.cpp
    vec3.cpp
    ray.cpp
    sphere.cpp
    hitable_list.cpp
    camera.cpp
    material.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
