cmake_minimum_required(VERSION 3.0.2)
project(Tugas_Aksan)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES Tugas_Aksan
 CATKIN_DEPENDS roscpp std_msgs
 DEPENDS system_lib
)


include_directories(include ${catkin_INCLUDE_DIRS}) 

add_executable(talker src/talker.cpp)
target_link_libraries (talker ${catkin_LIBRARIES})

add_executable(listener src/listener.cpp)
target_link_libraries (listener ${catkin_LIBRARIES})

add_executable(turtletest src/turtletest.cpp)
target_link_libraries (turtletest ${catkin_LIBRARIES})