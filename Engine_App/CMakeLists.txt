cmake_minimum_required(VERSION 3.5.1)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)
	
project(App_Engine LANGUAGES CXX)

set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
	${PROJECT_NAME} 
		${_INC_DIR}/common/CommonDefines.h
		${_INC_DIR}/engine/Engine.h
		${_INC_DIR}/engine/EngineConfigLoader.h
		${_INC_DIR}/engine/config/EngineConfig.h
		${_INC_DIR}/game/Game.h
		${_INC_DIR}/game/config/GameCfg.h
		${_INC_DIR}/game/entities/Hero.h

		${_SRC_DIR}/engine/Engine.cpp
		${_SRC_DIR}/engine/EngineConfigLoader.cpp
		${_SRC_DIR}/game/Game.cpp
		${_SRC_DIR}/game/entities/Hero.cpp
		${_SRC_DIR}/main.cpp
)

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})

target_include_directories(
	${PROJECT_NAME}
		PRIVATE
			${_INC_DIR}
)

target_link_libraries(
	${PROJECT_NAME}
		PRIVATE
			manager_utils
)

if(CMAKE_BUILD_TYPE MATCHES Release)
	target_compile_definitions(
		${PROJECT_NAME} 
			PRIVATE 
				-DRELEASE_BUILD=1) #create own pre-proccessor directive

	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_CURRENT_SOURCE_DIR}/resources/
				$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/
	)
endif()

add_subdirectory(utils)
add_subdirectory(sdl_utils)
add_subdirectory(manager_utils)