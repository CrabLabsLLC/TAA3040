cmake_minimum_required(VERSION 3.16)

if(IDF_VERSION_MAJOR GREATER_EQUAL 4)

    idf_component_register(
        SRCS ./src/taa3040.c
        INCLUDE_DIRS ./include
    )

else()

    project(TAA3040 
        LANGUAGES C 
        VERSION 0.1
        DESCRIPTION "A platform agnostic driver for the TAA3040 Audio Interface IC")

    add_library(${PROJECT_NAME} STATIC src/taa3040.c)
    target_include_directories(${PROJECT_NAME} PUBLIC include)

endif()