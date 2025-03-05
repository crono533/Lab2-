# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (POLICY CMP0079)
  cmake_policy(SET CMP0079 NEW)
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("AllocatorLab2")

# Указываем путь к папке с аллокатором
add_subdirectory(external/Allocator)

# Включите подпроекты.
add_subdirectory ("AllocatorConsoleApp")


# Подключаем заголовочные файлы
include_directories(external/Allocator) 


# Добавляем библиотеку Allocator к нашему проекту
target_link_libraries(AllocatorConsoleApp PRIVATE Allocator)
