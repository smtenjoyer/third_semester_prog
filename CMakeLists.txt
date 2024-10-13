include(CPack)
set(CPACK_GENERATOR ZIP) # Тип пакета
set(CPACK_PACKAGE_NAME ProgLaba3) # Имя пакета
set(CPACK_PACKAGE_VERSION 0.1.0) # Версия пакета

cmake_minimum_required(VERSION 3.5.0)
project(ProgLaba3 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ProgLaba3 main.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


install(TARGETS ProgLaba3 RUNTIME DESTINATION bin) # Устанавливает исполняемый файл
install(FILES README.md LICENSE DESTINATION doc) # Устанавливает дополнительные файлы
install(DIRECTORY include DESTINATION include) # Устанавливает заголовочные файлы
include(CPack)
