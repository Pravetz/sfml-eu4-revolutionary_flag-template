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

#include <iostream>
#include <unordered_map>
#include <fstream>

#include "include/color_parser.hpp"
#include "include/settings_parser.hpp"

#define ALLOCATE_SPRITE_AT(s, pos) s.setPosition((w / 3) * pos, 0)

int main(int argc, char** argv){
	parsed_config cfg = parse_config("assets/settings.cfg");
	parsed_colors colors = parse_colors("assets/colors.txt");
	int32_t w = cfg.values.at("w").data.integer;
	int32_t h = cfg.values.at("h").data.integer;
	int32_t bpp = cfg.values.at("bpp").data.integer;
	int32_t save_int = cfg.values.at("save").data.integer;
	for(const auto &error : cfg.errors){
		LOGERROR(error);
	}
	for(const auto &error : colors.errors){
		LOGERROR(error);
	}
	if(!cfg.errors.empty() || !colors.errors.empty()){
		return EXIT_FAILURE;
	}
	
	sf::RenderWindow app(sf::VideoMode(w, h, bpp), "SFML Revolutionary flag template by Pravetz");
	
	int stripe_colors[] = {0, 0, 0};
	for(int i = 1; i < argc && i < 4; i++){
		if(is_numerical(argv[i])){
			stripe_colors[i - 1] = std::atoi(argv[i]);
		}
		else{
			LOGERROR(argv[i]<<" is not an integer, using default value 0 for stripe №"<<i);
		}
	}
	
	LOGINFO("Generate IDs: "<<stripe_colors[0]<<" "<<stripe_colors[1]<<" "<<stripe_colors[2]);
	
	sf::RenderTexture texture;
	
	if (!texture.create(w, h)){
		return EXIT_FAILURE;
	}
	
	sf::Image stripe_image;
	stripe_image.create(w / 3, h, sf::Color::White);
	
	sf::Texture stripe;
	if(!stripe.loadFromImage(stripe_image)){
		return EXIT_FAILURE;
	}
	
	sf::Sprite s(stripe);
	sf::Sprite s1(stripe);
	sf::Sprite s2(stripe);
	
	ALLOCATE_SPRITE_AT(s, 0);
	ALLOCATE_SPRITE_AT(s1, 1);
	ALLOCATE_SPRITE_AT(s2, 2);
	
	s.setColor(get_color_from(colors, stripe_colors[0]));
	s1.setColor(get_color_from(colors, stripe_colors[1]));
	s2.setColor(get_color_from(colors, stripe_colors[2]));
	
	texture.clear(sf::Color::Black);
	
	texture.draw(s);
	texture.draw(s1);
	texture.draw(s2);
	
	while (app.isOpen()){
		sf::Event event;
        while (app.pollEvent(event)){
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				app.close();
			}
		}
	
		texture.display();
	
		app.clear(sf::Color::White);
	
		sf::Sprite sprite(texture.getTexture());
	
		app.draw(sprite);
		app.display();
	}
	
	std::string SAVED_FILENAME = cfg.values.at("save_path").data.str
							   + std::to_string(stripe_colors[0]) + " "
							   + std::to_string(stripe_colors[1]) + " "
							   + std::to_string(stripe_colors[2]) + ".png";
	if(save_int == 1){
		texture.getTexture().copyToImage().saveToFile(SAVED_FILENAME);
		LOGSUCCESS("Successfully saved revolutionary flag to file \'"<<SAVED_FILENAME<<'\'');
	}
	if(cfg.damaged){
		LOGINFO("it appears that program config was damaged or deleted, saving repaired version...");
		save_config(cfg, "assets/settings.cfg");
	}
	return EXIT_SUCCESS;
}
