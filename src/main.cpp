#include "../include/menu.hpp"
#include "../include/xml_news.hpp"

int main()
{
    initscr();
    std::string title = "RSS News Reader";
    std::vector<std::string> options = {
        "CNN",
        "Exit"};
    Menu *menu = nullptr;
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
            std::string url = "http://rss.cnn.com/rss/cnn_topstories.rss";
            std::string title = "CNN News";
            XML_news *news = new XML_news(title, url);
            news->showNews();
            touchwin(stdscr);
            wclear(stdscr);
            refresh();
        }
    } while (selection != options.at(1));

    delete menu;
    endwin();
    return 0;
}