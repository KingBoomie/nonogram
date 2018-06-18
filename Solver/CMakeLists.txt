# CMakeList.txt : CMake project for Solver, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

find_package(imgui CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package (OpenGL REQUIRED)
    
	
message ("${GLEW_LIBRARY}") 
# Add source to this project's executable.
add_executable (Solver 
	"Solver.cpp" 
	"Solver.h" 
	"gui/imgui_impl_sdl_gl3.cpp"
	"gui/imgui_impl_sdl_gl3.h")


target_compile_features(Solver PRIVATE cxx_std_17)
target_link_libraries(Solver PRIVATE GLEW::GLEW imgui::imgui SDL2::SDL2 SDL2::SDL2main OpenGL32)

set_target_properties(Solver PROPERTIES LINKER_LANGUAGE CXX)

# TODO: Add tests and install targets if needed.
