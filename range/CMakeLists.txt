cmake_minimum_required(VERSION 3.9)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(range)
add_subdirectory(generator)

set(STUDENT_ID 72)

#add_custom_command(
#	OUTPUT p_naive_decrease_max p_naive_decrease_avg p_naive_delete_avg p_naive_delete_max
#	COMMAND \( \"$<TARGET_FILE:generator>\" -p -s ${STUDENT_ID} | \"$<TARGET_FILE:fibb>\" -n p \)
#	DEPENDS fibb generator
#	)

#add_custom_target(results DEPENDS r_stand_decrease_max b_stand_decrease_max x_stand_decrease_max
#x_naive_decrease_max p_stand_decrease_max p_naive_decrease_max)

#add_custom_command(
#	OUTPUT 1.pdf
#	COMMAND python3 ${PROJECT_SOURCE_DIR}/plot.py
#	DEPENDS results ${PROJECT_SOURCE_DIR}/plot.py
#	)
#add_custom_target(plots ALL DEPENDS 1.pdf)

#add_custom_command(
#	OUTPUT res_time_obl
#	COMMAND transp -m ${MAXMEMORY} > res_time_obl
#	DEPENDS transp
#	)

#add_custom_target(results_time ALL DEPENDS res_time_naive res_time_obl)