#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <curl/curl.h>
#include <rapidxml.h>
#include <ncurses.h>
#include <cwchar>
#include <algorithm>

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

std::string fetch_xml_content(const std::string &url);

void add_window_title(WINDOW *win, const std::string &title);

// Add text to a window, centered horizontally, returns the next y position
int add_centered_text(WINDOW *win, const std::string &text, int y);

#endif