cmake_minimum_required(VERSION 3.17)
project(LTYunClient
    VERSION 1.0.0
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/ImSordayne/LTYunClient
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_SOURCES
    src/main.cpp
)

if(WIN32)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.rc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/icon.rc"
        @ONLY
    )
    list(APPEND APP_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/icon.rc")
endif()

if(APPLE)
    set_source_files_properties(
        "${CMAKE_CURRENT_SOURCE_DIR}/res/LTYunLogo.icns"
        PROPERTIES MACOSX_PACKAGE_LOCATION "Resources"
    )
    list(APPEND APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/res/LTYunLogo.icns")
endif()

add_executable(LTYunClient ${APP_SOURCES})

find_package(webview REQUIRED)
target_link_libraries(LTYunClient PRIVATE webview::core)

if(APPLE)
    set_target_properties(LTYunClient PROPERTIES
        MACOSX_BUNDLE                       TRUE
        MACOSX_BUNDLE_BUNDLE_NAME           "LTYunClient"
        MACOSX_BUNDLE_GUI_IDENTIFIER        "com.ltyun.client"
        MACOSX_BUNDLE_BUNDLE_VERSION        "${PROJECT_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING  "${PROJECT_VERSION}"
        MACOSX_BUNDLE_ICON_FILE             "LTYunLogo.icns"
    )
endif()

if(UNIX AND NOT APPLE)

    set(APPDIR       "${CMAKE_BINARY_DIR}/LTYunClient.AppDir")
    set(DESKTOP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/res/LTYunClient.desktop")
    set(ICON_FILE    "${CMAKE_CURRENT_SOURCE_DIR}/res/LTYunLogo.png")

    if(LINUXDEPLOY_EXECUTABLE)
        add_custom_target(appimage
            COMMAND ${CMAKE_COMMAND} -E rm -rf "${APPDIR}"
            COMMAND "${LINUXDEPLOY_EXECUTABLE}"
                    --appdir       "${APPDIR}"
                    --executable   "$<TARGET_FILE:LTYunClient>"
                    --desktop-file "${DESKTOP_FILE}"
                    --icon-file    "${ICON_FILE}"
                    --output       appimage
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
            DEPENDS LTYunClient
            COMMENT "使用 linuxdeploy 生成 AppImage"
            VERBATIM
        )
    else()
        message(WARNING
            "未找到 linuxdeploy")
    endif()
endif()

install(TARGETS LTYunClient
    RUNTIME DESTINATION bin
    BUNDLE  DESTINATION .
)

if(UNIX AND NOT APPLE)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/res/LTYunClient.desktop"
        DESTINATION share/applications
    )
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/res/LTYunLogo.png"
        DESTINATION share/icons/hicolor/256x256/apps
        RENAME LTYunClient.png
    )
endif()
