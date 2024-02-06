# Copyright 2022 Ingemar Hedvall
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
project(workflowapp
        VERSION 1.0
        DESCRIPTION "Workflow Applications"
        LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Static libraries are preferred" OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DEBUG_POSTFIX d)

include(CMakePrintHelpers)

include(script/utillib.cmake)
include(script/mdflib.cmake)
include(script/workflowlib.cmake)
include(script/odslib.cmake)


include(script/boost.cmake)


include(script/postgresql.cmake)
include(script/sqlite3.cmake)
#include(script/openssl.cmake)
#include(script/protobuf.cmake)
#include(script/grpc.cmake)
include(script/wxwidgets.cmake)

#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS proto/eventlogservice.proto proto/eventmessage.proto)
#cmake_print_variables(PROTO_SRCS)
#cmake_print_variables(PROTO_HDRS)
cmake_print_variables(CMAKE_CURRENT_BINARY_DIR) # Path to the generated cpp files

add_library(workflowserv STATIC
        src/genericworkflowserver.cpp include/workflow/genericworkflowserver.h
#        ${PROTO_SRCS} ${PROTO_HDRS}
        )

add_subdirectory(workflowexplorer)

target_include_directories(workflowserv PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_include_directories(workflowserv PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(workflowserv PRIVATE ${utillib_SOURCE_DIR}/include)
target_include_directories(workflowserv PRIVATE ${workflowlib_SOURCE_DIR}/include)
target_include_directories(workflowserv PRIVATE ${odslib_SOURCE_DIR}/include)
target_include_directories(workflowserv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
#target_include_directories(workflowserv PRIVATE ${Protobuf_INCLUDE_DIRS})
#target_include_directories(workflowserv PRIVATE ${gRPC_INCLUDE_DIRS} )
#target_include_directories(ods PUBLIC
#        $<INSTALL_INTERFACE:include>
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#        )


target_compile_definitions(workflowserv PRIVATE XML_STATIC)
