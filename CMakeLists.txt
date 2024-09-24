cmake_minimum_required(VERSION 3.6) # Устанавливает минимальную версию CMake, необходимую для этого проекта.
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
# Создает переменные PATCH_VERSION и PROJECT_VESRION для управления версиями проекта.

project(ip_check VERSION ${PROJECT_VESRION}) # Определяет имя проекта ip_check и использует переменную PROJECT_VESRION для указания версии проекта.
add_executable(ip_check ip_filter.cpp ip_filter.h)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)


set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

set(CPACK_PROJECT_NAME ip_check)

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

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing() # Включает тестирование

add_subdirectory(gtests)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})