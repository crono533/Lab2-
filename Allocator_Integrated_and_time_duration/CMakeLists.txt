cmake_minimum_required(VERSION 3.10)

# Если нужен MSVC hot reload (политика CMP0141), проверяем

project(AllocatorIntegrationConsoleApp)

# Подключаем библиотеку Allocator (папка externalAllocator/Allocator)
add_subdirectory(externalAllocator/Allocator)

# Подключаем проект sat_dpll (папка SAT_DPLL)
add_subdirectory(SAT_DPLL)

# include(/home/kali/Desktop/pvs-studio-7.35.89650.344-x86_64/lib/pvs-studio/plugins/pvs-studio-cmake-module/PVS-Studio.cmake)

# pvs_studio_add_target(TARGET sat_dpll.analyze ALL
#                       OUTPUT FORMAT json
#                       ANALYZE sat_dpll_app
#                       LOG sat_dpll.err)
