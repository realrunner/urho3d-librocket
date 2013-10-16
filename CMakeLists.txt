# Define target name
set (TARGET_NAME libRocket)

# Define source files
file (GLOB CPP_FILES Source/Controls/*.cpp Source/Core/*.cpp Source/Core/*.inl Source/Debugger/*.cpp Urho3DInterface/*.cpp)
file (GLOB_RECURSE H_FILES Include/Rocket *.h)
file (GLOB H_FILES2 Source/Controls/*.h Source/Core/*.h Source/Debugger/*.h Urho3DInterface/*.h )

set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${H_FILES2})

# Define dependency libs
set (LIBS ../FreeType/include)

set (INCLUDE_DIRS_ONLY Include)

# Setup target
setup_library ()
