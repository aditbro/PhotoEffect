cc_binary(
    name = "load_bmp",
    srcs = ["load_bmp_test.cc"],
    deps = [
        "//lib:image_loader"
    ]
)

cc_binary(
    name = "get_histogram",
    srcs = ["get_histogram.cc"],
    deps = [
        "//lib:image",
        "//lib:image_loader",
        "//lib:histogram",
        "//lib:operators"
    ]
)

cc_binary(
    name = "test_convolution",
    srcs = ["test_convolution.cc"],
    deps = [
        "//lib:image_loader",
        "//lib:image",
    ]
)

cc_binary(
    name = "operators_test",
    srcs = ["operators_test.cc"],
    deps = [
        "//lib:image",
        "//lib:image_loader",
        "//lib:histogram",
        "//lib:operators"
    ]
)

