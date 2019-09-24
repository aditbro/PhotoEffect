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
    name = "loader_utils",
    hdrs = ["loader_utils.h"],
    srcs = ["loader_utils.cc"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "image_loader",
    hdrs = ["image_loader.h"],
    srcs = ["load_bmp_image.cc", "load_raw_image.cc"],
    visibility = ["//visibility:public"],
    deps = [":color", ":image", ":loader_utils"]
)