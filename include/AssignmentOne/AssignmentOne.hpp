#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

namespace MunGame
{
	enum class ShapeType : std::uint8_t
	{
		Circle,
		Rectangle
	};

	struct FontInfo
	{
	public:
		sf::Color m_Color;
		std::uint16_t m_Size;
		sf::Font m_Font;

		FontInfo()
			: m_Size(0.F)
		{
		}

		FontInfo(const sf::Color& color, const std::uint16_t size)
			: m_Color(color), m_Size(size)
		{
		}
	};

	struct ShapeInfo
	{
	public:
		ShapeType m_Type;
		sf::Vector2<float> m_Position;
		sf::Vector2<float> m_Velocity;
		sf::CircleShape m_Circle;
		sf::RectangleShape m_Rectangle;
		sf::Text m_Text;

		ShapeInfo() = default;
		ShapeInfo(const ShapeType shapeType, const sf::Vector2<float>& position, const sf::Vector2<float>& velocity, const sf::Font& font)
			: m_Type(shapeType), m_Position(position), m_Velocity(velocity), m_Text(font)
		{
		}
	};

	class AssignmentOne
	{
	public:
		AssignmentOne();
		explicit AssignmentOne(std::string filepath);

		void Init();
		void Render();

	private:
		std::string m_FilePath;
		std::uint16_t m_Height;
		std::uint16_t m_Width;
		sf::Font m_Font;
		FontInfo m_FontInfo;
		std::vector<ShapeInfo> m_Shapes;
	};
} // namespace MunGame
