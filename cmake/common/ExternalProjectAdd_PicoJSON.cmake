include(ExternalProject)
set(PICOJSON_TARGET picojson)
ExternalProject_Add(${PICOJSON_TARGET}
  GIT_REPOSITORY  https://github.com/kazuho/picojson.git
  GIT_TAG         master
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  UPDATE_COMMAND    ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
  LOG_DOWNLOAD ON
  )

set(PICOJSON_FOUND TRUE)
ExternalProject_Get_Property(${PICOJSON_TARGET} source_dir)
set(PICOJSON_INCLUDE_DIRS ${source_dir})
set(PICOJSON_LIBRARIES)
