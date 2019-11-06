emcc -std=c++11 \
    ../lib/image.cc \
    ../lib/operators.cc \
    ../lib/histogram.cc \
    api.cc \
    -s WASM=1 -O3 -o index.js \
    -s "EXTRA_EXPORTED_RUNTIME_METHODS=[\
        'allocate', 'intArrayFromString',\
        'ccall',\
        'cwrap',\
        'create_image',\
        'image_brightness_correction',\
        'image_invert',\
        'image_convert_color',\
        'image_scalar_operator',\
        'image_scalar_boolean_operator',\
        'image_color_remapping',\
        'image_contrast_stretching',\
        'image_intensity_slice',\
        'image_edge_detect',\
        'image_bit_slice'\
    ]" \
    -s ASSERTIONS=1 --emrun \
    -s "BINARYEN_TRAP_MODE='clamp'"
