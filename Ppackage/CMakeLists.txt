cmake_minimum_required(VERSION 3.16)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 17)

# start 以下是打开QT的MOC功能，UI文件处理功能和RCC
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# end

#设置路径
set(Qt5Widgets_DIR /opt/Qt5.9.9/5.9.9/gcc_64/lib/cmake/Qt5Widgets)
#找QT库
find_package(Qt5Widgets REQUIRED NO_DEFAULT_PATH)
#找thread库 thread不是c的标准库
find_package(Threads REQUIRED)

# 配置链接库的库所在路径，主要需要放在exe之前
link_directories(E:/CLionProjects/HelloWorld/cmake-build-debug)

# start 以下是项目本身自己编成的静态链接库的目录（注意下面有各自的CMakeLists.txt文件），目的是提高编译速度，如果没有修改过内容，再次编译的时候直接跳过
add_subdirectory(cache)
add_subdirectory(rpc)
add_subdirectory(util)
# CMakeLists.txt文件内容例如
aux_source_directory(. DIR_RPC_SOURCE)

add_subdirectory(view)
# 又一层
# 内容例如
aux_source_directory(. DIR_RPC_VIEW)
add_library(RPC_VIEW ${DIR_RPC_VIEW})

add_library(RPC ${DIR_RPC_SOURCE})
target_link_libraries(RPC RPC_VIEW)
# end

add_executable(HelloWorld main.cpp readme_file.cpp configuration.h system.cpp system.h json.cpp json.h)
# 注此为创建可执行程序结果为HelloWorld.exe(sh)既可以创建多个

# 添加非标准库
target_link_libraries(Battle pthread)
# 添加项目中使用到的库 自定或引用
# 注意多级目录情况下，使用add library与target link library时
# 不要使用外部需要link的库，不然会出现not found情况
# 目录的层数最好区别开来一级XX二级XX_XX三级XX_XX_XX，link下以名称来区分，存在同名问题
# link一串中的先后顺序，也会出现not define的情况
# 循环引用问题，一定要注意
# 其中需要额外说明的是外部link库与循环引用问题可以在局部地方再细节link，但因为有顺序问题，可能会出现其他错误，还是老老实实在add executable中写一下比较好，可以只写有问题的文件
target_link_libraries(Battle Qt5::Widgets CACHE RPC UTIL)

# start 以下配置可以将项目打包成一个动态链接库
set(LIB_NAME t_sys)
set(SRC_LIB_CODE readme_file.cpp configuration.h system.cpp system.h json.cpp json.h)
add_library(t_sys SHARED ${SRC_LIB_CODE})
# end 注意动态链接库的注意事项，不仅配了link路径还需要在exe目录下加上库

# 配置链接库的库文件和头文件
target_link_libraries(TestLib t_sys)
target_include_directories(TestLib PUBLIC E:/CLionProjects/HelloWorld)
