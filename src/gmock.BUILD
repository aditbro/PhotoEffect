cc_library(
    name = "main",
    srcs = glob(
        ["src/*.cc"],
        exclude = ["src/gmock-all.cc"]
    ),
    hdrs = glob([
        "include/**/*.h",
        "src/*.h"
    ]),
    copts = ["-Iexternal/gmock/include", "-Iexternal/gtest/include"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
    deps = ["@gtest//:main"]
)
