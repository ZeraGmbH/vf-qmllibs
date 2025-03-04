set(CMAKE_TIMEZONE_TRANSLATE_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/zera/translations")
set(CMAKE_TIMEZONE_TRANSLATE_BUILD_PATH "${PROJECT_BINARY_DIR}/translations")

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(translation-files)
