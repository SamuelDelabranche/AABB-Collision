#include "../header/Engine.hpp"

int main() {
	Engine engine;

	while (engine.isRunning()) {
		engine.restartClock();
		engine.update();
		engine.render();
	}
}