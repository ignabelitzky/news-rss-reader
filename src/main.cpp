#include "../include/menu.hpp"
#include "../include/xml_news.hpp"

int main()
{
    initscr();
    std::string title = "RSS News Reader";
    std::vector<std::string> newspapers = {
        "CNN",
        "Exit"};
    Menu *menu = nullptr;
    try
    {
        menu = new Menu(title, newspapers);
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::string selection = menu->show();
    delete menu;
    if (selection == newspapers.at(0)) // CNN
    {
        std::string url = "http://rss.cnn.com/rss/cnn_topstories.rss";
        std::string title = "CNN News";
        XML_news *news = new XML_news(title, url);
        news->showNews();
    }
    if (selection == "Exit")
    {
        std::cout << "Goodbye!" << std::endl;
    }
    getch();
    endwin();
    return 0;
}