#ifndef XML_NEWS_HPP
#define XML_NEWS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "../include/utils.hpp"

struct News {
    std::string title;
    std::string link;
    std::string description;
};

class XML_news {
    public:
        XML_news(const std::string &title, const std::string &url);
        ~XML_news();
        void printXML();    // This method is for debugging purposes
        void showNews();    // This method prints the news in the ncurses window
    private:
        WINDOW *newsWin;
        WINDOW *infoWin;
        WINDOW *menuWin;
        int start_x, start_y, width, height;
        std::string winTitle;
        std::string url;
        std::vector<News> news;
        std::string xmlContent;
        void initialise();  // This method is called by the constructors
        void createXML(const std::string &url);
        void parseXML();
        void calculate_window_dimensions();
};

#endif