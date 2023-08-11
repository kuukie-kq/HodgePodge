cmake_minimum_required(VERSION 3.16)
project(Instrument)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-g)

aux_source_directory(./net SOURCE)
aux_source_directory(./plugin SOURCE)
aux_source_directory(./structure SOURCE)
aux_source_directory(./sys SOURCE)

add_executable(Instrument main.cpp ${SOURCE})

target_link_libraries(Instrument ws2_32.lib)

include(./test/CMakeLists.txt)

# cmake --build . --target package
#set(CPACK_GENERATOR "ZIP")
#set(CPACK_OUTPUT_FILE_PREFIX "dist")
#include(CPack)
# 打包成发行版，非正常zip软件解压即用的，废弃   直接zip压缩cmake-build-debug目录并添加第三方库（理论即可）
