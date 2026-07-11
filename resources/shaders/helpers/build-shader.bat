// directx 11
shaderc-win64.exe -f ../sprite.vs.sc -o ../bin/sprite.vs.d3d11.bin -i ../ --type vertex --platform windows -p s_5_0
shaderc-win64.exe -f ../sprite.fs.sc -o ../bin/sprite.fs.d3d11.bin -i ../ --type fragment --platform windows -p s_5_0

// directx 12
shaderc-win64.exe -f ../sprite.vs.sc -o ../bin/sprite.vs.d3d12.bin -i ../ --type vertex --platform windows -p s_6_0
shaderc-win64.exe -f ../sprite.fs.sc -o ../bin/sprite.fs.d3d12.bin -i ../ --type fragment --platform windows -p s_6_0