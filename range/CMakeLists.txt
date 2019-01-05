cmake_minimum_required(VERSION 3.9)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(range)
add_subdirectory(generator)

set(STUDENT_ID 72)

add_custom_command(
	OUTPUT q.in
	COMMAND generator -s ${STUDENT_ID} -q > q.in
	DEPENDS generator
	)

add_custom_command(
	OUTPUT u.in
	COMMAND generator -s ${STUDENT_ID} -u > u.in
	DEPENDS generator
	)

add_custom_command(
	OUTPUT res_u
	COMMAND range < u.in > res_u
	DEPENDS range u.in
	)

add_custom_command(
	OUTPUT res_q
	COMMAND range < q.in > res_q
	DEPENDS range q.in
	)

add_custom_target(results DEPENDS res_q res_u)

add_custom_command(
	OUTPUT 1.pdf
	COMMAND python3 ${PROJECT_SOURCE_DIR}/plot.py
	DEPENDS results ${PROJECT_SOURCE_DIR}/plot.py
	)
add_custom_target(plots ALL DEPENDS 1.pdf)

#add_custom_command(
#	OUTPUT res_time_obl
#	COMMAND transp -m ${MAXMEMORY} > res_time_obl
#	DEPENDS transp
#	)

#add_custom_target(results_time ALL DEPENDS res_time_naive res_time_obl)