cmake_minimum_required(VERSION 3.26)
project(linprog VERSION 0.1)
set(C_STANDARD 99)
add_subdirectory(iolibs)
add_subdirectory(linlibs)

add_executable(linprog main.c)


target_link_libraries(linprog PRIVATE linlibs iolibs)
target_include_directories(linprog PRIVATE "${PROJECT_BINARY_DIR}"
"${PROJECT_SOURCE_DIR}/linlibs" "${PROJECT_SOURCE_DIR}/iolibs")

install(TARGETS linprog DESTINATION bin)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/cinstall")
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)
