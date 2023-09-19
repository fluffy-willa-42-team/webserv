#ifndef FILE_PARSING_HPP
# define FILE_PARSING_HPP

/******************************************************************************/

#include "Config.hpp"
#include "request_validation.hpp"

/******************************************************************************/

bool is_a_file_path							(const string& input);
bool is_a_http_path							(const string& input);
bool is_bool								(const string& input);

e_status parseline(ifstream& file, string& line, vector<string>& line_split, e_status& status, u_int32_t& index);

bool is_server_line							(vector<string>& line_split);
bool is_server_option_server_name			(vector<string>& line_split);
bool is_server_option_listen				(vector<string>& line_split);
bool is_server_option_error_page			(vector<string>& line_split);
bool is_server_option_max_client_body_size	(vector<string>& line_split);

bool is_location_line						(vector<string>& line_split);
bool is_location_index						(vector<string>& line_split);
bool is_location_root						(vector<string>& line_split);
bool is_location_allow_methods				(vector<string>& line_split);
bool is_location_return						(vector<string>& line_split);
bool is_location_cgi_pass					(vector<string>& line_split);
bool is_location_download_file				(vector<string>& line_split);
bool is_location_autoindex					(vector<string>& line_split);

/******************************************************************************/

#endif /* FILE_PARSING_HPP */