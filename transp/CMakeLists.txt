cmake_minimum_required(VERSION 3.11)
find_package(PythonInterp)


add_subdirectory(transp)
add_subdirectory(simulator)

if(NOT DEFINED MAXMEMORY)
	set(MAXMEMORY 100)
endif()
### RESULTS ###
##### time measurement #####
add_custom_command(
	OUTPUT res_time_naive
	COMMAND transp -n -m ${MAXMEMORY} > res_time_naive
	DEPENDS transp
	)

add_custom_command(
	OUTPUT res_time_obl
	COMMAND transp -m ${MAXMEMORY} > res_time_obl
	DEPENDS transp
	)

add_custom_target(results_time ALL DEPENDS res_time_naive res_time_obl)

##### simulator inputs #####
add_custom_command(
	OUTPUT res_sim_naive
	COMMAND transp -s -n -m 120 > res_sim_naive
	DEPENDS transp
	)

add_custom_command(
	OUTPUT res_sim_obl
	COMMAND transp -s -m 120 > res_sim_obl
	DEPENDS transp
	)


add_custom_target(sim_input ALL DEPENDS res_sim_naive res_sim_obl)

##### simulator run #####
foreach(NAIVE_OBL naive obl)
add_custom_command(
	OUTPUT res_${NAIVE_OBL}_0064_0064
	COMMAND simulator 64 64 < res_sim_${NAIVE_OBL} > res_${NAIVE_OBL}_0064_0064
	DEPENDS simulator res_sim_${NAIVE_OBL}
	)
add_custom_command(
	OUTPUT res_${NAIVE_OBL}_0064_1024
	COMMAND simulator 64 1024 < res_sim_${NAIVE_OBL} > res_${NAIVE_OBL}_0064_1024
	DEPENDS simulator res_sim_${NAIVE_OBL}
	)
add_custom_command(
	OUTPUT res_${NAIVE_OBL}_0064_4096
	COMMAND simulator 64 4096 < res_sim_${NAIVE_OBL} > res_${NAIVE_OBL}_0064_4096
	DEPENDS simulator res_sim_${NAIVE_OBL}
	)
add_custom_command(
	OUTPUT res_${NAIVE_OBL}_0512_0512
	COMMAND simulator 512 512 < res_sim_${NAIVE_OBL} > res_${NAIVE_OBL}_0512_0512
	DEPENDS simulator res_sim_${NAIVE_OBL}
	)
add_custom_command(
	OUTPUT res_${NAIVE_OBL}_4096_0064
	COMMAND simulator 4096 64 < res_sim_${NAIVE_OBL} > res_${NAIVE_OBL}_4096_0064
	DEPENDS simulator res_sim_${NAIVE_OBL}
	)
endforeach()

add_custom_target(results_simulator DEPENDS res_naive_0064_0064 res_naive_0064_1024 res_naive_0064_4096 res_naive_0512_0512 res_naive_4096_0064
                                                res_obl_0064_0064 res_obl_0064_1024 res_obl_0064_4096 res_obl_0512_0512 res_obl_4096_0064)

add_custom_command(
	OUTPUT sim.pdf
	COMMAND python ${PROJECT_SOURCE_DIR}/plot_sim.py
	DEPENDS results_simulator ${PROJECT_SOURCE_DIR}/plot_sim.py
	)

add_custom_target(sim_plot ALL DEPENDS sim.pdf)

add_custom_command(
	OUTPUT time.pdf
	COMMAND python ${PROJECT_SOURCE_DIR}/plot_time.py
	DEPENDS results_time ${PROJECT_SOURCE_DIR}/plot_time.py
	)

add_custom_target(time_plot ALL DEPENDS time.pdf)

add_custom_command(
	OUTPUT sim.pdf
	COMMAND python ${PROJECT_SOURCE_DIR}/plot_sim.py
	DEPENDS results_simulator ${PROJECT_SOURCE_DIR}/plot_sim.py
	)