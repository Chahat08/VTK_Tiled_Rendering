# CMakeList.txt : CMake project for VTK_Basic, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (VTK_Basic "VTK_Basic.cpp" "VTK_Basic.h")

target_link_libraries(VTK_Basic PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
	TARGETS VTK_Basic
	MODULES ${VTK_LIBRARIES}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET VTK_Basic PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

