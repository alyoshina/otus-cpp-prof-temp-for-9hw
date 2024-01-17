cmake_minimum_required(VERSION 3.16.3)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(async VERSION ${PROJECT_VERSION})

add_library(async SHARED 
    src/async.cpp
    src/commands.cpp
    src/parser.cpp
)

target_include_directories(async PRIVATE
    "${CMAKE_BINARY_DIR}"
    src
    include
)

configure_file(version.h.in version.h)


add_executable(async_cli src/main.cpp)

target_link_libraries(async_cli async)

target_include_directories(async_cli PRIVATE
    "${CMAKE_BINARY_DIR}"
    src
    include
)
  
set_target_properties(async async_cli PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(async PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(async PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

#--------------------------------------
message(STATUS "CMAKE_CURRENT_LIST_DIR IS: " ${CMAKE_CURRENT_LIST_DIR})
set_target_properties(async PROPERTIES PUBLIC_HEADER "include/async.h")

message(STATUS "PUBLIC_HEADER IS: " async.${PUBLIC_HEADER})

#install(TARGETS async async_cli)
#install(FILES include/async.h DESTINATION include/async)
#install(FILES AsyncConfig.cmake DESTINATION lib/cmake/Async)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/AsyncConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/async"
  NO_SET_AND_CHECK_MACRO NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/AsyncConfigVersion.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY AnyNewerVersion
)

# install the configuration file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/AsyncConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/AsyncConfigVersion.cmake
        DESTINATION lib/cmake/async
)

install(TARGETS async async_cli)

#PUBLIC_HEADER
install(
        DIRECTORY include/
        DESTINATION include/async
        FILES_MATCHING PATTERN "*.h"
        )

#--------------------------------------

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

