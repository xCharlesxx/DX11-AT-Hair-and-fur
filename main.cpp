#include <Windows.h>
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Camera.h"

Window* m_Window; 
Renderer* m_Renderer; 
Triangle* m_Triangle; 
Camera* m_Camera; 


int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) 
{
	//Create window
	m_Window = new Window(800, 600); 
	m_Renderer = new Renderer(*m_Window); 
	m_Triangle = new Triangle(*m_Renderer);
	m_Camera = new Camera; 

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
		m_Camera->updateCamera();  

		m_Renderer->endFrame();
	}

	return 0;
}