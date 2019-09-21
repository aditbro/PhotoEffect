cc_test(
    name = "test",
    srcs = glob(["*.cc"]),
    copts = ["-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    deps = [
        "@gtest//:main",
        "@gmock//:main",
    ],
)

cc_test(
    name = "load_bmp_image",
    srcs = ["load_bmp_image_test.cc"],
    copts = ["-Iexternal/gtest/include", "-Iexternal/gmock/include"],
    deps = [
        "@gtest//:main",
        "@gmock//:main",
        "//lib:image_loader"
    ]
)