emcc ../lib/image.cc \
    ../lib/operators.cc \
    ../lib/histogram.cc \
    api.cc \
     -s WASM=1 -O3 -o index.js \
    -s "EXTRA_EXPORTED_RUNTIME_METHODS=[\
        'ccall',\
        'cwrap',\
        'create_image',\
        'image_brightness_correction',\
        'image_invert',\
        'image_convert_color',\
        'image_scalar_operator'\
    ]" \
    -s ASSERTIONS=1 --emrun