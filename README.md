# Lab2-
1)Папка Allocator_Integrated_and_time_duration содержит проект без интеграции аллокатора и замером времени работы программы, нужна для сравнения времени работы с проектом в папке Allocator_Integration_and_time_duration_to_compare, для анализа SAST и после сборки:
 1. cmake ..
 2. cmake --build .

можно исполняемый файл передать DAST valgrind.

2) Папка Allocator_Integration_and_time_duration_to_compare содержит проект с интегрированным аллокатором и замером времени работы программы. Также есть анализ SAST и после сборки:
 1. cmake ..
 2. cmake --build .

можно исполняемый файл передать DAST valgrind.