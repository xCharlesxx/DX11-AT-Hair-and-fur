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
Triangle* m_Triangle; 
Camera* m_Camera; 
Debug* m_debug; 
Model* m_model; 
void MakeAntTweakBar(); 

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) 
{
	//Create window
	m_Window = new Window(800, 600);
	m_Renderer = new Renderer(*m_Window); 
	m_Triangle = new Triangle(*m_Renderer);
	m_Camera = new Camera; 
	m_debug = new Debug; 
	m_model = new Model(); 
	m_model->getModel("Assets/only_quad_sphere.obj");
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
		m_Triangle->draw(*m_Renderer);
		TwDraw();
		m_Camera->updateCamera();  
		m_Renderer->endFrame();
	}
	TwTerminate();
	return 0;
}

void MakeAntTweakBar()
{
	TwWindowSize(800, 600);
	TwBar *myBar;
	myBar = TwNewBar("Hair And Fur");
	//TwAddVarRW(myBar, "NameOfMyVariable", TW, &myVar, "");
}
