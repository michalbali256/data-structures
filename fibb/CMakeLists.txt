cmake_minimum_required(VERSION 3.9)


add_subdirectory(fibb)
add_subdirectory(generator)

#if(NOT DEFINED MAXMEMORY)
#	set(MAXMEMORY 100)
#endif()
### RESULTS ###
##### time measurement #####
#add_custom_command(
#	OUTPUT res_time_naive
#	COMMAND transp -n -m ${MAXMEMORY} > res_time_naive
#	DEPENDS transp
#	)

#add_custom_command(
#	OUTPUT res_time_obl
#	COMMAND transp -m ${MAXMEMORY} > res_time_obl
#	DEPENDS transp
#	)

#add_custom_target(results_time ALL DEPENDS res_time_naive res_time_obl)