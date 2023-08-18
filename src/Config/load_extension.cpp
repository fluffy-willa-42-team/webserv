#include "webserv.hpp"

#define NB_EXTENSION 15
#define EXTENSION {\
	{ "",		"text/plain" },\
	{ "html",	"text/html" },\
	{ "css",	"text/css" },\
	{ "js",		"text/javascript" },\
	{ "json",	"application/json" },\
	{ "xml",	"application/xml" },\
	{ "pdf",	"application/pdf" },\
	{ "jpeg",	"image/jpeg" },\
	{ "jpg",	"image/jpeg" },\
	{ "png",	"image/png" },\
	{ "gif",	"image/gif" },\
	{ "mpeg",	"audio/mpeg" },\
	{ "wav",	"audio/wav" },\
	{ "mp4",	"video/mp4" },\
	{ "avi",	"video/avi" }\
}

typedef struct {
    const char* extension;
    const char* type;
}	t_extension;

map<string, string> get_extension_map(){
	map<string, string> res;
	t_extension array[] = EXTENSION;
	for (int i = 0; i < NB_EXTENSION; i++){
		res[(array[i].extension)] = array[i].type;
	}
	return res;
}