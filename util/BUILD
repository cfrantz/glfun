package(default_visibility=["//visibility:public"])

cc_library(
	name = "file",
	srcs = [
		"file.cc",
	],
	hdrs = [
		"file.h",
		"string.h",
	],
	deps = [
		":status",
	]
)

cc_library(
	name = "logging",
	hdrs = [
		"logging.h",
	],
	srcs = [
		"logging.cc",
	],
	deps = [
        ":string",
        "//external:gflags",
	]
)

cc_library(
	name = "os",
	srcs = [
		"os.cc",
	],
	hdrs = [
		"os.h",
		"string.h",
	],
	deps = [
	]
)

cc_library(
	name = "string",
	hdrs = [
		"string.h",
		"stringpiece.h",
		"stringprintf.h",
		"strutil.h",
	],
	deps = [
		"@google_protobuf//:protobuf",
	]
)

cc_library(
	name = "status",
	hdrs = [
		"status.h",
		"statusor.h",
		"string.h",
	],
	srcs = [
		"status.cc",
	],
	deps = [
		"@google_protobuf//:protobuf",
	]
)


cc_library(
	name = "fpsmgr",
	hdrs = [
		"fpsmgr.h",
	],
)

