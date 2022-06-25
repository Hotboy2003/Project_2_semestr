#include <scene.hpp>
#include <fstream>
#include <functional>

namespace ao
{
	Scene::Scene(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_width, m_height), "3D Engine");
		m_texture = std::make_unique<sf::Texture>();
		m_texture->create(m_width, m_height);
		m_sprite = std::make_unique<sf::Sprite>(*m_texture);

		Intrinsic intrinsic = { 960.0, 540.0, 960.0, 540.0 };
		Angles angles = { 0.0,0.0,0.0 };
		
		m_color = new color[30000000];
		m_points = new Point[30000000];

		double k, a, b, c;
		std::cout << "Введите число от 1 до 3. 1 - Конус. 2 - Эллиптический параболоид. 3 - Пересекающиеся прямые. 4 - Гиперболический параболоид." << std::endl;
		std::cout << "5 - считать с файла" << std::endl;
		std::cout << "Предупреждение! Если вы захотите считать с файла, то считывая координаты больше 1 млн, вы окажетесь слишком далеко от точек, которые программа считала" << std::endl;
		
		bool flag = true;
		while (flag) {
			std::cin >> k;
			if (k < 5 && k >= 1)
			{
				std::cout << "Теперь введите направляющие векторы фигуры (a,b,c)" << std::endl;
				std::cout << "Предупреждение! Если вы введете слишком большие направляющие, то велика вероятность, что фигура не отрисуется.";
				std::cin >> a >> b >> c;
				flag = false;
			}
			if (k == 1)
			{
				Konus(a, b, c);
				Point position = { 0.0, 0.0, 0.0 };
				m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);
			}
			if (k == 2)
			{
				El_Paraboloid(a, b);
				Point position = { 0.0, 0.0, 0.0 };
				m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);
			}
			if (k == 3)
			{
				Pryamye(a, b);
				Point position = { 0.0, 0.0, 0.0 };
				m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);
			}
			if (k == 4)
			{
				Hyp_Paraboloid(a, b);
				Point position = { 0.0, 0.0, 0.0 };
				m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);
			}
			if (k == 5)
			{
				flag = false;
				std::ifstream in("points_1.txt");

				if (!in.is_open())
					std::cerr << "File not found" << std::endl;
				else
					std::cerr << "File is OK!" << std::endl;

				while (!in.eof())
				{
					int r, g, b;
					in >> m_points[m_size].x >> m_points[m_size].y >> m_points[m_size].z >> r >> g >> b;
					m_color[m_size].r = r;
					m_color[m_size].g = g;
					m_color[m_size].b = b;
					m_size++;
				}
				Point position = { m_points[1].x, m_points[1].y, m_points[1].z };
				m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);
			}
			if ( k < 1 || k > 5)
			{
				std::cout << "Серьезно? Давайте попробуем еще раз!";
			}
		}
	}
	Scene::~Scene()
	{
		if (m_points != nullptr)
			delete[] m_points;
	}

	void Scene::Konus(double a,double b, double c)
	{
		for (double x = -127; x < 127; x++)
			for (double y = -127; y < 127; y++)
			{
				double x_2 = pow(x, 2);
				double y_2 = pow(y, 2);
				double a_2 = pow(a, 2);
				double b_2 = pow(b, 2);
				double c_2 = pow(c, 2);

				m_points[m_size].x = x;
				m_points[m_size].y = y;
				m_points[m_size].z = sqrt((x_2 * c_2) / a_2 + (y_2 * c_2) / b_2);
				m_color[m_size].r = 127 - int(x);
				m_color[m_size].g = int(x) + 127;
				m_color[m_size].b = int(x) + 127;
				m_size++;
				m_points[m_size].x = x;
				m_points[m_size].y = y;
				m_points[m_size].z = -sqrt((x_2 * c_2) / a_2 + (y_2 * c_2) / b_2);
				m_color[m_size].r = int(x) + 127;
				m_color[m_size].g = 127 - int(x);
				m_color[m_size].b = int(x) + 127;
				m_size++;
			}
	}

	void Scene::El_Paraboloid(double a, double b)
	{
		for (double x = -127; x < 127; x++)
			for (double y = -127; y < 127; y++)
			{
				double x_2 = pow(x, 2);
				double y_2 = pow(y, 2);
				double a_2 = pow(a, 2);
				double b_2 = pow(b, 2);

				m_points[m_size].x = x;
				m_points[m_size].y = y;
				m_points[m_size].z = (x_2/a_2 + y_2/b_2) / 2;
				m_color[m_size].r = 127 - int(x);
				m_color[m_size].g = int(x) + 127;
				m_color[m_size].b = int(x) + 127;
				m_size++;
			}
	}

	void Scene::Pryamye(double a, double b)
	{
		for (double x = -127; x < 127; x++)
		{
			double x_2 = pow(x, 2);
			double a_2 = pow(a, 2);
			double b_2 = pow(b, 2);

			m_points[m_size].x = x;
			m_points[m_size].y = sqrt(x_2*b_2/a_2);
			m_color[m_size].r = 127 - int(x);
			m_color[m_size].g = int(x) + 127;
			m_color[m_size].b = int(x) + 127;
			m_size++;
			m_points[m_size].x = x;
			m_points[m_size].y = -sqrt(x_2 * b_2 / a_2);
			m_color[m_size].r = 127 - int(x);
			m_color[m_size].g = int(x) + 127;
			m_color[m_size].b = int(x) + 127;
			m_size++;
		}
	}

	void Scene::Hyp_Paraboloid(double a, double b)
	{
		for (double x = -127; x < 127; x++)
			for (double y = -127; y < 127; y++)
			{
				double x_2 = pow(x, 2);
				double y_2 = pow(y, 2);
				double a_2 = pow(a, 2);
				double b_2 = pow(b, 2);

				m_points[m_size].x = x;
				m_points[m_size].y = y;
				m_points[m_size].z = (x_2 / a_2 - y_2 / b_2) / 2;
				m_color[m_size].r = 127 - int(x);
				m_color[m_size].g = int(x) + 127;
				m_color[m_size].b = int(x) + 127;
				m_size++;
			}
	}

	void Scene::LifeCycle()
	{
		while (m_window->isOpen()) {
			sf::Event event;
			while (m_window->pollEvent(event))
				if (event.type == sf::Event::Closed)
					m_window->close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				m_camera->dZ(10.1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_camera->dZ(-10.1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_camera->dX(-10.1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_camera->dX(10.1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				m_camera->dPitch(-0.12);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				m_camera->dPitch(0.12);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				m_camera->dRoll(-0.12);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				m_camera->dRoll(0.12);
			}

	
			for (int i = 0; i < m_size; i++)
				m_camera->ProjectPoint(m_points[i], { m_color[i].r, m_color[i].g ,m_color[i].b, 255 });

			m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
			m_camera->Clear();


			m_window->clear();
			m_window->draw(*m_sprite);

			m_window->display();

		}
	}
}
