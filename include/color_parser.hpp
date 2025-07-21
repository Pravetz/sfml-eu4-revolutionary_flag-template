/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#ifndef EU4RVF_COLOR_PARSER_HPP
#define EU4RVF_COLOR_PARSER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cstdint>
#include <climits>
#include "logging.hpp"
#include "readfile.hpp"
#include "check_numerical.hpp"

#define DEFAULT_COLOR sf::Color(0,0,0,255)
#define COLOR_OFFSET_BITS 8
#define LOG2(x) ((sizeof(x) * CHAR_BIT - 1) - __builtin_clz(x))

enum PCOLOR_FILL_MODE : uint8_t {
	PFILL_NOTHING = 0,
	PFILL_R = 1 << 3,
	PFILL_G = 1 << 2,
	PFILL_B = 1 << 1,
	PFILL_A = 1 << 0
};

struct parsed_colors {
	std::vector<std::string> errors;
	std::vector<sf::Color> colors;
};

void fill_color(const std::string &value, uint8_t fill_mode, sf::Color &color); 
parsed_colors parse_colors(const std::string &path);
sf::Color get_color_from(const parsed_colors &colors, size_t idx);

#endif