# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WorkplaceMonitor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WorkplaceMonitor_autogen.dir\\ParseCache.txt"
  "WorkplaceMonitor_autogen"
  )
endif()
