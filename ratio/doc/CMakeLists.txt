find_package (Doxygen)

message(VERBOSE "Doxigen settings :")
message(VERBOSE "ratio_SOURCE_DIR :  " ${ratio_SOURCE_DIR})
message(VERBOSE "ratio_BINARY_DIR :  " ${ratio_BINARY_DIR})
message(VERBOSE "DOXYGEN_EXECUTABLE :  " ${DOXYGEN_EXECUTABLE})

if(DOXYGEN_FOUND)
  configure_file (${ratio_SOURCE_DIR}/doc/Doxyfile-html.cmake ${ratio_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${ratio_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)
