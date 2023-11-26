#include "../header/Engine.hpp"

Engine::Engine(): m_event(), m_tabPressed(false), m_dt(0)
{
	m_window.create(sf::VideoMode(GV::WINDOWSIZE.x, GV::WINDOWSIZE.y), GV::TITLE, sf::Style::Close | sf::Style::Titlebar);

	for (int i = 0; i <= 3; i++) {
		sf::RectangleShape tempRec = sf::RectangleShape({ GV::SHAPESIZE, GV::SHAPESIZE });
		tempRec.setFillColor(GV::SHAPECOLOR);

		m_shapes.push_back(tempRec);

	}

	const float step = GV::SHAPESIZE;
	m_shapes[0].setPosition({ step , step });
	m_shapes[1].setPosition({ GV::WINDOWSIZE.x - step * 2, step });
	m_shapes[2].setPosition({ step , GV::WINDOWSIZE.y - step * 2});
	m_shapes[3].setPosition({ GV::WINDOWSIZE.x - step * 2, GV::WINDOWSIZE.y - step * 2 });

	m_choice = carre1;
	m_window.setFramerateLimit(250);

}

Engine::~Engine()
{
}

void Engine::restartClock() { m_dt = m_clock.restart().asSeconds(); }

bool Engine::isRunning() const { return m_window.isOpen(); }

void Engine::update()
{
	while (m_window.pollEvent(m_event)) {
		if (m_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { m_window.close(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !m_tabPressed) {

			int currentSquare = static_cast<int>(m_choice);

			m_choice = static_cast<m_dirChoice>((currentSquare + 1) % static_cast<int>(m_dirChoice::carre4 + 1));

			m_tabPressed = true;
		}
		else { m_tabPressed = !m_tabPressed; }

		
	}

	auto& shape = m_shapes[m_choice];


	if(shape.getPosition().x + GV::SHAPESIZE < m_window.getSize().x) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			shape.move({ GV::VELOCITY * GV::ACCELERATION * m_dt, 0});
		}
	}
	if (shape.getPosition().x > 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			shape.move({ GV::VELOCITY * GV::ACCELERATION * -m_dt, 0});
		}
	}
	if (shape.getPosition().y + GV::SHAPESIZE < m_window.getSize().y) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			shape.move({ 0, GV::VELOCITY * GV::ACCELERATION * m_dt});
		}
	}
	if (shape.getPosition().y > 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			shape.move({ 0 , GV::VELOCITY * GV::ACCELERATION * -m_dt});
		}
	}
	bool colision = false;

	for (int i = 0; i < m_shapes.size(); i++) {
		auto& currentObject = m_shapes[i]; 

		for (int j = 0; j < m_shapes.size(); j++) {
			if (i != j) { 
				auto& otherObject = m_shapes[j]; 

				float Object1X = currentObject.getPosition().x;
				float Object1Y = currentObject.getPosition().y;
				float Object2X = otherObject.getPosition().x;
				float Object2Y = otherObject.getPosition().y;

				float objectSize = GV::SHAPESIZE;

				if (Object1X <= Object2X + objectSize &&
					Object1X + objectSize >= Object2X &&
					Object1Y <= Object2Y + objectSize &&
					Object1Y + objectSize >= Object2Y) {

					float diffCenterX = currentObject.getPosition().x - otherObject.getPosition().x;
					float diffCenterY = currentObject.getPosition().y - otherObject.getPosition().y;

					sf::Vector2f overlap = {
						objectSize - std::abs(diffCenterX),
						objectSize - std::abs(diffCenterY)
					};

					if (overlap.x < overlap.y) {
						if (diffCenterX > 0) {
							otherObject.move({ -overlap.x / 2, 0 });
							currentObject.move({ overlap.x / 2, 0 });
						}
						else {
							
							otherObject.move({ overlap.x / 2, 0 });
							currentObject.move({ -overlap.x / 2, 0 });
						}
					}
					else {
						if (diffCenterY > 0) {
							otherObject.move({ 0, -overlap.y / 2 });
							currentObject.move({ 0, overlap.y / 2 });
						}
						else {
							otherObject.move({ 0, overlap.y / 2 });
							currentObject.move({ 0, -overlap.y / 2 });
						}
					}
				}
			}
		}
	}


	for (auto& object : m_shapes) {
		object.setFillColor(GV::SHAPECOLOR);
	}
	m_shapes[m_choice].setFillColor(sf::Color::Red);


	//std::cout << m_dt << std::endl;

}

void Engine::render()
{
	m_window.clear(sf::Color::Black);

	for (auto& object : m_shapes) {
		m_window.draw(object);
	}

	m_window.display();
}
