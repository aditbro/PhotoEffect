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
    hdrs = ["image_loader.h"],
    srcs = ["load_bmp_image.cc"],
    visibility = ["//visibility:public"],
    deps = [":color", ":image"]
)

cc_library(
    name = "histogram",
    hdrs = ["histogram.h"],
    srcs = ["histogram.cc"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "operators",
    hdrs = ["operators.h"],
    srcs = ["operators.cc"],
    visibility = ["//visibility:public"],
    deps = [":color", ":image", ":histogram"]
)

cc_library(
    name = "ocr",
    hdrs = ["ocr.h"],
    srcs = ["ocr.cc"],
    visibility = ["//visibility:public"],
    deps = [":color", ":image", ":histogram", ":operators", ":image_loader"]
)

cc_library(
    name = "complex",
    hdrs = ["complex.h"],
    srcs = ["complex.cc"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "dft",
    hdrs = ["dft.h"],
    srcs = ["dft.cc"],
    visibility = ["//visibility:public"],
    deps = [":image", ":complex", ":color"]
)