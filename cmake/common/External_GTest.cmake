# FYI: [CMake ExternalProject\_Add for Google Mock \(gmock\) and Google Test \(gtest\) Libraries]( https://gist.github.com/ClintLiddick/51deffb768a7319e715071aa7bd3a3ab )
find_package(Threads REQUIRED)
set(GTEST_FOUND TRUE)
include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        mster
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  )

ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include)
set(GMOCK_INCLUDE_DIRS ${source_dir}/googlemock/include)

ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBRARY_PATH ${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
set(GTEST_LIBRARY gtest)
add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
set_target_properties(${GTEST_LIBRARY} PROPERTIES
  IMPORTED_LOCATION ${GTEST_LIBRARY_PATH}
  # NOTE: ${CMAKE_THREAD_LIBS_INIT} may be blank
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
add_dependencies(${GTEST_LIBRARY} googletest)

set(GTEST_MAIN_LIBRARY_PATH ${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a)
set(GTEST_MAIN_LIBRARY gtest_main)
add_library(${GTEST_MAIN_LIBRARY} UNKNOWN IMPORTED)
set_target_properties(${GTEST_MAIN_LIBRARY} PROPERTIES
  IMPORTED_LOCATION ${GTEST_MAIN_LIBRARY_PATH}
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
add_dependencies(${GTEST_MAIN_LIBRARY} googletest)

set(GMOCK_LIBRARY_PATH ${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gmock.a)
set(GMOCK_LIBRARY gmock)
add_library(${GMOCK_LIBRARY} UNKNOWN IMPORTED)
set_target_properties(${GMOCK_LIBRARY} PROPERTIES
  IMPORTED_LOCATION ${GMOCK_LIBRARY_PATH}
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
add_dependencies(${GMOCK_LIBRARY} googletest)

set(GMOCK_MAIN_LIBRARY_PATH ${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gmock_main.a)
set(GMOCK_MAIN_LIBRARY gmock_main)
add_library(${GMOCK_MAIN_LIBRARY} UNKNOWN IMPORTED)
set_target_properties(${GMOCK_MAIN_LIBRARY} PROPERTIES
  IMPORTED_LOCATION ${GMOCK_MAIN_LIBRARY_PATH}
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
add_dependencies(${GMOCK_MAIN_LIBRARY} ${GTEST_LIBRARY})

set(GTEST_LIBRARIES ${GTEST_LIBRARY})
set(GTEST_MAIN_LIBRARIES ${GTEST_MAIN_LIBRARY})
set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
set(GMOCK_LIBRARIES ${GMOCK_LIBRARY})
set(GMOCK_MAIN_LIBRARIES ${GMOCK_MAIN_LIBRARY})
set(GMOCK_BOTH_LIBRARIES ${GMOCK_LIBRARIES} ${GMOCK_MAIN_LIBRARIES})
