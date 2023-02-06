if(NOT DEFINED CMAKE_MINIMUM_REQUIRED_VERSION)
   cmake_minimum_required(VERSION 3.12)
   project(DTDataGlove)
   find_package(YARP REQUIRED COMPONENTS os)
 endif()

 add_executable(extractor)
 target_sources(extractor PRIVATE extractor.cpp)
 target_link_libraries(extractor
   PRIVATE
     YARP::YARP_os
     YARP::YARP_init
     fglove
 )
