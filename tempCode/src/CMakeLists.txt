# CMakeList.txt: BattleDesign 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


INCLUDE_DIRECTORIES(system ./svr_util_copy/)
INCLUDE_DIRECTORIES(after  ${PROJECT_SOURCE_DIR}/svr_util_copy/)

file(GLOB_RECURSE SRC  ${PROJECT_SOURCE_DIR} "./*.cpp")
file(GLOB_RECURSE SRC2  ${PROJECT_SOURCE_DIR} "./battle/**.cpp")

# 将源代码添加到此项目的可执行文件。
add_executable (BattleDesign ${SRC} ${SRC2})


# TODO: 如有需要，请添加测试并安装目标。
