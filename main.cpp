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

Window* m_Window; 
Renderer* m_Renderer; 
//Triangle* m_Triangle; 
Camera* m_Camera; 
Debug* m_debug; 
Model* m_model; 
Input* m_input; 
DrawData* m_DD; 
Lighting* m_light; 
void MakeAntTweakBar(); 

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) 
{
	//Create window
	m_Window = new Window(800, 600);
	m_Renderer = new Renderer(*m_Window); 
	m_DD = new DrawData(); 
	m_DD->m_pd3dImmediateContext = nullptr;
	m_DD->m_renderer = m_Renderer;
	m_DD->m_cam = m_Camera;
	m_DD->m_light = m_light;
	//m_Triangle = new Triangle(*m_Renderer);
	m_Camera = new Camera(0.4f*3.14f, (float)800 / 600, 1.0f, 1000.0f);
	m_debug = new Debug; 
	m_input = new Input(m_Camera); 
	m_model = new Model("Assets/Sphere.obj", m_DD);
	m_light = new Lighting(XMFLOAT3(0, 10, 0), XMFLOAT4(1, 1, 1, 1));


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

		m_Renderer->beginFrame();
		//Draw scene
		//m_Triangle->draw(*m_Renderer);
		TwDraw();
		m_model->draw(m_DD);
		m_Camera->updateCamera(); 
		m_input->DetectInput();
		m_Renderer->endFrame();
		m_debug->Output("Camera Pos: " + m_Camera->getPosStr() + "\nCamera Rot: " + m_Camera->getRotStr() + "\n");
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
		"min = -100 max = 100 step = 10 group =Camera Position");
	TwAddVarRW(myBar, "Cam yPos", TW_TYPE_FLOAT, m_Camera->getYPos(),
		"min = -100 max = 100 step = 10 group=Camera Position");
	TwAddVarRW(myBar, "Cam zPos", TW_TYPE_FLOAT, m_Camera->getZPos(),
		"min = -100 max = 100 step = 10 group=Camera Position");
	TwAddVarRW(myBar, "Background Colour", TW_TYPE_COLOR4F, m_Renderer->getColour(),
		"min = -100 max = 100 step = 10");
	//TwAddVarRW(myBar, "NameOfMyVariable", TW, &myVar, "");
}
