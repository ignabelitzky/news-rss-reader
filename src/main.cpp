#include "../include/menu.hpp"
#include "../include/xml_news.hpp"

int main()
{
    initscr();
    std::string title = "RSS News Reader";
    std::vector<std::string> options = {
        "New York Times",
        "CNN",
        "Exit"};
    Menu *menu = nullptr;
    std::string url = "", winTitle = "";
    std::string selection = "";
    try
    {
        menu = new Menu(title, options);
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    do {
        selection = menu->show();
        if(selection == options.at(0)) {
            url = "https://rss.nytimes.com/services/xml/rss/nyt/World.xml";
            winTitle = "New York Times News";
        }
        if(selection == options.at(1)) {
            url = "http://rss.cnn.com/rss/cnn_topstories.rss";
            winTitle = "CNN News";
        }
        if(selection != options.at(2)) {
            XML_news *news = new XML_news(winTitle, url);
            news->showNews();
            touchwin(stdscr);
            wclear(stdscr);
            refresh();
        }
    } while (selection != options.at(2));

    delete menu;
    endwin();
    return 0;
}