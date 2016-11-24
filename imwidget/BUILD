package(default_visibility=["//visibility:public"])

cc_library(
    name = "debug_console",
    hdrs = ["debug_console.h"],
    srcs = ["debug_console.cc"],
    deps = [
        "//external:imgui",
    ],
)


cc_library(
    name = "imgui_sdl_opengl",
    copts = [
        "-I/usr/include/SDL2",
    ],
    hdrs = [
        "imgui_impl_sdl_gl3.h",
    ],
    srcs = [
        "imgui_impl_sdl_gl3.cpp",
    ],
    deps = [
        "//external:imgui",
    ],
)
