# Build and install the library
add_library( String2Ops SHARED)
target_compile_definitions( String2Ops PRIVATE STRING2_BUILD_NODEDEF_DLL )
target_sources( String2Ops PRIVATE String2.cpp)
target_link_libraries( String2Ops PUBLIC Amino::Cpp )
target_link_libraries( String2Ops PUBLIC Amino::Core )
bifrost_set_install_rpath(String2Ops)
install( TARGETS String2Ops DESTINATION lib )

# Generate and install the json files
set( headers_to_parse
    String2.h
)

bifrost_header_parser(
    String2JsonFiles  # Name of the target.
    "json/${PROJECT_NAME}" # Install and build dirs - relative to install prefix
                           # and build directory
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    HEADER_FILES ${headers_to_parse})

# Create config json file to load the bifrost pack
set( CONFIG_PACK_VERSION "${PROJECT_VERSION}")
set( CONFIG_PACK_NAME "${PROJECT_NAME}")
set( CONFIG_SHARED_LIBS "./lib")
set( CONFIG_JSON_FILES "./json/${PROJECT_NAME}")
set( config_json ${CMAKE_BINARY_DIR}/${PROJECT_NAME}PackConfig.json )
configure_file(PackConfig.json.in ${config_json} )
install(FILES ${config_json} DESTINATION . )

# copy compounds to final pack location
file(GLOB STRING2_COMPOUNDS ${CMAKE_SOURCE_DIR}/compounds/*.json)
install(
    COPY ${STRING2_COMPOUNDS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/json/${PROJECT_NAME}
)
