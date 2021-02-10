cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----
project(
	Pixie16
	VERSION 8.23.0
	LANGUAGES C)

# ---- Options ----

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info
include(cmake/CPM.cmake)

CPMAddPackage(
		NAME PackageProject.cmake
		GITHUB_REPOSITORY TheLartians/PackageProject.cmake
		VERSION 1.4
)



add_library(Pixie16 STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/pixie16/communication.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/pixie16/i2cm24c64.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/pixie16/pixie16app.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/pixie16/pixie16sys.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/pixie16/tools.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/pixie16/utilities.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/plx/Aardvark.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/plx/Eep_8000.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/plx/I2cAaUsb.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/plx/MdioSpliceUsb.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/plx/PlxApi.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/plx/PlxApiDirect.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/plx/SdbComPort.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/plx/SpiFlash.c)

target_include_directories(Pixie16
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>)

target_compile_definitions(Pixie16 PUBLIC PLX_LITTLE_ENDIAN PCI_CODE PLX_LINUX)

target_link_libraries(Pixie16 PUBLIC ldl lrt lm)


set_property(TARGET Pixie16 PROPERTY POSITION_INDEPENDENT_CODE ON)
add_library(Pixie16::Pixie16 ALIAS Pixie16)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
		NAME ${PROJECT_NAME}
		VERSION ${PROJECT_VERSION}
		NAMESPACE ${PROJECT_NAME}
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
		INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
		VERSION_HEADER "${VERSION_HEADER_LOCATION}"
		DEPENDENCIES ""
)