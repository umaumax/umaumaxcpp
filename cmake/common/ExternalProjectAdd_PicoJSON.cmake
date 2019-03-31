include(ExternalProject)
ExternalProject_Add(picojson
  GIT_REPOSITORY  https://github.com/kazuho/picojson.git
  GIT_TAG         master
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  UPDATE_COMMAND    ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
  LOG_DOWNLOAD ON
  )

# include(ExternalProject)
# ExternalProject_Add(cxxopts
# GIT_REPOSITORY    https://github.com/jarro2783/cxxopts.git
# GIT_TAG           master
# SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/cxxopts-build"
# CONFIGURE_COMMAND ""
# BUILD_COMMAND     ""
# INSTALL_COMMAND   ""
# TEST_COMMAND      ""
# BUILD_IN_SOURCE TRUE
# )
# set(cxxopts_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/cxxopts-build/include)
# target_include_directories(${PROJECT_NAME} PRIVATE
# ${cxxopts_INCLUDE_DIR}
# )
# add_dependencies(${PROJECT_NAME} cxxopts)

set(PicoJSON_FOUND TRUE)
ExternalProject_Get_Property(picojson source_dir)
set(PicoJSON_INCLUDE_DIRS ${source_dir})
set(PicoJSON_LIBRARIES)

set(PICOJSON_FOUND TRUE)
set(PICOJSON_INCLUDE_DIRS ${source_dir})
set(PICOJSON_LIBRARIES)
