include(CTest)
add_executable(test_read test_read.cpp )
add_executable(test_convert_to_admitted test_convert_to_admitted.cpp )
add_executable(test_verify_assumption test_verify_assumption.cpp )
add_executable(test_heuristics1 test_heuristics1.cpp )
add_executable(test_heuristics2 test_heuristics2.cpp )

target_link_libraries(test_read board)
target_link_libraries(test_convert_to_admitted board)
target_link_libraries(test_heuristics1 board)
target_link_libraries(test_heuristics2 board)
target_link_libraries(test_verify_assumption board)


configure_file(../example_tables/table1.txt ${CMAKE_CURRENT_BINARY_DIR}/table1.txt)
configure_file(output_table1.txt ${CMAKE_CURRENT_BINARY_DIR}/output_table1.txt)
configure_file(../example_tables/table2.txt ${CMAKE_CURRENT_BINARY_DIR}/table2.txt)
configure_file(output_table2.txt ${CMAKE_CURRENT_BINARY_DIR}/output_table2.txt)

add_test(test_read_ex1 test_read table1.txt ) 
add_test(test_convert_to_admitted test_convert_to_admitted table1.txt ) 

add_test(test_heuristics1_1 test_heuristics1 table1.txt output_table1.txt ) 
add_test(test_heuristics1_2 test_heuristics1 table2.txt output_table2.txt ) 

add_test(test_heuristics2_1 test_heuristics2 table1.txt output_table1.txt ) 
add_test(test_heuristics2_2 test_heuristics2 table2.txt output_table2.txt ) 

add_test(test_verify_assumption1 test_verify_assumption table1.txt output_table1.txt ) 
add_test(test_verify_assumption1 test_verify_assumption table2.txt output_table2.txt ) 
