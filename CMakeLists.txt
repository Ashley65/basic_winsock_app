cmake_minimum_required(VERSION 3.26)
project(Network)

set(CMAKE_CXX_STANDARD 17)

add_executable(Network main.cpp
        TCP_server.cpp
        TCP_client.cpp
        test.c
)

# Adding libraries from the system
find_package(Threads REQUIRED)
target_link_libraries(Network Threads::Threads)

set(MARIADBCPP_DIR "C:/Program Files/MariaDB/MariaDB C++ Connector 64-bit/include/mariadb")
set(MARIADBCPP_LIB "C:/Program Files/MariaDB/MariaDB C++ Connector 64-bit/mariadbcpp.dll")

set(MARIADB_DIR "C:/Program Files/MariaDB 11.1/include/mysql")
set(MARIADB_LIB "C:/Program Files/MariaDB 11.1/lib/libmariadb.dll")

# Adding MariaDB library
include_directories(${MARIADB_DIR})
include_directories(${MARIADBCPP_DIR})

# Adding socket library
if (WIN32)
    target_link_libraries(Network wsock32 ws2_32)
endif ()

# Linking MariaDB libraries after other libraries
target_link_libraries(Network ${MARIADB_LIB})
target_link_libraries(Network ${MARIADBCPP_LIB})






