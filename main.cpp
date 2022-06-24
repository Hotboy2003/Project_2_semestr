#include <SFML/Graphics.hpp>
#include <scene.hpp>
#include <string>

int main()
{
	setlocale(LC_ALL, "Russian");
	ao::Scene scene(1920, 1080);
	scene.LifeCycle();
	return 0;
}
