#include <Windows.h>
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Camera.h"
#include "Debug.h"
#include "AntTweakBar.h"
#include "Model.h"

Window* m_Window; 
Renderer* m_Renderer; 
//Triangle* m_Triangle; 
Camera* m_Camera; 
Debug* m_debug; 
Model* m_model; 
Input* m_input; 
void MakeAntTweakBar(); 

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) 
{
	//Create window
	m_Window = new Window(800, 600);
	m_Renderer = new Renderer(*m_Window); 
	//m_Triangle = new Triangle(*m_Renderer);
	m_Camera = new Camera; 
	m_debug = new Debug; 
	m_input = new Input(m_Camera); 
	m_model = new Model("Assets/Sphere.obj", *m_Renderer);
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
		TwDraw();
		//m_Triangle->draw(*m_Renderer);
		m_model->draw(*m_Renderer);
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
	TwAddVarRW(myBar, "Cam xPos    ", TW_TYPE_FLOAT, m_Camera->getCamX(),
		"min = -100 max = 100 step = 10 group = Camera Position");
	TwAddVarRW(myBar, "Cam yPos    ", TW_TYPE_FLOAT, m_Camera->getCamY(),
		"min = -100 max = 100 step = 10 group=Camera Position");
	TwAddVarRW(myBar, "Cam zPos    ", TW_TYPE_FLOAT, m_Camera->getCamZ(),
		"min = -100 max = 100 step = 10 group=Camera Position");
	TwAddVarRW(myBar, "Background Colour    ", TW_TYPE_COLOR4F, m_Renderer->getColour(),
		"min = -100 max = 100 step = 10 group = Camera Position");
	TwAddVarRW(myBar, "Cam yPos    ", TW_TYPE_FLOAT, m_Camera->getCamY(),
		"min = -100 max = 100 step = 10 group=Camera Position");
	TwAddVarRW(myBar, "Cam zPos    ", TW_TYPE_FLOAT, m_Camera->getCamZ(),
		"min = -100 max = 100 step = 10 group=Camera Position");
	//TwAddVarRW(myBar, "NameOfMyVariable", TW, &myVar, "");
}
