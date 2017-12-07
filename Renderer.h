#pragma once

#include "Window.h"
#include <d3d11.h>

class Renderer 
{
public:
	Renderer(Window& window);
	void beginFrame();
	void endFrame() { m_swapChain->Present(1, 0); };
	ID3D11Device* getDevice() { return m_device; };
	ID3D11DeviceContext* getDeviceContext() { return m_deviceContext; } ;
	XMFLOAT4* getColour() { return &colour; };

private:
	void createDevice(Window& window);
	void createRenderTarget();

	//Colour 
	XMFLOAT4 colour; 
	//Device stuff
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;

	//Render target
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	D3D11_TEXTURE2D_DESC m_backBufferDesc;
};
