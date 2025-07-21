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
#include "../include/color_parser.hpp"

void fill_color(const std::string &value, uint8_t fill_mode, sf::Color &color){
	if(!is_numerical(value)){
		LOGERROR(value<<" is not a number");
		return;
	}
	uint32_t u32_color = color.toInteger();
	uint8_t num_value = std::stoul(value);
	uint32_t clear[] = {
		~((uint32_t)UCHAR_MAX << 0U),		// A
		~((uint32_t)UCHAR_MAX << 8U),		// B
		~((uint32_t)UCHAR_MAX << 16U),		// G
		~((uint32_t)UCHAR_MAX << 24U)		// R
	};
	
	for(uint32_t filler = PFILL_R; filler > PFILL_NOTHING; filler >>= 1){
		if(filler & fill_mode){
			uint32_t fillid = LOG2(filler);
			u32_color &= clear[fillid];
			u32_color |= num_value << (fillid * COLOR_OFFSET_BITS);
		}
	}
	color = sf::Color(u32_color);
}

parsed_colors parse_colors(const std::string &path){
	sf::Color new_color = DEFAULT_COLOR;
	parsed_colors colors = {};
	bool comment = false;
	bool met_color = false;
	size_t line = 1;
	size_t col = 0;
	bool reset_col = false;
	uint8_t fill_mode = PFILL_NOTHING;
	std::vector<char> src = read_file(path);
	std::string token = "";
	
	for(const char c : src){
		if(!reset_col){
			col++;
		}
		else{
			reset_col = false;
		}
		if(comment && c != '\n'){
			continue;
		}
		switch(c){
			case '0' ... '9':{
				met_color = true;
				token.push_back(c);
			}break;
			case 'a':
			case 'A':
				fill_mode |= PFILL_A;
			break;
			case 'r':
			case 'R':
				fill_mode |= PFILL_R;
			break;
			case 'g':
			case 'G':
				fill_mode |= PFILL_G;
			break;
			case 'b':
			case 'B':
				fill_mode |= PFILL_B;
			break;
			case '#':{
				comment = true;
				if(met_color){
					fill_color(token, fill_mode, new_color);
					colors.colors.push_back(new_color);
					new_color = DEFAULT_COLOR;
					token.clear();
					met_color = false;
					fill_mode = PFILL_NOTHING;
				}
			}break;
			case ',':{
				if(met_color){
					fill_color(token, fill_mode, new_color);
					token.clear();
					fill_mode = PFILL_NOTHING;
				}
			}break;
			case '\n':{
				comment = false;
				line++;
				col = 0;
				reset_col = true;
				if(met_color){
					fill_color(token, fill_mode, new_color);
					colors.colors.push_back(new_color);
					new_color = DEFAULT_COLOR;
					token.clear();
					met_color = false;
					fill_mode = PFILL_NOTHING;
				}
			}break;
		}
	}
	
	return colors;
}

sf::Color get_color_from(const parsed_colors &colors, size_t idx){
	return idx < colors.colors.size() ? colors.colors[idx] : DEFAULT_COLOR;
}