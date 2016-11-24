package(default_visibility=["//visibility:public"])

cc_library(
    name = "imapp",
    linkopts = [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
        "-lSDL2_gfx",
    ],
    hdrs = [
        "imapp.h",
    ],
    srcs = [
        "imapp.cc",
    ],
    deps = [
        "//imwidget:debug_console",
        "//util:fpsmgr",
        "//util:os",
        "//external:gflags",
        "//external:imgui_sdl_opengl",
    ],
)

cc_binary(
    name = "main",
    linkopts = [
        "-lpthread",
    ],
    srcs = [
        "main.cc",
    ],
    deps = [
        ":imapp",
        "//util:file",
        "//util:logging",
        "//util:string",
        "//external:gflags",
    ],
)
