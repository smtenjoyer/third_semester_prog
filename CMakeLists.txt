cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION}) # Исправлено на 'PROJECT_VERSION'

project(helloworld VERSION ${PROJECT_VERSION})

# Обязательно укажите пакет Boost с компонентом unit_test_framework
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Настройте файл версии
configure_file(version.h.in version.h)

# Добавление исполняемых файлов и библиотеки
add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp)

# Установка стандартов C++
set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Добавление директории для выборки библиотеки
target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# Установка определений компиляции для тестов
target_compile_definitions(test_version PRIVATE BOOST_TEST_DYN_LINK)
target_include_directories(test_version PRIVATE ${Boost_INCLUDE_DIR})

# Связывание библиотек
target_link_libraries(helloworld_cli PRIVATE
    helloworld
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    helloworld
)

# Установка параметров компиляции
if (MSVC)
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else ()
    target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(helloworld PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Установка для установки
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

# Настройки CPack для создания пакетов
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

# Включение тестирования
enable_testing()

# Добавление теста
add_test(NAME test_version COMMAND test_version)
