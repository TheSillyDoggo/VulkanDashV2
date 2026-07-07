# vulkan
./shaderc-linux -f ../sprite.vs.sc -o ../bin/sprite.vs.vulkan.bin -i ../ --type vertex --profile spirv
./shaderc-linux -f ../sprite.fs.sc -o ../bin/sprite.fs.vulkan.bin -i ../ --type fragment --profile spirv


# gl
./shaderc-linux -f ../sprite.vs.sc -o ../bin/sprite.vs.gl.bin -i ../ --type vertex --profile 430
./shaderc-linux -f ../sprite.fs.sc -o ../bin/sprite.fs.gl.bin -i ../ --type fragment --profile 430

# metal
./shaderc-linux -f ../sprite.vs.sc -o ../bin/sprite.vs.metal.bin -i ../ --type vertex --platform osx --profile metal
./shaderc-linux -f ../sprite.fs.sc -o ../bin/sprite.fs.metal.bin -i ../ --type fragment --platform osx --profile metal