#include <Geode/Geode.hpp>
#include <Geode/modify/CCEGLView.hpp>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <ShaderCache.hpp>
#include <macOS.hpp>
#include <BGFX.hpp>

using namespace geode::prelude;

#define PRINT_STAT_I($stat) \
y++; \
bgfx::dbgTextPrintf(0, y, 0x0f, #$stat ": %i", stats->$stat);

#define PRINT_STAT_U($stat) \
y++; \
bgfx::dbgTextPrintf(0, y, 0x0f, #$stat ": %u", stats->$stat);


class $modify (BGFXEGLView, CCEGLView)
{
    void swapBuffers()
    {
        uint16_t screenWidth = uint16_t(CCEGLView::get()->m_obScreenSize.width);
        uint16_t screenHeight = uint16_t(CCEGLView::get()->m_obScreenSize.height);

        static uint16_t lastWidth = 0;
        static uint16_t lastHeight = 0;

        if (screenWidth != lastWidth || screenHeight != lastHeight)
        {
            lastWidth = screenWidth;
            lastHeight = screenHeight;

            log::warn("resized to {}x{}", lastWidth, lastHeight);
        }

        bgfx::dbgTextClear();

        const bgfx::Stats* stats = bgfx::getStats();

        if (CCKeyboardDispatcher::get()->getAltKeyPressed())
        {

        int y = 0;

        /*
        PRINT_STAT_I( cpuTimeFrame);               //!< CPU time between two `bgfx::frame` calls.
		PRINT_STAT_I( cpuTimeBegin);               //!< Render thread CPU submit begin time.
		PRINT_STAT_I( cpuTimeEnd);                 //!< Render thread CPU submit end time.
		PRINT_STAT_I( cpuTimerFreq);               //!< CPU timer frequency. Timestamps-per-second
		PRINT_STAT_I( gpuTimeBegin);               //!< GPU frame begin time.
		PRINT_STAT_I( gpuTimeEnd);                 //!< GPU frame end time.
		PRINT_STAT_I( gpuTimerFreq);               //!< GPU timer frequency.*/
		PRINT_STAT_I( waitRender);                 //!< Time spent waiting for render backend thread to finish issuing draw commands to underlying graphics API.
		PRINT_STAT_I( waitSubmit);                 //!< Time spent waiting for submit thread to advance to next frame.
		PRINT_STAT_U( numDraw);                   //!< Number of draw calls submitted.
		PRINT_STAT_U( numCompute);                //!< Number of compute calls submitted.
		PRINT_STAT_U( numBlit);                   //!< Number of blit calls submitted.
		PRINT_STAT_U( numDrawCallsPeak);          //!< Highest number of draw+compute calls requested in a single

        PRINT_STAT_U( maxGpuLatency);             //!< GPU driver latency.
		PRINT_STAT_U( gpuFrameNum);               //!< Frame which generated gpuTimeBegin, gpuTimeEnd.
		PRINT_STAT_U( numDynamicIndexBuffers);    //!< Number of used dynamic index buffers.
		PRINT_STAT_U( numDynamicVertexBuffers);   //!< Number of used dynamic vertex buffers.
		PRINT_STAT_U( numFrameBuffers);           //!< Number of used frame buffers.
		PRINT_STAT_U( numIndexBuffers);           //!< Number of used index buffers.
		PRINT_STAT_U( numOcclusionQueries);       //!< Number of used occlusion queries.
		PRINT_STAT_U( numPrograms);               //!< Number of used programs.
		PRINT_STAT_U( numShaders);                //!< Number of used shaders.
		PRINT_STAT_U( numTextures);               //!< Number of used textures.
		PRINT_STAT_U( numUniforms);               //!< Number of used uniforms.
		PRINT_STAT_U( numVertexBuffers);          //!< Number of used vertex buffers.
		PRINT_STAT_U( numVertexLayouts);          //!< Number of used vertex layouts.
		PRINT_STAT_I( textureMemoryUsed);          //!< Estimate of texture memory used.
		PRINT_STAT_I( rtMemoryUsed);               //!< Estimate of render target memory used.
		PRINT_STAT_I( transientVbUsed);            //!< Amount of transient vertex buffer used.
		PRINT_STAT_I( transientIbUsed);            //!< Amount of transient index buffer used.
		// uint32_t numPrims[Topology::Count]; //!< Number of primitives rendered.
		PRINT_STAT_I( gpuMemoryMax);               //!< Maximum available GPU memory for application.
		PRINT_STAT_I( gpuMemoryUsed);              //!< Amount of GPU memory used by the application.
		PRINT_STAT_U( numViews);                  //!< Number of view stats.
		// ViewStats* viewStats;               //!< Array of View stats.
		PRINT_STAT_U( numEncoders);


        /*bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dx%d"
            , stats->width
            , stats->height
            );

        const GLubyte* gpu = glGetString(GL_RENDERER);

        bgfx::dbgTextPrintf(0, 4, 0x0f, "Renderer: %s", bgfx::getRendererName(bgfx::getRendererType()));
        bgfx::dbgTextPrintf(0, 5, 0x0f, "GPU: %s", reinterpret_cast<const char*>(gpu));
        if (CCDirector::get()->m_pFPSNode)
            bgfx::dbgTextPrintf(0, 6, 0x0f, "%s", CCDirector::get()->m_pFPSNode->getString());*/

        }
        
        bgfx::frame();
        #ifdef BGFX_CONFIG_MULTITHREADED
        bgfx::renderFrame();
        #endif
    }
};