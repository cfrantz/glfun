package(default_visibility=["//visibility:public"])

cc_library(
    name = "triangle",
    srcs = [ "triangle.cc", ],
    hdrs = [ "triangle.h", ],
)

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
        ":triangle",
        "//imwidget:debug_console",
        "//util:fpsmgr",
        "//util:os",
        "//util:logging",
        "//external:gflags",
        "//imwidget:imgui_sdl_opengl",
    ],
)

cc_binary(
    name = "main",
    linkopts = [
        "-lpthread",
        "-lGLEW",
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
