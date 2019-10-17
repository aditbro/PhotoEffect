const api = {
    create_image: Module.cwrap('create_image', 'number', ['number', 'number']),
    image_brightness_correction: Module.cwrap('image_brightness_correction', 'number', ['number', 'number']),
    image_invert: Module.cwrap('image_invert', null, null),
    image_convert_color: Module.cwrap('image_convert_color', null, null),
    image_scalar_operator: Module.cwrap('image_scalar_operator', null, ['number', 'number']),
    image_scalar_boolean_operator: Module.cwrap('image_scalar_boolean_operator', null, ['number']),
    image_color_remapping: Module.cwrap('image_color_remapping', null, ['number', 'number', 'number']),
    image_contrast_stretching: Module.cwrap('image_contrast_stretching', null, ['number', 'number', 'number', 'number']),
    image_intensity_slice: Module.cwrap('image_intensity_slice', null, ['number', 'number', 'number', 'number']),
    image_bit_slice: Module.cwrap('image_bit_slice', null, ['number']),
    image_edge_detect: Module.cwrap('image_bit_slice', null),
};

document.getElementById("selector").addEventListener("change", function() {
    loadImage()
})

var img_pointer = 0

function loadImage() {
    var preview = document.querySelector("#preview")
    var file = document.querySelector('#selector').files[0]
    var reader = new FileReader();

    reader.onloadend = function () {
        preview.onload = function () {
            previewImage()
            setImageHeap()
            loadImageToHeap()
        }
        preview.src = reader.result;
    }

    if (file) {
        reader.readAsDataURL(file)
    } else {
        preview.src = "";
    }
}

function previewImage() {
    var ctx = document.querySelector("#myCanvas").getContext("2d")
    var preview = document.querySelector("#preview")
    ctx.canvas.width = preview.width
    ctx.canvas.height = preview.height
    ctx.drawImage(preview, 0, 0);
}

function setImageHeap() {
    var preview = document.querySelector("#preview")
    img_pointer = api.create_image(preview.width, preview.height)
    Module.HEAP8.set([], img_pointer);
}

function loadImageToHeap() {
    var preview = document.querySelector("#preview")
    var ctx = document.querySelector("#myCanvas").getContext("2d")
    imageData = ctx.getImageData(0, 0, preview.width, preview.height)

    for(let i = 0; i < preview.width * preview.height * 4; i++) {
        Module.HEAPU8[i + img_pointer] = imageData.data[i]
    }
}

function reloadImage() {
    var preview = document.querySelector("#preview")
    var ctx = document.querySelector("#myCanvas").getContext("2d")
    var imgData = new ImageData(preview.width, preview.height * 4)

    imgData.data.set(Module.HEAPU8.slice(img_pointer))

    ctx.putImageData(imgData, 0, 0)
}