# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
set(project_name "zone")
# 项目信息
project (${project_name} CXX)

configure_file("version.h.in" "${PROJECT_SOURCE_DIR}/version.h")

# include directories
INCLUDE_DIRECTORIES(after  ./)
INCLUDE_DIRECTORIES(after  ./Mgr/)
INCLUDE_DIRECTORIES(after  ./DynamicCfg/)
INCLUDE_DIRECTORIES(after  ./StaticCfg/)
INCLUDE_DIRECTORIES(after  ./Scene/)
INCLUDE_DIRECTORIES(after  ./Com/)
INCLUDE_DIRECTORIES(after  ./Actor/)
INCLUDE_DIRECTORIES(after  ./Monster/)
INCLUDE_DIRECTORIES(after  ./Player/)
INCLUDE_DIRECTORIES(after  ./Client/)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
file(GLOB_RECURSE SRCS  ${PROJECT_SOURCE_DIR} "*.cpp"
"../dbProto/*.cpp"
"../com/*.cpp"
"../cppProto/*.cpp"
"../external/cpp_cfg/com/*.cpp"
)


# 指定生成目标
ADD_EXECUTABLE(${project_name} ${SRCS})
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/Zone1)
#设置依赖
#ADD_DEPENDENCIES(db_driver svr_util libevent_cpp)

# 设置链接库,顺序有要求。高层的引用方前面。最底层的方后面
target_link_libraries(${project_name} acc_driver acc_proto )
target_link_libraries(${project_name} db_driver.a)
target_link_libraries(${project_name} svr_util libcevent_cpp.a)
set_target_properties(zone PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
cotire(zone)
    
