# Define target name
set (TARGET_NAME stb)

# Define source files
file (GLOB C_FILES *.c)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})

# Setup target
setup_library ()
