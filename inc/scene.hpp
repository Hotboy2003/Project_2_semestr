#pragma once
#include <SFML/Graphics.hpp>
#include <camera.hpp>

namespace ao
{
	class Scene
	{
	public:
		Scene(int width, int height);
		~Scene();
		void Konus(double a,double b,double c);
		void El_Paraboloid(double a, double b);
		void Pryamye(double a, double b);
		void Hyp_Paraboloid(double a, double b);
		void LifeCycle();

	private:
		std::unique_ptr<Camera> m_camera;

		int m_width;
		int m_height;

		std::unique_ptr<sf::RenderWindow> m_window;
		std::unique_ptr<sf::Texture> m_texture;
		std::unique_ptr<sf::Sprite> m_sprite;
		color* m_color = nullptr;
		Point* m_points = nullptr;
		int m_size = 0;
	};
}
