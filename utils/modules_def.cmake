#GLOBAL INCLUDE
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
        GIT_PROGRESS TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)
enable_testing()

#DEFINITION
macro(defineModule MODULE)
    #LIBRARY
    file(
            GLOB_RECURSE sources
            LIST_DIRECTORIES true
            CONFIGURE_DEPENDS true
            "${CMAKE_CURRENT_LIST_DIR}/private/*.cpp"
    )
    list(FILTER sources EXCLUDE REGEX "^.*Test\.cpp$")

    add_library(
            ${CMAKE_PROJECT_NAME}_${MODULE} STATIC
            ${sources}
    )
    target_include_directories(
            ${CMAKE_PROJECT_NAME}_${MODULE} PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/public"
    )

    file(
            GLOB_RECURSE sources
            LIST_DIRECTORIES true
            CONFIGURE_DEPENDS true
            "${CMAKE_CURRENT_LIST_DIR}/private/*Test.cpp"
    )

    #Test target
    add_executable(
            ${CMAKE_PROJECT_NAME}_${MODULE}_test
            ${sources}
    )
    target_link_libraries(
            ${CMAKE_PROJECT_NAME}_${MODULE}_test PUBLIC
            ${CMAKE_PROJECT_NAME}_${MODULE}
            GTest::gtest_main
            GTest::gmock_main
    )

    #Discover Test
    include(GoogleTest)
    gtest_discover_tests(${CMAKE_PROJECT_NAME}_${MODULE}_test)

    target_compile_definitions(
            ${CMAKE_PROJECT_NAME}_${MODULE}
            PRIVATE
            TARGET_NAME="${CMAKE_PROJECT_NAME}_${MODULE}")

    target_compile_definitions(
            ${CMAKE_PROJECT_NAME}_${MODULE}_test
            PRIVATE
            TARGET_NAME="${CMAKE_PROJECT_NAME}_${MODULE}_test")
endmacro()

macro(addDependency MODULE DEPENDENCY)
    target_link_libraries(
            ${CMAKE_PROJECT_NAME}_${MODULE} PUBLIC
            ${DEPENDENCY}
    )
endmacro()

macro(addModuleDependency MODULE DEPENDENCY)
    target_link_libraries(
            ${CMAKE_PROJECT_NAME}_${MODULE} PUBLIC
            ${CMAKE_PROJECT_NAME}_${DEPENDENCY}
    )
endmacro()

macro(defineExecutableForModule MODULE)
    #EXECUTABLE
    add_executable(
            ${CMAKE_PROJECT_NAME}_${MODULE}_exe
            "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
    )

    target_link_libraries(
            ${CMAKE_PROJECT_NAME}_${MODULE}_exe PUBLIC
            ${CMAKE_PROJECT_NAME}_${MODULE}
    )

    target_compile_definitions(
            ${CMAKE_PROJECT_NAME}_${MODULE}_exe
            PRIVATE
            TARGET_NAME="${CMAKE_PROJECT_NAME}_${MODULE}_exe")

    #DLL
    if (WIN32 AND BUILD_SHARED_LIBS)
        add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_${MODULE}_exe POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}_${MODULE}_exe> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}_${MODULE}_exe> COMMAND_EXPAND_LISTS)
    endif()
endmacro()

macro(add3rdPartyHeaders MODULE IMPORT)
    #LIBRARY

    target_include_directories(
            ${CMAKE_PROJECT_NAME}_${MODULE} PUBLIC
            "${PROJECT_SOURCE_DIR}/3rdParty/${IMPORT}"
    )
endmacro()
