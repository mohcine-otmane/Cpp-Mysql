cmake_minimum_required(VERSION 3.10)
project(LoginApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug symbols
set(CMAKE_BUILD_TYPE Debug)

if(WIN32)
    # wxWidgets configuration
    set(wxWidgets_LIBRARIES 
        "C:/msys64/mingw64/lib/libwx_mswu_core-3.2.dll.a"
        "C:/msys64/mingw64/lib/libwx_baseu-3.2.dll.a"
    )
    set(wxWidgets_INCLUDE_DIRS 
        "C:/msys64/mingw64/include/wx-3.2"
        "C:/msys64/mingw64/lib/wx/include/msw-unicode-3.2"
    )
    add_definitions(-D__WXMSW__ -DWXUSINGDLL)
    
    # MariaDB configuration
    set(MySQL_INCLUDE_DIR "C:/msys64/mingw64/include")
    set(MySQL_LIBRARY "C:/msys64/mingw64/lib/libmariadb.dll.a")
    
    # Add DLL output directory
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    
    # Create output directories
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Debug)
endif()

add_executable(LoginApp 
    src/main.cpp
    src/LoginFrame.cpp
    src/LoginFrame.h
    src/Database.cpp
    src/Database.h
)

target_include_directories(LoginApp PRIVATE 
    ${MySQL_INCLUDE_DIR}
    ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(LoginApp PRIVATE 
    ${wxWidgets_LIBRARIES}
    ${MySQL_LIBRARY}
)

# Copy DLLs to output directory
if(WIN32)
    # List of DLLs to copy
    set(DLLS_TO_COPY
        "C:/msys64/mingw64/bin/libmariadb.dll"
        "C:/msys64/mingw64/bin/wxbase32u_gcc_custom.dll" 
        "C:/msys64/mingw64/bin/wxmsw32u_core_gcc_custom.dll"
        "C:/msys64/mingw64/bin/libcurl-4.dll"
    )

    # Copy to main output directory
    add_custom_command(TARGET LoginApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLLS_TO_COPY}
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/"
    )

    # Copy to Debug directory
    add_custom_command(TARGET LoginApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLLS_TO_COPY}
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/"
    )
endif()
