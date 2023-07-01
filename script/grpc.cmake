# Copyright 2023 Ingemar Hedvall
# SPDX-License-Identifier: MIT


if (NOT gRPC_FOUND)
    set(gRPC_USE_STATIC_LIBS ON)
    set(gRPC_DEBUG ON)
    find_package(gRPC CONFIG)
    message(STATUS "gRPC Found (Try 1): " ${gRPC_FOUND})
    if (NOT gRPC_FOUND)
        set( gRPC_ROOT "k:/grpc/master")
        find_package(gRPC CONFIG REQUIRED)
        message(STATUS "gRPC Found (Try 2): " ${gRPC_FOUND})

    endif()
endif()

if (gRPC_FOUND)
    get_target_property(gRPC_INCLUDE_DIRS gRPC::grpc INTERFACE_INCLUDE_DIRECTORIES )
    get_target_property(gRPC_LIBRARIES gRPC::grpc INTERFACE_LINK_LIBRARIES )

    find_program(gRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
    cmake_print_properties(TARGETS gRPC::grpc PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES
            INTERFACE_LINK_LIBRARIES
            LOCATION)

    cmake_print_properties(TARGETS gRPC::grpc++ PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES
            INTERFACE_LINK_LIBRARIES
            LOCATION)
    cmake_print_properties(TARGETS gRPC::grpc++_reflection PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES
            INTERFACE_LINK_LIBRARIES
            LOCATION)

    cmake_print_properties(TARGETS gRPC::grpc_cpp_plugin PROPERTIES
            LOCATION)

    cmake_print_variables(gRPC_VERSION)
    cmake_print_variables(gRPC_INCLUDE_DIRS)
    cmake_print_variables(gRPC_LINK_LIBRARIES)
endif()