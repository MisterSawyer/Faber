#pragma once

#include <framework/renderer/opengl/opengl-surface-bitfields.h>
#include <framework/renderer/renderer-context/renderer-context.h>

namespace fbr::opengl
{
	class ContextOpenGL : public fbr::IRendererContext
	{
	public:
		virtual ~ContextOpenGL() = default;

		void SetBackgroundColor(const Color<float> & color) override;

		void Clear() override;
		virtual void SwapBuffer() = 0;
		virtual void Destroy() = 0;

	protected:
		virtual bool GetAccessToOpenGLExtensions() = 0;
		bool LoadOpenGLExtensions();
		void SetOpenGLSettings();

	private:
		void SwitchDepthTest(bool enable) override;
		void SwitchStencilTest(bool enable)override;

		void SetDepthClearValue(double depth) override;
		void SetStencilClearValue(int stencil) override;
		void SetAsRenderTarget() override;

		void ClearBuffers(SurfaceMask masks);
	};
}