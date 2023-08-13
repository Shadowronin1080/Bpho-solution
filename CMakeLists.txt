cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(RLIMGUI_DIR "${CMAKE_SOURCE_DIR}/build/include/rlimgui")
set(NUMPY_DIR "${CMAKE_SOURCE_DIR}/build/include/numpy/core")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/build/include")
set(HEADERS src/main.h )
set(CMAKE_PREFIX_PATH "C:/root_v6.28.04")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:__cplusplus")

project(bpho VERSION 0.1.0 LANGUAGES C CXX)

add_executable(bpho src/main.cpp ${HEADERS})


find_package(OpenGL)
find_package(Boost COMPONENTS filesystem iostreams)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
target_link_libraries(bpho PRIVATE OpenSSL::SSL OpenSSL::Crypto)
find_package(sciplot CONFIG REQUIRED)

find_package(GSL REQUIRED)
target_link_libraries(bpho PRIVATE GSL::gsl GSL::gslcblas)

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/build/include/imgui")

add_library( imgui 
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp 
    ${IMGUI_DIR}/imgui_draw.cpp 
    ${IMGUI_DIR}/imgui_tables.cpp 
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imGui_stdlib.cpp
    ${IMGUI_DIR}/imgui-knobs.cpp


)
target_include_directories("imgui" PRIVATE ${IMGUI_DIR})
target_include_directories(bpho PRIVATE ${IMGUI_DIR})
target_link_libraries(imgui PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE "imgui")


#rlimgui
set(IMPLOT_DIR "${CMAKE_SOURCE_DIR}/build/include/implot")
add_library( implot 
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp 
)
target_include_directories(implot PRIVATE ${IMPLOT_DIR}  ${IMGUI_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMPLOT_DIR} ${InCLUDE_DIR})
target_link_libraries("implot" PRIVATE "imgui")
target_link_libraries(${PROJECT_NAME} PRIVATE "implot")

target_link_libraries(${PROJECT_NAME} PRIVATE  glfw opengl32 imgui sciplot::sciplot Boost::boost Boost::iostreams Boost::filesystem) 









