#include "Game.h"

bool Game::init(const char* title, int xPos, int yPos, int height, int width, int flags)
{
	//Attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL init success" <<std::endl;
		m_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		// if the window creation succeeded create our renderer
		if (m_pWindow != 0)
		{
			std::cout << "SDL window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0)
			{
				std::cout << "SDL renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
				
				SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
				if (pTempSurface == 0)
				{
					std::cout << "Failed to Load BMP" << std::endl;
				}
				m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer,
					pTempSurface);
				SDL_FreeSurface(pTempSurface);

				SDL_QueryTexture(m_pTexture, NULL, NULL,
					&m_sourceRectangle.w, &m_sourceRectangle.h);

				m_destinationRectangle.x = m_sourceRectangle.x = 0;
				m_destinationRectangle.y = m_sourceRectangle.y = 0;
				m_destinationRectangle.w = m_sourceRectangle.w;
				m_destinationRectangle.h = m_sourceRectangle.h;
			
			}
			else
			{
				std::cout << "SDL renderer creation fail" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "SDL window creation fail" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "SDL init fail" << std::endl;
		return false; // sdl could not initialize
	}
	std::cout << "SDL init success" << std::endl;
	m_bRunning = true;
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle,
		&m_destinationRectangle);

	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{

}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

Game::Game()
{
}


Game::~Game()
{
}
