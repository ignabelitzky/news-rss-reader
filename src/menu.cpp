#include "../include/menu.hpp"

Menu::Menu(std::vector<std::string> items) {
    initialise("", items);
}

Menu::Menu(std::string title, std::vector<std::string> items) {
    initialise(title, items);
}

Menu::~Menu() {
    wclear(menuWin);
    wrefresh(menuWin);
    delwin(menuWin);
}

std::string Menu::show() {
    int key;
    while(true) {
        print_menu();
        key = wgetch(menuWin);
        switch(key) {
            case KEY_UP:
                selectedItem--;
                if(selectedItem == -1) {
                    selectedItem = menuItems.size() - 1;
                }
                break;
            case KEY_DOWN:
                selectedItem++;
                if(selectedItem == static_cast<int>(menuItems.size())) {
                    selectedItem = 0;
                }
                break;
            case 10:    // Enter key
                return menuItems.at(selectedItem);            
            default:
                break;
        }
    }
}

void Menu::calculate_window_dimensions() {
    int maxx, maxy; // Maximum x and y values of the screen
    getmaxyx(stdscr, maxy, maxx);

    height = menuItems.size() * MENU_ITEM_HEIGHT_FACTOR + 3;
    width = longest_menu_item() + MENU_ITEM_PADDING;
    if(width < static_cast<int>(winTitle.length()) + MENU_ITEM_PADDING) {
        width = winTitle.length() + MENU_ITEM_PADDING;
    }

    start_y = (maxy - height) / 2;
    start_x = (maxx - width) / 2;
    if(maxy < height || maxx < width) {
        endwin();
        throw std::runtime_error("Screen is too small to display the menu");
    }
}

int Menu::longest_menu_item() {
    int longest = 0;
    for(int i = 0; i < static_cast<int>(menuItems.size()); ++i) {
        if(static_cast<int>(menuItems.at(i).length()) > longest) {
            longest = menuItems.at(i).length();
        }
    }
    return longest;
}

void Menu::initialise(std::string title, std::vector<std::string> items) {
    if(isendwin() == TRUE) {
        throw std::runtime_error("Cannot create a menu after calling endwin()");
    } else {
        menuItems = items;
        selectedItem = 0;
        winTitle = title;
        calculate_window_dimensions();
        menuWin = newwin(height, width, start_y, start_x);
        curs_set(0);
        keypad(menuWin, TRUE);
        box(menuWin, 0, 0);
    }
}

void Menu::print_menu() {
    wclear(menuWin);
    box(menuWin, 0, 0);
    add_window_title(menuWin, winTitle);
    int y = 2, x = 0;
    for(int i = 0; i < static_cast<int>(menuItems.size()); ++i) {
        i == selectedItem ? wattron(menuWin, A_REVERSE) : wattroff(menuWin, A_REVERSE);
        x = (width - menuItems.at(i).length()) / 2; // Calculate the x position to center the text
        mvwprintw(menuWin, y, x, menuItems.at(i).c_str());
        y += MENU_ITEM_HEIGHT_FACTOR;
    }
    wattroff(menuWin, A_REVERSE);
    wrefresh(menuWin);
}