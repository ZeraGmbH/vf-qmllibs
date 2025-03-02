file(GLOB TS_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ts
    )

add_custom_target(timzone-translations ALL
    DEPENDS ${TS_FILES}
    SOURCES ${TS_FILES}
    COMMAND ${LRELEASE} ${TS_FILES}
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/translations
    COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/*.qm ${CMAKE_CURRENT_BINARY_DIR}/translations
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/translations
    DESTINATION ${CMAKE_INSTALL_DATADIR}/zera
)
