#include "JsonObject.h"

#include <cpprest/json.h>
using namespace web;


JsonObject::JsonObject()
{
}


JsonObject::~JsonObject()
{
}

void JsonObject::fromJson(const TSTRING& string) {
	json::value obj = json::value::parse(string);
	this->fromJsonObject(obj);
}

TSTRING JsonObject::toJson() {
	json::value obj;
	this->toJsonObject(obj);

	return obj.to_string();
}