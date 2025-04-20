cmake_minimum_required(VERSION 3.10)
project(LoginApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add source files
add_executable(LoginApp 
    src/main.cpp
    src/LoginFrame.cpp
    src/LoginFrame.h
    src/Database.cpp
    src/Database.h
)

# ---- Platform-specific configurations ----

if(WIN32)
    # wxWidgets manual config (MSYS2)
    set(wxWidgets_LIBRARIES 
        "C:/msys64/mingw64/lib/libwx_mswu_core-3.2.dll.a"
        "C:/msys64/mingw64/lib/libwx_baseu-3.2.dll.a"
    )
    set(wxWidgets_INCLUDE_DIRS 
        "C:/msys64/mingw64/include/wx-3.2"
        "C:/msys64/mingw64/lib/wx/include/msw-unicode-3.2"
    )
    set(MySQL_INCLUDE_DIR "C:/msys64/mingw64/include")
    set(MySQL_LIBRARY "C:/msys64/mingw64/lib/libmariadb.dll.a")
    add_definitions(-D__WXMSW__ -DWXUSINGDLL)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    target_include_directories(LoginApp PRIVATE 
        ${MySQL_INCLUDE_DIR}
        ${wxWidgets_INCLUDE_DIRS}
    )

    target_link_libraries(LoginApp PRIVATE 
        ${wxWidgets_LIBRARIES}
        ${MySQL_LIBRARY}
    )

    # DLL copy
    set(DLLS_TO_COPY
        "C:/msys64/mingw64/bin/libmariadb.dll"
        "C:/msys64/mingw64/bin/wxbase32u_gcc_custom.dll" 
        "C:/msys64/mingw64/bin/wxmsw32u_core_gcc_custom.dll"
        "C:/msys64/mingw64/bin/libcurl-4.dll"
    )

    add_custom_command(TARGET LoginApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLLS_TO_COPY}
        "$<TARGET_FILE_DIR:LoginApp>"
    )

else()  # Linux / macOS

    find_package(wxWidgets REQUIRED COMPONENTS core base)
    include(${wxWidgets_USE_FILE})

    find_path(MYSQL_INCLUDE_DIR mysql.h PATH_SUFFIXES mariadb)
    find_library(MYSQL_LIBRARY mariadb)

    target_include_directories(LoginApp PRIVATE 
        ${MYSQL_INCLUDE_DIR}
    )

    target_link_libraries(LoginApp PRIVATE 
        ${wxWidgets_LIBRARIES}
        ${MYSQL_LIBRARY}
    )

endif()
