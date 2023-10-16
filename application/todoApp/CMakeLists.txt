defineModule("app_todoApp")

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG master
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)
addDependency("app_todoApp" "raylib")
add3rdPartyHeaders("app_todoApp" "raygui")


addModuleDependency("app_todoApp" "core_qstruct_serialize")
defineExecutableForModule("app_todoApp")
