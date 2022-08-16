#pragma once
#include "../dx-renderer-context.h"
#define NOMINMAX
#include <Windows.h>
#include <d3d11.h>
#include "../../../../logger/logger.h"

namespace fbr::dx {
	class ContextDirectX11Windows : public ContextDirectX11
	{
	public:
		virtual ~ContextDirectX11Windows()
		{
			Destroy();
		}

		ContextDirectX11Windows(windows::WindowWin * window)
		{
			m_handle = window->GetHandle();
			Create();
		}

		void SetBackgroundColor(const Color<float>& color)
		{
			background[0] = color.R();
			background[1] = color.G();
			background[2] = color.B();
			background[3] = color.Alpha();
		}

		bool Good() const override
		{
			return true;
		}

		void SwitchDepthTest(bool enable) override
		{

		}

		void SwitchStencilTest(bool enable) override
		{

		}

		void SetDepthClearValue(double depth)override
		{

		}

		void SetStencilClearValue(int stencil) override
		{

		}

		void Clear() override
		{
			d3dcontext->ClearRenderTargetView(d3dtarget, background);
		}


	protected:
		bool Create() override
		{
			HRESULT result = S_OK;

			DXGI_MODE_DESC dxgi_mode_desc = { 0 };
			dxgi_mode_desc.Width = 800;
			dxgi_mode_desc.Height = 600;
			dxgi_mode_desc.RefreshRate.Numerator = 0;
			dxgi_mode_desc.RefreshRate.Denominator = 0;
			dxgi_mode_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			dxgi_mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			dxgi_mode_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			DXGI_SWAP_CHAIN_DESC dxgi_swapchain_desc = { 0 };
			dxgi_swapchain_desc.BufferDesc = dxgi_mode_desc;
			dxgi_swapchain_desc.SampleDesc.Count = 8;
			dxgi_swapchain_desc.SampleDesc.Quality = 0;
			dxgi_swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			dxgi_swapchain_desc.BufferCount = 1;
			dxgi_swapchain_desc.OutputWindow = m_handle;
			dxgi_swapchain_desc.Windowed = TRUE;
			dxgi_swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			dxgi_swapchain_desc.Flags = 0;

			D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_0;
			result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_SINGLETHREADED, nullptr, 0, D3D11_SDK_VERSION, &dxgi_swapchain_desc, &swapchain, &d3ddevice, &feature_level, &d3dcontext);
			if (FAILED(result))
			{
				LOG_ERR("Initializing Direct3D 11 failed.");
				return false;
			}

			ID3D11Texture2D* backbuffer = nullptr;
			result = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
			if (FAILED(result))
			{
				LOG_ERR("Invalid backbuffer.");
				return false;
			}

			result = d3ddevice->CreateRenderTargetView(backbuffer, nullptr, &d3dtarget);
			if (FAILED(result))
			{
				LOG_ERR("Creating render target view failed.");
				safeRelease(&backbuffer);
				return false;
			}
			safeRelease(&backbuffer);

			D3D11_VIEWPORT viewport = { 0 };
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = 800;
			viewport.Height = 600;
			viewport.MinDepth = 0.0F;
			viewport.MaxDepth = 1.0F;

			d3dcontext->RSSetViewports(1, &viewport);
			d3dcontext->OMSetRenderTargets(1, &d3dtarget, nullptr);

			return true;
		}

		void Destroy() override
		{
			safeRelease(&swapchain);
			safeRelease(&d3dtarget);
			safeRelease(&d3dcontext);
			safeRelease(&d3ddevice);
		}

		void SetAsRenderTarget()
		{

		}

		void SwapBuffer() override
		{
			swapchain->Present(1, 0);
		}


		bool MakeCurrent() const
		{
			return true;
		}

	private:
		HWND m_handle;

		ID3D11Device* d3ddevice = nullptr;
		ID3D11DeviceContext* d3dcontext = nullptr;
		ID3D11RenderTargetView* d3dtarget = nullptr;
		IDXGISwapChain* swapchain = nullptr;

		FLOAT background[4] = { 0.16F, 0.16F, 0.16F, 1.0F };
	};
}