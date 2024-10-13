cmake_minimum_required(VERSION 3.5.0)
project(ProgLaba3 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ProgLaba3 main.cpp )

include(CTest)
enable_testing()

# Установка пакета DEB для Linux
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CPACK_GENERATOR DEB) # Настраивает CPack для создания пакетов DEB (Linux).
    # Укажите зависимости пакета
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtk-3-dev libstdc++6-dev")
endif()
# Установка пакета ZIP для macOS
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CPACK_GENERATOR ZIP) # Настройка CPack для создания пакетов ZIP (macOS)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
