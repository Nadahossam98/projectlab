# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Hospital_Patient_Management_system_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Hospital_Patient_Management_system_autogen.dir\\ParseCache.txt"
  "Hospital_Patient_Management_system_autogen"
  )
endif()
