#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "GV.hpp"

class Engine
{
	public:
		Engine();
		~Engine();

		void restartClock();
		bool isRunning() const;
		void update();
		void render();

	private:
		sf::RenderWindow m_window;
		sf::Event m_event;
		sf::Clock m_clock;
		float m_dt;

		std::vector<sf::RectangleShape> m_shapes;

		enum m_dirChoice
		{
			carre1,
			carre2,
			carre3,
			carre4
		};


		bool m_tabPressed;
		m_dirChoice m_choice;
};

#endif