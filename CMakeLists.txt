# Copyright (C) 2018 Tomasz Gałaj

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(Starlight)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# Configure assets header file
configure_file(src/engine/helpers/RootDir.h.in src/engine/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/src)

file(GLOB IMGUI_SOURCES imgui/*.cpp imgui/*.h)
	
# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES}
		src/starlight.h
		src/starlight.h
        src/engine/models/RawModel.cpp
        src/engine/models/RawModel.h
        src/engine/renderer/Loader.cpp
        src/engine/renderer/Loader.h
        src/engine/renderer/Renderer.cpp
        src/engine/renderer/Renderer.h
        src/engine/utils/Math.cpp
        src/engine/utils/Math.h
        src/engine/textures/Texture.cpp
        src/engine/textures/Texture.h
        src/engine/models/Model.cpp
        src/engine/models/Model.h
        src/engine/shaders/ShaderProgram.cpp
        src/engine/shaders/ShaderProgram.h
        src/engine/shaders/StaticShader.cpp
        src/engine/shaders/StaticShader.h
        src/engine/entities/Camera.cpp
        src/engine/entities/Camera.h
        src/engine/entities/Entity.cpp
        src/engine/entities/Entity.h
        src/engine/entities/Lighting.cpp
        src/engine/entities/Lighting.h
        src/engine/utils/LogUtils.cpp
        src/engine/utils/LogUtils.h
		${IMGUI_SOURCES}
		imgui/backends/imgui_impl_glfw.cpp
		imgui/backends/imgui_impl_glfw.h
		imgui/backends/imgui_impl_opengl3.cpp
		imgui/backends/imgui_impl_opengl3.h
        src/engine/editor/Editor.cpp
        src/engine/editor/Editor.h
        src/engine/utils/AssetServer.cpp
        src/engine/utils/AssetServer.h
        src/engine/utils/ECS.cpp
        src/engine/utils/ECS.h
		src/engine/engine.cpp
		src/engine/engine.h
		src/engine/engine.h
        src/game/barbarian/Attack.cpp
        src/game/barbarian/Attack.h
		src/game/barbarian/Barbarian.cpp
		src/game/barbarian/Barbarian.h)

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#######################################
# LOOK for the packages that we need! #
#######################################

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# ASSIMP
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

# STB_IMAGE
add_library(STB_IMAGE "thirdparty/stb_image.cpp")

# GLAD
add_library(GLAD "thirdparty/glad.c")

# ReactPhysics3D
find_package(RP3D REQUIRED)
message(STATUS "Found ReactPhysics in ${RP3D_INCLUDE_DIR}")
# Put all libraries into a variable
set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} GLAD ${CMAKE_DL_LIBS} ${ASSIMP_LIBRARY} ${RP3D_LIBRARY} STB_IMAGE)

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/include/glad"
	"${CMAKE_SOURCE_DIR}/include/glm"
)

# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})

# Create virtual folders to make it look nicer in VS
if(MSVC_IDE)
	# Macro to preserve source files hierarchy in the IDE
	macro(GroupSources curdir)
		file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

		foreach(child ${children})
			if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
				GroupSources(${curdir}/${child})
			else()
				string(REPLACE "/" "\\" groupname ${curdir})
				string(REPLACE "src" "Sources" groupname ${groupname})
				source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			endif()
		endforeach()
	endmacro()

	# Run macro
	GroupSources(src)
endif()

# Copy dlls
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/dlls"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# Copy assets and shaders
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${PROJECT_SOURCE_DIR}/res"
			"$<TARGET_FILE_DIR:${PROJECT_NAME}>/res")
endif()
