cmake_minimum_required(VERSION 3.5.1)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)
	
project(App_Engine LANGUAGES CXX)

#create vars for SDL libs:
if(UNIX)
	set(SDL2_image_name SDL2_image)
	set(SDL2_ttf_name SDL2_ttf)
	set(SDL2_mixer_name SDL2_mixer)
elseif(WIN32 OR APPLE)
	set(SDL2_image_name SDL2_IMAGE)
	set(SDL2_ttf_name SDL2_TTF)
	set(SDL2_mixer_name SDL2_MIXER)
endif()

find_package(SDL2 REQUIRED)
find_package(${SDL2_image_name} REQUIRED)
find_package(${SDL2_ttf_name} REQUIRED)
find_package(${SDL2_mixer_name} REQUIRED)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
	${PROJECT_NAME} 
		${_BASE_DIR}/common/CommonDefines.h

		${_BASE_DIR}/engine/Engine.h
		${_BASE_DIR}/engine/Engine.cpp
		${_BASE_DIR}/engine/EngineConfigLoader.h
		${_BASE_DIR}/engine/EngineConfigLoader.cpp
		${_BASE_DIR}/engine/config/EngineConfig.h

		${_BASE_DIR}/game/Game.h
		${_BASE_DIR}/game/Game.cpp
		${_BASE_DIR}/game/config/GameCfg.h

		${_BASE_DIR}/main.cpp
)

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})

target_include_directories(
	${PROJECT_NAME}
		PRIVATE
			${_BASE_DIR}
)

target_link_libraries(
	${PROJECT_NAME}
		PRIVATE
			sdl_utils
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