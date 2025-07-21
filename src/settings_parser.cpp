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
#include "../include/settings_parser.hpp"

config_value::cfv_data::cfv_data(){
	
}
config_value::cfv_data::~cfv_data(){
	
}
config_value::config_value(){
	LOGINFO("called empty constructor");
	this->type = CFV_UNKNOWN;
	this->data.integer = 0;
}
config_value::config_value(const config_value &&cfv){
	this->type = cfv.type;
	switch(this->type){
		case CFV_UNKNOWN:
			this->data.integer = 0;
		break;
		case CFV_INTEGER:
			this->data.integer = cfv.data.integer;
		break;
		case CFV_STRING:
			new (&this->data.str) std::string(cfv.data.str);
		break;
	}
}

config_value& config_value::operator=(const config_value &cfv){
	this->type = cfv.type;
	switch(this->type){
		case CFV_UNKNOWN:
			this->data.integer = 0;
		break;
		case CFV_INTEGER:
			this->data.integer = cfv.data.integer;
		break;
		case CFV_STRING:
			new (&this->data.str) std::string(cfv.data.str);
		break;
	}
	return *this;
}

config_value::config_value(const uint8_t type, int64_t intv){
	this->type = type;
	this->data.integer = intv;
}
config_value::config_value(const uint8_t type, const std::string &str){
	this->type = type;
	new (&this->data.str) std::string(str);
}
config_value::config_value(const config_value &cfv){
	this->type = cfv.type;
	switch(this->type){
		case CFV_UNKNOWN:
			this->data.integer = 0;
		break;
		case CFV_INTEGER:
			this->data.integer = cfv.data.integer;
		break;
		case CFV_STRING:
			new (&this->data.str) std::string(cfv.data.str);
		break;
	}
}

config_value::~config_value(){
	switch(this->type){
		case CFV_STRING: this->data.str.~basic_string(); break;
		default: return;
	}
}

extern const expected_arg_map expected_args = {
	{ "w", CFV_INTEGER },
	{ "h", CFV_INTEGER },
	{ "bpp", CFV_INTEGER },
	{ "save", CFV_INTEGER },
	{ "save_path", CFV_STRING }
};

config_value create_cfg_value(parsed_config &cfg, const std::string &token, const uint8_t type){
	switch(type){
		case CFV_INTEGER:{
			if(!is_numerical(token)){
				if(cfg.values.find(token) != cfg.values.end() &&
				   cfg.values.at(token).type == type){
					return config_value(cfg.values.at(token));
				}
				return config_value(CFV_UNKNOWN, 0);
			}
			return config_value(CFV_INTEGER, std::stoll(token));
		}
		case CFV_STRING: return config_value(CFV_STRING, token);
	}
	return config_value(CFV_UNKNOWN, 0);
}

void config_fill_defaults(parsed_config &cfg){
	static const default_arg_map defaults = {
		{ "w", config_value(CFV_INTEGER, 300) },
		{ "h", config_value(CFV_INTEGER, 200) },
		{ "bpp", config_value(CFV_INTEGER, 32) },
		{ "save", config_value(CFV_INTEGER, 1) },
		{ "save_path", config_value(CFV_STRING, "./") }
	};
	
	for(const auto &d : defaults){
		if(cfg.values.find(d.first) == cfg.values.end()){
			cfg.damaged = true;
			cfg.values.emplace(d.first, d.second);
		}
		else if(cfg.values.at(d.first).type == CFV_UNKNOWN){
			cfg.damaged = true;
			cfg.values.at(d.first) = d.second;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const config_value& cfv){
	switch(cfv.type){
		case CFV_UNKNOWN: os << "UNKNOWN"; break;
		case CFV_INTEGER: os << cfv.data.integer; break;
		case CFV_STRING: os << cfv.data.str; break;
	}
	return os;
}

parsed_config parse_config(const std::string &path){
	parsed_config cfg = {};
	size_t line = 1;
	size_t col = 0;
	bool reset_col = false;
	bool comment = false;
	bool lvalue = false;
	bool rvalue = false;
	std::vector<char> src = read_file(path);
	std::string new_entry = "";
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
			case '=': {
				if(!lvalue){
					cfg.errors.push_back(INJECT_FLINECOL(path, line, col) + " error: can\'t set unknown settings key");
					break;
				}
				if(expected_args.find(token) == expected_args.end()){
					cfg.errors.push_back(INJECT_FLINECOL(path, line, col) + " error: unexpected settings key \'" + token + "\'");
					break;
				}
				new_entry = token;
				token.clear();
				rvalue = true;
				lvalue = false;
			}break;
			case '#':{
				comment = true;
				if(rvalue){
					cfg.values.emplace(new_entry, create_cfg_value(cfg, token, expected_args.at(new_entry)));
					if(cfg.values.at(new_entry).type != expected_args.at(new_entry)){
						cfg.errors.push_back(INJECT_FLINECOL(path, line, col) + " error: invalid value for key \'" + token + "\'");
					}
					token.clear();
					rvalue = false;
				}
			}break;
			case '\n':{
				comment = false;
				line++;
				col = 0;
				reset_col = true;
				if(rvalue){
					cfg.values.emplace(new_entry, create_cfg_value(cfg, token, expected_args.at(new_entry)));
					if(cfg.values.at(new_entry).type != expected_args.at(new_entry)){
						cfg.errors.push_back(INJECT_FLINECOL(path, line, col) + " error: invalid value for key \'" + token + "\'");
					}
					token.clear();
					rvalue = false;
				}
			}break;
			case ' ':
			case '\t':
			case '\v':
				if(!rvalue || expected_args.at(new_entry) != CFV_STRING){
					break;
				}
			default:{
				token.push_back(c);
				if(!rvalue){
					lvalue = true;
				}
			}break;
		}
	}
	
	config_fill_defaults(cfg);
	return cfg;
}

void save_config(const parsed_config &cfg, const std::string &path){
	std::ofstream _save_file;
	_save_file.open(path.c_str());
	if(_save_file){
		for(const auto &kv : cfg.values){
			_save_file << kv.first << " = " << kv.second << '\n';
		}
		_save_file.close();
		LOGSUCCESS("successfully saved config to \'"<<path<<'\'');
	}
	else{
		LOGERROR("failed to save config to \'"<<path<<'\'');
	}
}