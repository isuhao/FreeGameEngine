
##################################################
###
##################################################
set(SOURCES
	util core math graphics platform script
)

foreach(TARGET_NAME ${SOURCES})
	add_subdirectory(${TARGET_NAME})
endforeach()

foreach(TARGET_NAME util core math graphics platform script)
	set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "engine")
endforeach()

#if(WIN32)
#	add_subdirectory (test/testmath)
#endif()
