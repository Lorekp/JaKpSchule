#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "tgui" for configuration "Debug"
set_property(TARGET tgui APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(tgui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tgui-s-d.lib"
  )

list(APPEND _cmake_import_check_targets tgui )
list(APPEND _cmake_import_check_files_for_tgui "${_IMPORT_PREFIX}/lib/tgui-s-d.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
