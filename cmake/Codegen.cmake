if (NOT DEFINED GEODE_TARGET_PLATFORM)
	message(FATAL_ERROR "GEODE_TARGET_PLATFORM is not defined")
endif()
if (NOT DEFINED GEODE_BINDING_PATH)
	message(FATAL_ERROR "GEODE_BINDING_PATH is not defined")
endif()
if (NOT DEFINED GEODE_CODEGEN_DIR)
	set(GEODE_CODEGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/codegen)
	message("Using current binary dir for GEODE_CODEGEN_DIR, which is ${CMAKE_CURRENT_BINARY_DIR}/codegen")
endif()

add_custom_target(CodegenRun ALL
	COMMAND Codegen ${GEODE_TARGET_PLATFORM} ${GEODE_BINDING_PATH} ${GEODE_CODEGEN_DIR}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Run Codegen"
)

add_dependencies(CodegenRun Codegen)