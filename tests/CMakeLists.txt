include(CTest)
add_executable(test_read test_read.cpp ${SOURCES})
add_executable(test_convert_to_admitted test_convert_to_admitted.cpp ${SOURCES})
add_executable(test_heuristics1 test_heuristics1.cpp ${SOURCES})

configure_file(../example_tables/table1.txt ${CMAKE_CURRENT_BINARY_DIR}/table1.txt)
configure_file(output_table1.txt ${CMAKE_CURRENT_BINARY_DIR}/output_table1.txt)
configure_file(../example_tables/table2.txt ${CMAKE_CURRENT_BINARY_DIR}/table2.txt)
configure_file(output_table2.txt ${CMAKE_CURRENT_BINARY_DIR}/output_table2.txt)

add_test(test_read_ex1 test_read table1.txt ) 
add_test(test_convert_to_admitted test_convert_to_admitted table1.txt ) 
add_test(test_heuristics1_1 test_heuristics1 table1.txt output_table1.txt ) 
add_test(test_heuristics1_2 test_heuristics1 table2.txt output_table2.txt ) 
