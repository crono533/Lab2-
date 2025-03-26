cmake_minimum_required(VERSION 3.10)
project(SAT_DPLL LANGUAGES CXX)
# ����� Qt
# ������� ���� �� Qt6Config.cmake
set(Qt6_DIR "/home/kali/Qt/6.8.2/gcc_64/lib/cmake/Qt6")  # ���� ������� � ����������� �� ����, ��� ���������� Qt
find_package(Qt6 REQUIRED COMPONENTS Core)
# �������� ��� cpp/h � SAT_DPLL
file(GLOB SAT_DPLL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# ������ ����������� ���� (�������� ��� ������, �������� sat_dpll_app)
add_executable(sat_dpll_app ${SAT_DPLL_SOURCES})

# ���������� include-����
target_include_directories(sat_dpll_app
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# ������� � ����� ����������� Allocator

target_link_libraries(sat_dpll_app PRIVATE Allocator Qt6::Core)