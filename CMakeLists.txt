cmake_minimum_required(VERSION 3.5.0)
project(ProgLaba3 VERSION 0.1.0)

# Определение версий
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

add_executable(ProgLaba3 main.cpp)

# CPack
set(CPACK_PROJECT_NAME ProgLaba3)
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT example@example.com)
set(CPACK_PACKAGE_VENDOR "Your Company")

# Зависимости для Linux (DEB)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
 set(CPACK_GENERATOR DEB)
 set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtk-3-dev libstdc++6-dev")
endif()

# Зависимости для macOS (ZIP)
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
 set(CPACK_GENERATOR ZIP)
endif()

include(CPack)

# Установка файлов в пакет 
install(TARGETS ProgLaba3 RUNTIME DESTINATION bin)
install(FILES README.md LICENSE DESTINATION doc)
install(DIRECTORY include DESTINATION include)
