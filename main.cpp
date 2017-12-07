#include <Windows.h>
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Camera.h"
#include "Debug.h"
#include "AntTweakBar.h"
#include "Model.h"
#include "DrawData.h"
#include "Lighting.h"
#include "Material.h"
#include <memory>
Camera* m_Camera;
Renderer* m_Renderer;
void MakeAntTweakBar(); 

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) 
{
	Window* m_Window;
	Triangle* m_Triangle;
	Debug* m_debug;
	Model* m_model;
	Input* m_input;
	DrawData* m_DD;
	Lighting* m_light;
	unique_ptr<Material> m_material = nullptr;

	//Create window
	m_Window = new Window(800, 600);
	m_Renderer = new Renderer(*m_Window); 
	m_light = new Lighting(XMFLOAT3(0, 10, 0), XMFLOAT4(1, 1, 1, 1));
	m_Camera = new Camera(0.4f*3.14f, (float)800 / 600, 1.0f, 1000.0f);
	m_DD = new DrawData(); 
	m_DD->m_renderer = m_Renderer;
	m_DD->m_cam = m_Camera;
	m_DD->m_light = m_light;
	m_Triangle = new Triangle(*m_Renderer);
	m_debug = new Debug; 
	m_input = new Input(m_Camera); 
	m_model = new Model("Assets/Sphere.obj", m_DD);

	m_material = make_unique<Material>();

	m_material->createBuffers(m_DD); 
	m_model->setMaterial(m_material.get());
	m_input->InitInput(appInstance, m_Window->getHandle());
	TwInit(TW_DIRECT3D11, m_Renderer->getDevice());
	MakeAntTweakBar();
	MSG msg = { 0 };
	while (true) 
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) 
				break;
		}
		m_model->tick(); 
		m_Camera->tick(); 
		m_Camera->updateCamera();
		m_light->tick(); 
		m_Renderer->beginFrame();
		//Draw scene
		//m_Triangle->draw(*m_Renderer);

		/*m_material->obj.transform = XMMatrixTranspose(m_model->getWorldMat());
		m_material->frame.view = XMMatrixTranspose(m_Camera->getViewMatrix());
		m_material->frame.proj = XMMatrixTranspose(m_Camera->getProjMatrix());*/

		m_model->draw(m_DD);
		m_input->DetectInput();
		TwDraw();
		m_Renderer->endFrame();
		m_debug->Output("Camera Pos: " + m_Camera->getPosStr() + "\nCamera Rot: " + m_Camera->getRotStr() + "\n\n"
		              + "Model Pos: X: " + m_model->getPosStr() + "\nModel Rot: " + m_model->getRotStr());
		//m_debug->Output("ProjMatrix: " + std::to_string(m_Camera->getProjMatrix()));
	}
	TwTerminate();
	return 0;
}

void MakeAntTweakBar()
{
	TwWindowSize(800, 600);
	TwBar *myBar;
	myBar = TwNewBar("Hair And Fur");
	TwAddVarRW(myBar, "Cam xPos", TW_TYPE_FLOAT, m_Camera->getXPos(),
		"min = -10000 max = 10000 step = 10 group =Camera Position");
	TwAddVarRW(myBar, "Cam yPos", TW_TYPE_FLOAT, m_Camera->getYPos(),
		"min = -10000 max = 10000 step = 10 group=Camera Position");
	TwAddVarRW(myBar, "Cam zPos", TW_TYPE_FLOAT, m_Camera->getZPos(),
		"min = -10000 max = 10000 step = 10 group=Camera Position");
	TwAddVarRW(myBar, "Background Colour", TW_TYPE_COLOR4F, m_Renderer->getColour(),
		"min = -100 max = 100 step = 10");
}
