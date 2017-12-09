#include "Material.h"



Material::Material()
{
}


Material::~Material()
{
}

void Material::createBuffers(DrawData *_DD)
{
	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DYNAMIC; 
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; 
	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
	buffer_desc.MiscFlags = 0; 
	buffer_desc.StructureByteStride = 0; 
	HRESULT hr = {}; 

	buffer_desc.ByteWidth = sizeof(frame); 
	hr = _DD->m_renderer->getDevice()->CreateBuffer(&buffer_desc, nullptr, &frame_buffer);
	if (hr != MB_OK)
	{
		MessageBox(nullptr, "[Material] (createBuffers) Failed to create frame buffer", "Error", MB_OK);
		exit(0);
	}

	buffer_desc.ByteWidth = sizeof(obj);
	hr = _DD->m_renderer->getDevice()->CreateBuffer(&buffer_desc, nullptr, &object_buffer);
	if (hr != MB_OK)
	{
		MessageBox(nullptr, "[Material] (createBuffers) Failed to create object buffer", "Error", MB_OK);
		exit(0);
	}
}

void Material::updateBuffers(DrawData *_DD)
{
	HRESULT hr = {};
	D3D11_MAPPED_SUBRESOURCE vsObjMapping{ nullptr };
	hr = _DD->m_renderer->getDeviceContext()->Map(object_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vsObjMapping);
	memcpy(vsObjMapping.pData, &obj, sizeof(VSOBJBUFFER));
	_DD->m_renderer->getDeviceContext()->Unmap(object_buffer, 0);

	D3D11_MAPPED_SUBRESOURCE vsFrameMapping{ nullptr };
	hr = _DD->m_renderer->getDeviceContext()->Map(frame_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vsFrameMapping);
	memcpy(vsFrameMapping.pData, &frame, sizeof(VSFRAMEBUFFER));
	_DD->m_renderer->getDeviceContext()->Unmap(frame_buffer, 0);
}

void Material::setBuffers(DrawData * _DD)
{
	//ID3D11Buffer* vs_buffers[] = { frame_buffer, object_buffer };
	//_DD->m_renderer->getDeviceContext()->VSSetConstantBuffers(0, _countof(vs_buffers), vs_buffers);
	_DD->m_renderer->getDeviceContext()->VSSetConstantBuffers(0, 1, &object_buffer);
	_DD->m_renderer->getDeviceContext()->VSSetConstantBuffers(1, 1, &frame_buffer);
}


