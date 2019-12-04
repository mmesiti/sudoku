include(CTest)
add_executable(test_read test_read.cpp )
add_executable(test_convert_to_admitted test_convert_to_admitted.cpp )
add_executable(test_verify_assumption test_verify_assumption.cpp )
add_executable(test_algorithm1 test_algorithm1.cpp )
add_executable(test_algorithm2 test_algorithm2.cpp )

target_link_libraries(test_read libcommon)
target_link_libraries(test_convert_to_admitted libcommon)
target_link_libraries(test_algorithm1 libcommon libalgo1)
target_link_libraries(test_algorithm2 libcommon libalgo2)
target_link_libraries(test_verify_assumption libcommon libalgo1)


configure_file(../example_tables/table1.txt ${CMAKE_CURRENT_BINARY_DIR}/table1.txt)
configure_file(output_table1.txt ${CMAKE_CURRENT_BINARY_DIR}/output_table1.txt)
configure_file(../example_tables/table2.txt ${CMAKE_CURRENT_BINARY_DIR}/table2.txt)
configure_file(output_table2.txt ${CMAKE_CURRENT_BINARY_DIR}/output_table2.txt)

add_test(test_read_ex1 test_read table1.txt ) 
add_test(test_convert_to_admitted test_convert_to_admitted table1.txt ) 

add_test(test_algorithm1_1 test_algorithm1 table1.txt output_table1.txt ) 
add_test(test_algorithm1_2 test_algorithm1 table2.txt output_table2.txt ) 

add_test(test_algorithm2_1 test_algorithm2 table1.txt output_table1.txt ) 
add_test(test_algorithm2_2 test_algorithm2 table2.txt output_table2.txt ) 

add_test(test_verify_assumption1 test_verify_assumption table1.txt output_table1.txt ) 
add_test(test_verify_assumption1 test_verify_assumption table2.txt output_table2.txt ) 
