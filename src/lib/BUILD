cc_library(
    name = "color",
    hdrs = ["color.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "image",
    srcs = ["image.cc"],
    hdrs = ["image.h"],
    visibility = ["//visibility:public"],
    deps = [":color"]
)

cc_library(
    name = "image_loader",
    srcs = ["load_bmp_image.cc"],
    hdrs = ["image_loader.h"],
    visibility = ["//visibility:public"],
    deps = [":color", ":image"]
)