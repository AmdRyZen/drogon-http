cmake_minimum_required(VERSION 3.20)

SET(CMAKE_C_COMPILER "/usr/local/bin/gcc-11")
SET(CMAKE_CXX_COMPILER "/usr/local/bin/g++-11")

project(drogon-http C CXX)

include(CheckIncludeFileCXX)

#configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in @ONLY)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 23)

elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 23)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 条件判断
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_CXX_FLAGS_DEBUG "-pipe -Wall -O0 -L/usr/local/lib -ljemalloc")
    message("Debug mode:${CMAKE_CXX_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_CXX_FLAGS_RELEASE "-pipe -w -Ofast -march=native -flto -L/usr/local/lib -ljemalloc")
    message("Release mode:${CMAKE_CXX_FLAGS_RELEASE}")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "-pipe -w -Ofast -march=native -flto -L/usr/local/lib -ljemalloc")
    message("Release mode:${CMAKE_CXX_FLAGS_RELEASE}")
    message("CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE}")
endif()

#find_package(Threads REQUIRED)
#find_package(PkgConfig REQUIRED)
# Find required protobuf package
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()
include_directories(${Protobuf_INCLUDE_DIRS})

add_subdirectory(proto)
#include_directories(${PROTO_GEN_C_INCLUDE_DIRS}) # c
include_directories(${PROTO_GEN_CXX_INCLUDE_DIRS}) # cpp

add_executable(
    ${PROJECT_NAME} main.cc
    controllers/PlaintextCtrl.cc controllers/PlaintextCtrl.h
    controllers/api_v1_User.cc controllers/api_v1_User.h
    controllers/api_v1_OpenApi.cc controllers/api_v1_OpenApi.h
    utils/redisUtils.h utils/redisUtils.cpp
    ws_controllers/EchoWebsocket.h ws_controllers/EchoWebsocket.cc
    service/SbcConvertService.h service/impl/SbcConvertServiceImpl.cpp
    service/TrieService.h service/impl/TrieServiceImpl.cpp
    utils/base64Utils.h utils/base64Utils.c
    utils/aes.h utils/aes.c utils/cipherUtils.h utils/cipherUtils.cpp utils/md5Utils.h utils/md5Utils.cpp aop/Application.h threadPool/threadPool.h utils/checkloginUtils.h filters/LoginFilter.h)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon
# add_subdirectory(drogon)
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)
find_package(mimalloc 1.7.6 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon proto_gen_cxx)

# ##############################################################################

if (CMAKE_CXX_STANDARD LESS 17)
    # With C++14, use boost to support any, string_view and filesystem
    message(STATUS "use c++14")
    find_package(Boost 1.61.0 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
elseif (CMAKE_CXX_STANDARD LESS 23)
    message(STATUS "use c++20")
else ()
    message(STATUS "use c++23")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})
# use the following line to create views with namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC})
# ##############################################################################
# uncomment the following line for dynamically loading views
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

# ##############################################################################

#add_subdirectory(test)
