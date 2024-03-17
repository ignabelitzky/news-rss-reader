#include "../include/xml_news.hpp"

XML_news::XML_news(const std::string &title, const std::string &url) : winTitle(title), url(url)
{
    initialise();
}

XML_news::~XML_news()
{
    wclear(infoWin);
    wrefresh(infoWin);
    delwin(infoWin);
    wclear(menuWin);
    wrefresh(menuWin);
    delwin(menuWin);
    wclear(newsWin);
    wrefresh(newsWin);
    delwin(newsWin);
}

void XML_news::printXML()
{
    std::cout << xmlContent << std::endl;
}

void XML_news::showNews()
{
}

void XML_news::initialise()
{
    calculate_window_dimensions();
    newsWin = newwin(height, width, start_y, start_x);
    box(newsWin, 0, 0);
    // TODO
}

void XML_news::createXML(const std::string &url)
{
    xmlContent = fetchXmlContent(url);
}

void XML_news::parseXML()
{
    rapidxml::xml_document<> doc;
    doc.parse<0>(&xmlContent[0]);
    rapidxml::xml_node<> *root = doc.first_node();
    for (rapidxml::xml_node<> *item = root->first_node("item"); item; item = item->next_sibling())
    {
        News n;
        n.title = item->first_node("title")->value();
        n.link = item->first_node("link")->value();
        n.description = item->first_node("description")->value();
        news.push_back(n);
    }
}

void XML_news::calculate_window_dimensions()
{
    int maxx, maxy; // Maximum x and y values of the screen
    getmaxyx(stdscr, maxy, maxx);

    height = maxy;
    width = maxx;
    start_y = 0;
    start_x = 0;
}