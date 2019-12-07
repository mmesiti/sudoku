include(CTest)
add_executable(test_read test_read.cpp )
add_executable(test_convert_to_admitted test_convert_to_admitted.cpp )
add_executable(test_verify_assumption test_verify_assumption.cpp )
add_executable(test_algorithms test_algorithms.cpp )

target_link_libraries(test_read common)
target_link_libraries(test_convert_to_admitted common)
target_link_libraries(test_algorithms common algo1 algo2) 
target_link_libraries(test_verify_assumption common algo1)

configure_file(../example_tables/table1.txt ${CMAKE_CURRENT_BINARY_DIR}/table1.txt)
configure_file(output_table1.txt ${CMAKE_CURRENT_BINARY_DIR}/output_table1.txt)
configure_file(../example_tables/table2.txt ${CMAKE_CURRENT_BINARY_DIR}/table2.txt)
configure_file(output_table2.txt ${CMAKE_CURRENT_BINARY_DIR}/output_table2.txt)

add_test(test_read_ex1 test_read table1.txt ) 
add_test(test_convert_to_admitted test_convert_to_admitted table1.txt ) 

add_test(test_algorithms_11 test_algorithms table1.txt output_table1.txt 1) 
add_test(test_algorithms_12 test_algorithms table2.txt output_table2.txt 2) 

add_test(test_algorithms_21 test_algorithms table1.txt output_table1.txt 1) 
add_test(test_algorithms_22 test_algorithms table2.txt output_table2.txt 2) 

add_test(test_verify_assumption1 test_verify_assumption table1.txt output_table1.txt ) 
add_test(test_verify_assumption1 test_verify_assumption table2.txt output_table2.txt ) 
