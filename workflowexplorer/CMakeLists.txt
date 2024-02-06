# Copyright 2022 Ingemar Hedvall
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
project(WorkflowExplorer
        VERSION 1.0
        DESCRIPTION "Report Explorer"
        LANGUAGES CXX)

add_executable(workflowexplorer
        src/workflowexplorer.cpp src/workflowexplorer.h
        src/mainframe.cpp src/mainframe.h
        src/eventdialog.cpp src/eventdialog.h
        src/workflowexplorer.rc
        src/workflowexplorerid.h
        src/parameterpanel.cpp src/parameterpanel.h
        src/parameterdialog.cpp src/parameterdialog.h
        src/workflowpanel.cpp src/workflowpanel.h
        src/workflowdialog.cpp src/workflowdialog.h
        src/eventpanel.cpp src/eventpanel.h
        src/runnerdialog.cpp src/runnerdialog.h
        src/templatepanel.cpp src/templatepanel.h src/generalpanel.cpp src/generalpanel.h src/propertydialog.cpp src/propertydialog.h)



target_include_directories(workflowexplorer PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_include_directories(workflowexplorer PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(workflowexplorer PRIVATE ${utillib_SOURCE_DIR}/include)
target_include_directories(workflowexplorer PRIVATE ${workflow_SOURCE_DIR}/include)
target_include_directories(workflowexplorer PRIVATE ../include)
target_compile_definitions(workflowexplorer PRIVATE XML_STATIC)

if (MINGW)
target_link_options(workflowexplorer PRIVATE -mwindows -static -fstack-protector)
endif()

if (MSVC)
    target_link_options(workflowexplorer PRIVATE /SUBSYSTEM:WINDOWS)
    target_compile_definitions(workflowexplorer PRIVATE _WIN32_WINNT=0x0A00)
endif()

target_link_libraries(workflowexplorer PRIVATE workflowserv)
target_link_libraries(workflowexplorer PRIVATE ods)
target_link_libraries(workflowexplorer PRIVATE workflow)
target_link_libraries(workflowexplorer PRIVATE mdf)
target_link_libraries(workflowexplorer PRIVATE util)
target_link_libraries(workflowexplorer PRIVATE ${EXPAT_LIBRARIES})
target_link_libraries(workflowexplorer PRIVATE ${wxWidgets_LIBRARIES})
target_link_libraries(workflowexplorer PRIVATE ${Boost_LIBRARIES})
target_link_libraries(workflowexplorer PRIVATE ${SQLite3_LIBRARIES})
target_link_libraries(workflowexplorer PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpq.lib)
target_link_libraries(workflowexplorer PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpgtypes.lib)
target_link_libraries(workflowexplorer PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpgport.lib)
target_link_libraries(workflowexplorer PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpgcommon.lib)
target_link_libraries(workflowexplorer PRIVATE ${OPENSSL_LIBRARIES})
if (WIN32)
#target_link_libraries(reportexplorer PRIVATE iconv )
#target_link_libraries(reportexplorer PRIVATE ws2_32)
#target_link_libraries(reportexplorer PRIVATE wsock32)
target_link_libraries(workflowexplorer PRIVATE secur32)
target_link_libraries(workflowexplorer PRIVATE crypt32)
endif()

foreach (pqfile ${PostgreSQL_DEPENDENCIES})

    #Copy the Postgres DLL/SO files to the current binary directory
    add_custom_command(
            TARGET workflowexplorer
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ARGS ${pqfile} "${CMAKE_CURRENT_BINARY_DIR}"
    )
endforeach ()
