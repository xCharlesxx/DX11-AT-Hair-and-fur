#include "Renderer.h"

Renderer::Renderer(Window& window) 
{
	colour = XMFLOAT4(0.06, 0.50, 0.60, 0);
	createDevice(window);
	createRenderTarget();
}

void Renderer::createDevice(Window& window) 
{
	//Define swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window.getHandle();
	swapChainDesc.SampleDesc.Count = 8;
	swapChainDesc.Windowed = true;
	
	//Create the swap chain, device and device context
	auto result = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		nullptr, 0, D3D11_SDK_VERSION,
		&swapChainDesc, &m_swapChain,
		&m_device, nullptr, &m_deviceContext);

	//Check for error
	if (result != S_OK) {
		MessageBox(nullptr, "Error creating DX11", "Error", MB_OK);
		exit(0);
	}
}

void Renderer::createRenderTarget() 
{
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &backBuffer);
	m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	backBuffer->GetDesc(&m_backBufferDesc);
	backBuffer->Release();
}

void Renderer::beginFrame() 
{
	//Bind render target
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

	//Set viewport
	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, (float) m_backBufferDesc.Width, (float) m_backBufferDesc.Height);
	m_deviceContext->RSSetViewports(1, &viewport);

	//Set the background colour
	float BackgroundColour[] = { colour.x, colour.y, colour.z, colour.w };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, BackgroundColour);
}