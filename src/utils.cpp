#include "../include/utils.hpp"

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string fetch_xml_content(const std::string &url)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "Failed to initialize curl" << std::endl;
        return "";
    }
    std::string responseBuffer;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK)
    {
        std::cerr << "Failed to fetch content from " << url << std::endl;
        return "";
    }
    return responseBuffer;
}

void add_window_title(WINDOW *win, const std::string &title)
{
    std::string fullTitle = " [ " + title + " ]";
    int maxx = getmaxx(win);
    int fullTitleLength = fullTitle.length();
    int startx = (maxx - fullTitleLength) / 2;
    mvwprintw(win, 0, startx, fullTitle.c_str());
    wrefresh(win);
}

int add_centered_text(WINDOW *win, const std::string &text, int y)
{
    std::string textCopy = text;
    int maxx = getmaxx(win);
    int textLength = textCopy.length();
    if(textLength < maxx - 4) {
        int startx = (maxx - textLength) / 2;
        mvwaddstr(win, y, startx, textCopy.c_str());
        wrefresh(win);
        y++;
    } else {
        int startx = 2;
        int endx = maxx - 2;
        int textPos = 0;
        int textLength = textCopy.length();
        while(textPos < textLength) {
            std::string line = textCopy.substr(textPos, endx - 4);
            mvwaddstr(win, y, startx, line.c_str());
            wrefresh(win);
            textPos += endx - 4;
            y++;
        }
    }
    return y;
}