cmake_minimum_required(VERSION 3.16)

project(LumiQt	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(QtScriptNetworkEditor)
add_subdirectory(QtScriptNetworkRunner)
add_subdirectory(Common)

#target_link_libraries(QtScriptNetworkEditor PRIVATE Common)
#target_link_libraries(QtScriptNetworkRunner PRIVATE Common)
