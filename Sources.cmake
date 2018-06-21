# Libraries:

link_libraries (gcc)

set (hwlib ${build_environment}/libraries/hwlib)
include_directories (${hwlib}/library)

set (catch ${build_environment}/libraries/Catch2)
include_directories (${catch}/single_include)

# Source Files:

set (sources
    src/coordinate3d.cpp
    src/libc-stub.cpp
    src/main.cpp
    src/robot_arm.cpp
	src/uart_connection.cpp
    src/wrap-hwlib.cpp
)