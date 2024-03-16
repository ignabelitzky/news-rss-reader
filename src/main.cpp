#include <iostream>
#include <curl/curl.h>
#include <rapidxml.h>
#include "../include/menu.hpp"


size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    std::string title = "RSS News Reader";
    std::vector<std::string> newspapers = {
        "La Voz del Interior",
        "Clarin",
        "Pagina 12",
        "La Nacion",
        "Infobae",
        "Ambito Financiero",
        "Cronica",
        "El Cronista",
        "CNN",
        "BBC",
        "The New York Times",
        "The Guardian",
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
    if (selection == newspapers.at(1))  // Clarin
    {
        CURL *curl;
        CURLcode res;
        std::string responseBuffer;

        curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://www.clarin.com/rss/lo-ultimo/"); // Set the URL
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);                 // Write the response to a string
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);                   // Set the string to write the response to

            res = curl_easy_perform(curl); // Perform the request, res will get the return code
            if (res != CURLE_OK)
            {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }
            else
            {
                std::cout << responseBuffer << std::endl;
            }
            curl_easy_cleanup(curl); // Clean up
        }
    }
    if (selection == "Exit")
    {
        std::cout << "Goodbye!" << std::endl;
        return 0;
    }
    return 0;
}