#include "../include/xml_news.hpp"

XML_news::XML_news(const std::string &title, const std::string &url) : winTitle(title), url(url)
{
    initialise();
}

XML_news::~XML_news()
{
    if(infoWin != nullptr)
    {
        wclear(infoWin);
        delwin(infoWin);
    }
    if(menuWin != nullptr)
    {
        wclear(menuWin);
        delwin(menuWin);
    }
    if(newsWin != nullptr)
    {
        wclear(newsWin);
        delwin(newsWin);
    }
}

void XML_news::printXML()
{
    std::cout << xmlContent << std::endl;
}

void XML_news::showNews()
{
    wrefresh(newsWin);
    wrefresh(infoWin);
    wrefresh(menuWin);
    int option = wgetch(menuWin);
    while (option != 'q')
    {
        option = wgetch(menuWin);
    }
    delwin(menuWin);
    delwin(infoWin);
    delwin(newsWin);
    echo();
}

void XML_news::initialise()
{
    parseXML();
    calculate_window_dimensions();
    noecho();
    
    newsWin = subwin(stdscr, height, width, start_y, start_x);
    box(newsWin, 0, 0);
    add_window_title(newsWin, winTitle);
    
    infoWin = subwin(newsWin, height - 7, width - 4, start_y + 1, start_x + 2);
    // box(infoWin, 0, 0);
    scrollok(infoWin, TRUE);
    for(int i = 0; i < static_cast<int>(news.size()); i++)
    {
        add_centered_text(infoWin, "Title", i * 7 + 1);
        add_centered_text(infoWin, news.at(i).title, i * 7 + 2);
        add_centered_text(infoWin, "Description", i * 7 + 3);
        add_centered_text(infoWin, news.at(i).description, i * 7 + 4);
        add_centered_text(infoWin, "Link", i * 7 + 5);
        add_centered_text(infoWin, news.at(i).link, i * 7 + 6);
        add_centered_text(infoWin, " ", i * 7 + 7);
    }

    menuWin = subwin(newsWin, 5, width - 4, start_y + height - 6, start_x + 2);
    box(menuWin, 0, 0);
    int y = getmaxy(menuWin);
    add_centered_text(menuWin, "Press 'q' to go to the menu", y/2);
}

void XML_news::createXML()
{
    xmlContent = fetch_xml_content(url);
}

void XML_news::parseXML()
{
    createXML();
    rapidxml::xml_document<> doc;
    doc.parse<0>(&xmlContent[0]);
    rapidxml::xml_node<> *root = doc.first_node();
    for(rapidxml::xml_node<> *item = root->first_node("channel")->first_node("item"); item; item = item->next_sibling())
    {
        // I got to improve this part of the code
        News n;
        n.title = item->first_node("title")->first_node()->value();
        n.link = item->first_node("link")->value();
        if(item->first_node("description") != nullptr)
        {
            n.description = item->first_node("description")->first_node()->value();
        }
        else
        {
            n.description = "No description available";
        }
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