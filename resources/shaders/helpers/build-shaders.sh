OS="$(uname)"
ARCH="$(uname -m)"

if [ "$OS" = "Darwin" ]; then
    if [ "$ARCH" = "arm64" ]; then
        SHADERC="./shaderc-osx-m1"
    else
        SHADERC="./shaderc-osx-64"
    fi
elif [ "$OS" = "Linux"]; then
    SHADERC="./shaderc-linux"
fi

# vulkan
$SHADERC -f ../sprite.vs.sc -o ../bin/sprite.vs.vulkan.bin -i ../ --type vertex --profile spirv
$SHADERC -f ../sprite.fs.sc -o ../bin/sprite.fs.vulkan.bin -i ../ --type fragment --profile spirv

# gl
$SHADERC -f ../sprite.vs.sc -o ../bin/sprite.vs.gl.bin -i ../ --type vertex --profile 430
$SHADERC -f ../sprite.fs.sc -o ../bin/sprite.fs.gl.bin -i ../ --type fragment --profile 430

# metal
$SHADERC -f ../sprite.vs.sc -o ../bin/sprite.vs.metal.bin -i ../ --type vertex --platform osx --profile metal
$SHADERC -f ../sprite.fs.sc -o ../bin/sprite.fs.metal.bin -i ../ --type fragment --platform osx --profile metal