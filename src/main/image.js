document.getElementById("selector").addEventListener("change", function() {
    loadImage()
})

function loadImage() {
    var preview = document.querySelector("#preview")
    var file = document.querySelector('#selector').files[0]
    var reader = new FileReader();

    reader.onloadend = function () {
        preview.src = reader.result;
        previewImage()
        // setImageHeap()
        // loadImageInC()
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