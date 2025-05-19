# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "Business_logic\\Business_logic_autogen"
  "Business_logic\\CMakeFiles\\Business_logic_autogen.dir\\AutogenUsed.txt"
  "Business_logic\\CMakeFiles\\Business_logic_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\Expense_manager_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Expense_manager_autogen.dir\\ParseCache.txt"
  "Expense_manager_autogen"
  )
endif()
