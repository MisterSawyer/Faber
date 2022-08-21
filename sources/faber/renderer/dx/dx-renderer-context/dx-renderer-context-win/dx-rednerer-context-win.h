#pragma once
#define NOMINMAX
#include <Windows.h>
#include <d3d11.h>
#include <faber/window/window-win/window-win.h>

#include <faber/logger/logger.h>
#include <faber/renderer/dx/dx-renderer-context/dx-renderer-context.h>


namespace fbr::dx {
	class ContextDirectX11Windows : public ContextDirectX11
	{
	public:
		virtual ~ContextDirectX11Windows();

		ContextDirectX11Windows(windows::WindowWin* window);

		void SetBackgroundColor(const Color<float>& color);
		bool Good() const override;
		void SwitchDepthTest(bool enable) override;
		void SwitchStencilTest(bool enable) override;
		void SetDepthClearValue(double depth)override;
		void SetStencilClearValue(int stencil) override;
		void Clear() override;
	protected:
		bool Create() override;

		void Destroy() override;

		void SetAsRenderTarget();

		void SwapBuffer() override;


		bool MakeCurrent() const;

	private:
		HWND m_handle;

		ID3D11Device* d3ddevice = nullptr;
		ID3D11DeviceContext* d3dcontext = nullptr;
		ID3D11RenderTargetView* d3dtarget = nullptr;
		IDXGISwapChain* swapchain = nullptr;

		FLOAT background[4] = { 0.16F, 0.16F, 0.16F, 1.0F };
	};
}