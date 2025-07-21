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
#ifndef EU4RVF_CFG_PARSER_HPP
#define EU4RVF_CFG_PARSER_HPP

#include <utility>
#include <unordered_map>
#include <new>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include "logging.hpp"
#include "readfile.hpp"
#include "check_numerical.hpp"

enum CFV_TYPE : uint8_t {
	CFV_UNKNOWN = 0,
	CFV_INTEGER = 1,
	CFV_STRING = 2
};

struct config_value {
	uint8_t type;
	union cfv_data {
		int64_t integer;
		std::string str;
		cfv_data();
		~cfv_data();
	} data;
	config_value();
	config_value(const uint8_t type, int64_t intv);
	config_value(const uint8_t type, const std::string &str);
	config_value(const config_value &cfv);
	config_value(const config_value &&cfv);
	config_value& operator=(const config_value &cfv);
	~config_value();
};

struct parsed_config {
	bool damaged:		1;
	std::vector<std::string> errors;
	std::unordered_map<std::string, config_value> values;
};

typedef std::unordered_map<std::string, uint8_t> expected_arg_map;
typedef std::unordered_map<std::string, config_value> default_arg_map;

std::ostream& operator<<(std::ostream& os, const config_value& cfv);
extern const expected_arg_map expected_args;
config_value create_cfg_value(parsed_config &cfg, const std::string &token, const uint8_t type);
void config_fill_defaults(parsed_config &cfg);
parsed_config parse_config(const std::string &path);
void save_config(const parsed_config &cfg, const std::string &path);

#endif