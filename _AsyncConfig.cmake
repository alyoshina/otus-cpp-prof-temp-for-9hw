add_library(async SHARED IMPORTED)
find_library(ASYNC_LIBRARY_PATH async HINTS "${CMAKE_CURRENT_LIST_DIR}/../../")
set_target_properties(async PROPERTIES IMPORTED_LOCATION "${ASYNC_LIBRARY_PATH}")