#include "AssignmentOne/AssignmentOne.hpp"

#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <utility>

namespace MunGame
{
	AssignmentOne::AssignmentOne()
		: m_Height(0), m_Width(0)
	{
	}

	AssignmentOne::AssignmentOne(std::string filepath)
		: m_FilePath(std::move(filepath)), m_Height(0), m_Width(0)
	{
	}

	void AssignmentOne::Init()
	{
		std::ifstream inFile(m_FilePath);
		if (!inFile.is_open())
		{
			std::cout << "File not found" << '\n';
			return;
		}

		const size_t lineCount = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');
		m_Shapes.reserve(lineCount - 2);
		inFile.clear();
		inFile.seekg(0, std::ios::beg);

		std::string line;
		int shapeCount = 0;
		while (std::getline(inFile, line))
		{
			std::stringstream lineSS(line);
			constexpr char delimiter = ' ';
			std::string token;
			while (std::getline(lineSS, token, delimiter))
			{
				if (token == "Window")
				{
					std::getline(lineSS, token, delimiter);
					m_Width = std::stoi(token);
					std::getline(lineSS, token, delimiter);
					m_Height = std::stoi(token);
				}
				else if (token == "Font")
				{
					std::string fontPath;
					std::getline(lineSS, fontPath, delimiter);
					std::getline(lineSS, token, delimiter);
					const int fontSize = std::stoi(token);
					std::getline(lineSS, token, delimiter);
					const int red = std::stoi(token);
					std::getline(lineSS, token, delimiter);
					const int blue = std::stoi(token);
					std::getline(lineSS, token, delimiter);
					const int green = std::stoi(token);
					m_FontInfo = FontInfo(sf::Color(red, green, blue), fontSize);
					if (!m_Font.openFromFile(fontPath))
					{
						std::cout << "Font not found" << '\n';
						return;
					}
				}
				else
				{
					const std::string shapeType = token;
					std::string shapeName;
					std::getline(lineSS, shapeName, delimiter);
					std::getline(lineSS, token, delimiter);
					const float shapeXPosition = std::stof(token);
					std::getline(lineSS, token, delimiter);
					const float shapeYPosition = std::stof(token);
					std::getline(lineSS, token, delimiter);
					const float shapeXVelocity = std::stof(token);
					std::getline(lineSS, token, delimiter);
					const float shapeYVelocity = std::stof(token);
					std::getline(lineSS, token, delimiter);
					const int red = std::stoi(token);
					std::getline(lineSS, token, delimiter);
					const int green = std::stoi(token);
					std::getline(lineSS, token, delimiter);
					const int blue = std::stoi(token);

					if (shapeType == "Circle")
					{
						std::getline(lineSS, token, delimiter);
						const float radius = std::stof(token);
						sf::CircleShape circleShape(radius);
						circleShape.setFillColor(sf::Color(red, green, blue));
						ShapeInfo circle(
							ShapeType::Circle,
							sf::Vector2(shapeXPosition, shapeYPosition),
							sf::Vector2(shapeXVelocity, shapeYVelocity),
							m_Font
						);
						circle.m_Circle = std::move(circleShape);
						circle.m_Text.setString(shapeName);
						circle.m_Text.setCharacterSize(m_FontInfo.m_Size);
						circle.m_Text.setFillColor(m_FontInfo.m_Color);
						circle.m_Text.setOutlineColor(sf::Color::Black);
						circle.m_Text.setOutlineThickness(1.F);
						m_Shapes.emplace(m_Shapes.begin() + shapeCount, std::move(circle));
						shapeCount++;
					}
					else if (shapeType == "Rectangle")
					{
						std::getline(lineSS, token, delimiter);
						const float width = std::stof(token);
						std::getline(lineSS, token, delimiter);
						const float height = std::stof(token);
						sf::RectangleShape rectangleShape(sf::Vector2f(width, height));
						rectangleShape.setFillColor(sf::Color(red, green, blue));
						ShapeInfo rectangle(
							ShapeType::Rectangle,
							sf::Vector2(shapeXPosition, shapeYPosition),
							sf::Vector2(shapeXVelocity, shapeYVelocity),
							m_Font
						);
						rectangle.m_Rectangle = std::move(rectangleShape);
						rectangle.m_Text.setString(shapeName);
						rectangle.m_Text.setCharacterSize(m_FontInfo.m_Size);
						rectangle.m_Text.setFillColor(m_FontInfo.m_Color);
						rectangle.m_Text.setOutlineColor(sf::Color::Black);
						rectangle.m_Text.setOutlineThickness(1.F);
						m_Shapes.emplace(m_Shapes.begin() + shapeCount, std::move(rectangle));
						shapeCount++;
					}
				}
			}
		}

		inFile.close();
	}

	void AssignmentOne::Render()
	{
		sf::RenderWindow window(sf::VideoMode({m_Width, m_Height}), "SFML works!");
		constexpr std::uint8_t frameRateLimit = 120;
		window.setFramerateLimit(frameRateLimit);

		while (window.isOpen())
		{
			while (const std::optional event = window.pollEvent())
			{
				if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				{
					window.close();
				}
			}

			window.clear();

			for (ShapeInfo& shape : m_Shapes)
			{
				float sizeX = 0;
				float sizeY = 0;

				if (shape.m_Type == ShapeType::Circle)
				{
					shape.m_Circle.setPosition(shape.m_Position);
					sizeX = sizeY = 2 * shape.m_Circle.getRadius();
					const sf::Vector2<float> textPosition(
						(shape.m_Position.x + (sizeX / 2)) - (shape.m_Text.getLocalBounds().size.x / 2),
						(shape.m_Position.y + (sizeY / 2)) - (shape.m_Text.getLocalBounds().size.y / 2)
					);
					shape.m_Text.setPosition(textPosition);
					window.draw(shape.m_Circle);
					window.draw(shape.m_Text);
				}
				else if (shape.m_Type == ShapeType::Rectangle)
				{
					shape.m_Rectangle.setPosition(shape.m_Position);
					sizeX = shape.m_Rectangle.getSize().x;
					sizeY = shape.m_Rectangle.getSize().y;
					const sf::Vector2<float> textPosition(
						(shape.m_Position.x + (sizeX / 2)) - (shape.m_Text.getLocalBounds().size.x / 2),
						(shape.m_Position.y + (sizeY / 2)) - (shape.m_Text.getLocalBounds().size.y / 2)
					);
					shape.m_Text.setPosition(textPosition);
					window.draw(shape.m_Rectangle);
					window.draw(shape.m_Text);
				}

				if (shape.m_Position.x + shape.m_Velocity.x + sizeX > static_cast<float>(m_Width) || shape.m_Position.x + shape.m_Velocity.x < 0)
				{
					shape.m_Velocity.x *= -1;
				}
				if (shape.m_Position.y + shape.m_Velocity.y + sizeY > static_cast<float>(m_Height) || shape.m_Position.y + shape.m_Velocity.y < 0)
				{
					shape.m_Velocity.y *= -1;
				}

				shape.m_Position += shape.m_Velocity;
			}

			window.display();
		}
	}
} // namespace MunGame
