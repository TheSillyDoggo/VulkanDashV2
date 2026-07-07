#include "ShaderCache.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

bgfx::ProgramHandle ShaderCache::get(std::string vertex, std::string frag)
{
    if (!programs.contains({vertex, frag}))
    {
        programs[{vertex, frag}] = bgfx::createProgram(getShader(vertex), getShader(frag));
    }

    return programs[{vertex, frag}];
}

bgfx::ShaderHandle ShaderCache::getShader(std::string file)
{
    std::string renderer = "";

    switch (bgfx::getRendererType())
    {
        case bgfx::RendererType::Agc:
            renderer = "";
            break;
        case bgfx::RendererType::Direct3D11:
            renderer = "d3d11";
            break;
        case bgfx::RendererType::Direct3D12:
            renderer = "d3d12";
            break;
        case bgfx::RendererType::Gnm:
            renderer = "";
            break;
        case bgfx::RendererType::Metal:
            renderer = "metal";
            break;
        case bgfx::RendererType::Nvn:
            renderer = "";
            break;
        case bgfx::RendererType::OpenGLES:
            renderer = "gles";
            break;
        case bgfx::RendererType::OpenGL:
            renderer = "gl";
            break;
        case bgfx::RendererType::Vulkan:
            renderer = "vulkan";
            break;
        case bgfx::RendererType::WebGPU:
            renderer = "";
            break;

        default:
            break;
    }

    auto finalName = utils::string::replace(file, ".sc", fmt::format(".{}.bin", renderer));
    auto path = Mod::get()->getResourcesDir() / finalName;

    log::info("path: {}, final: {}", path, finalName);

    if (shaders.contains(finalName))
        return shaders[finalName];

    auto f = utils::file::readBinary(path);

    if (!f.isOk())
        return BGFX_INVALID_HANDLE;

    auto data = f.unwrap();

    size_t size = data.size();

    const bgfx::Memory* mem = bgfx::alloc(uint32_t(size + 1));
    memcpy(mem->data, data.data(), data.size());

    mem->data[mem->size - 1] = '\0';

    auto handle = bgfx::createShader(mem);
    if (!bgfx::isValid(handle))
    {
        return BGFX_INVALID_HANDLE;
    }

    shaders[finalName] = handle;
    return handle;
}

bgfx::UniformHandle ShaderCache::getSpriteUniform()
{
    static bgfx::UniformHandle handle = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
    return handle;
}