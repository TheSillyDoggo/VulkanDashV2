#pragma once

#include <bgfx/bgfx.h>
#include <string.h>

class ShaderCache
{
    protected:
        static inline std::map<std::pair<std::string, std::string>, bgfx::ProgramHandle> programs = {};
        static inline std::map<std::string, bgfx::ShaderHandle> shaders = {};
        static inline std::map<std::string, bgfx::ProgramHandle> computePrograms = {};

    public:
        static bgfx::ProgramHandle get(std::string vertex, std::string frag);
        static bgfx::ProgramHandle getCompute(std::string file);
        static bgfx::ShaderHandle getShader(std::string file);

        static bgfx::UniformHandle getSpriteUniform();
};