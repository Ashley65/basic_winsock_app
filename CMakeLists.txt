cmake_minimum_required(VERSION 3.26)
project(Network)

set(CMAKE_CXX_STANDARD 17)



add_executable(Network main.cpp
        TCP_server.cpp
        TCP_client.cpp
)

# Adding libraries from the system
find_package(Threads REQUIRED)
target_link_libraries(Network Threads::Threads)
include_directories("C:/Program Files/MySQL/MySQL Connector C++ 8.2/include")
link_directories("C:/Program Files/MySQL/MySQL Connector C++ 8.2/lib64")


# Adding socket library
if (WIN32)
    target_link_libraries(Network wsock32 ws2_32)
endif ()

#adding MySQL library
if (WIN32)
    target_link_libraries(Network mysqlcppconn)
endif ()







