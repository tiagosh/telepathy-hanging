project(telepathy-hanging)

cmake_minimum_required(VERSION 2.8)

find_package(TelepathyQt5 0.9.6 REQUIRED)
find_package(TelepathyQt5Service 0.9.6 REQUIRED)
find_package(Protobuf REQUIRED)

find_package(Hangish REQUIRED)

find_package(Qt5 REQUIRED COMPONENTS Core DBus Network Xml)

include(GNUInstallDirs)

set(hanging_SOURCES
    main.cpp
    connection.cpp
    protocol.cpp
    hangingtextchannel.cpp
)

add_executable(telepathy-hanging ${hanging_SOURCES})

set_target_properties(telepathy-hanging PROPERTIES AUTOMOC TRUE)

target_include_directories(telepathy-hanging PRIVATE
    ${TELEPATHY_QT5_INCLUDE_DIR}
    ${PROTOBUF_INCLUDE_DIRS}
    ${HANGISH_INCLUDE_DIR}
)

target_link_libraries(telepathy-hanging
    Qt5::Core
    Qt5::DBus
    Qt5::Network
    ${TELEPATHY_QT5_LIBRARIES}
    ${TELEPATHY_QT5_SERVICE_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    ${HANGISH_LIBRARIES}
)

configure_file(hanging.service.in org.freedesktop.Telepathy.ConnectionManager.hanging.service)

install(
    TARGETS telepathy-hanging
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/telepathy
)

install(
    FILES hanging.manager
    DESTINATION share/telepathy/managers
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/org.freedesktop.Telepathy.ConnectionManager.hanging.service
    DESTINATION share/dbus-1/services
)
