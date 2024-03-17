#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <curl/curl.h>
#include <rapidxml.h>

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);

std::string fetchXmlContent(const std::string &url);

#endif