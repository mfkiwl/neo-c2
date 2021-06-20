#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#include <dirent.h>
#include <sys/stat.h>

void ViWin_commandModeView(ViWin* self, Vi* nvi) 
{
    werase(self.win);

    self.textsView(nvi);

    wattron(self.win, A_REVERSE);
    mvwprintw(self.win, self.height-1, 0, ":%s", nvi.commandString);
    wattroff(self.win, A_REVERSE);

    wrefresh(self.win);
}

string ViWin_selector(ViWin* self, list<string>* lines) 
{
    bool end_of_select = false;
    bool canceled = false;

    int maxx = getmaxx(self.win);
    int maxy = getmaxy(self.win);

    int scrolltop = 0;
    int cursor = 0;

    while(!end_of_select) {
        clear();
        int maxy2 = lines.length() - scrolltop;

        ### view ###
        for(int y=0; y<maxy && y < maxy2; y++) {
            var it = lines.item(scrolltop+y, null);

            var line = it.substring(0, maxx-1);

            if(cursor == y) {
                attron(A_REVERSE);
                mvprintw(y, 0, "%s", line);
                attroff(A_REVERSE);
            }
            else {
                mvprintw(y, 0, "%s", line);
            }
        }
        refresh();

        ### input ###
        var key = getch();

        switch(key) {
            case KEY_UP:
            case 'k':
            case 'P'-'A'+1:
                cursor--;
                break;

            case KEY_DOWN:
            case 'j':
            case 'N'-'A'+1:
            case (('I'-'A')+1):
                cursor++;
                break;

            case 'D'-'A'+1:
                cursor+=10;
                break;
           
            case (('U'-'A')+1):
                cursor-=10;
                break;

            case ('C'-'A')+1:
            case 'q':
            case ('['-'A')+1:
                canceled = true;
                end_of_select = true;
                break;

            case KEY_ENTER:
            case ('J'-'A')+1:
                end_of_select = true;
                break;
        }
        
        ### modification ###
        if(cursor < 0) {
            int scroll_size = -cursor +1;
            
            cursor = 0;
            scrolltop-=scroll_size;

            if(scrolltop < 0) {
                scrolltop = 0;
                cursor = 0;
            }
        }

        if(maxy2 < maxy) {
            if(cursor >= maxy2) {
                cursor = maxy2 - 1;
            }
        }
        else {
            if(cursor >= maxy) {
                int scroll_size = cursor - maxy + 1;

                scrolltop += scroll_size;
                cursor -= scroll_size;
            }
        }
    }

    if(canceled) {
        return string("");
    }
    return string(lines.item(scrolltop+cursor, string("")));
}

void ViWin_fileCompetion(ViWin* self, Vi* nvi) 
{
    char* line = nvi.commandString;

    char* p = line + strlen(line) -1;
    
    while(p >= line) {
        if(*p == ' ' || *p == '\t') {
            p++;
            break;
        }
        else {
            p--;
        }
    }
    
    var word = string(p);

    string dir_name = null;
    if(word[strlen(word)-1] == '/') {
        dir_name = string(word);
    }
    else {
        char* dname = dirname(clone word);

        if(strcmp(dname, "/") == 0) {
            dir_name = string("/");
        }
        else {
            dir_name = xsprintf("%s/", dirname(clone word));
        }
    }

    var words = new list<string>.initialize();

    if(dir_name.equals("./")) {
        char* cwd = getenv("PWD");
        
        if(cwd == null) {
            return;
        }
    
        DIR* dir = opendir(cwd);
    
        if(dir == null) {
            return;
        }
    
        while(true) {
            struct dirent* entry = readdir(dir);
    
            if(entry == null) {
                break;
            }
            
            string path = xsprintf("%s/%s", cwd, entry->d_name);
            
            stat stat_;
            stat(path, &stat_);
            
            if(S_ISDIR(stat_.st_mode)) {
                var item = borrow xsprintf("%s/", entry->d_name);
                words.push_back(item);
            }
            else {
                words.push_back(string(entry->d_name));
            }
        }
    
        closedir(dir);
    }
    else if(dir_name[0] == '/') {
        DIR* dir;
        if(strcmp(word, "/") != 0 && word[strlen(word)-1] == '/') {
            dir = opendir(word.substring(0, -2));
        }
        else {
            dir = opendir(dir_name);
        }
    
        if(dir == null) {
            return;
        }
    
        while(true) {
            struct dirent* entry = readdir(dir);
    
            if(entry == null) {
                break;
            }
            
            string path = xsprintf("%s%s", dir_name, entry->d_name);
            
            stat stat_;
            stat(path, &stat_);
            
            if(S_ISDIR(stat_.st_mode)) {
                var item = borrow xsprintf("%s%s/", dir_name, entry->d_name);
                words.push_back(item);
            }
            else {
                words.push_back(xsprintf("%s%s", dir_name, string(entry->d_name)));
            }
        }
    
        closedir(dir);
    }
    else {
        DIR* dir;
        if(word[strlen(word)-1] == '/') {
            dir = opendir(word.substring(0, -2));
        }
        else {
            dir = opendir(dir_name);
        }
    
        if(dir == null) {
            return;
        }
    
        while(true) {
            struct dirent* entry = readdir(dir);
    
            if(entry == null) {
                break;
            }
            
            string path = xsprintf("%s%s", dir_name, entry->d_name);
            
            stat stat_;
            stat(path, &stat_);
            
            if(S_ISDIR(stat_.st_mode)) {
                var item = borrow xsprintf("%s%s/", dir_name, entry->d_name);
                words.push_back(item);
            }
            else {
                words.push_back(xsprintf("%s%s", dir_name, entry->d_name));
            }
        }
    
        closedir(dir);
    }
    
    var words2 = new vector<string>.initialize();
    
    foreach(it, words) {
        if(strcmp(word, "") == 0 || strstr(it, word) == it) {
            words2.push_back(clone it);
        }
    }
    var words3 = words2.to_list().sort(lambda(char* left, char* right):int { return strcmp(left, right);} );
    
    var file_name = self.selector(words3).substring(strlen(word), -1);
    
    strncat(nvi.commandString, file_name, 128);
}

void ViWin_commandModeInput(ViWin* self, Vi* nvi) 
{
    var key = self.getKey(false);

    char a[128];
    snprintf(a, 128, "%c", key);

    switch(key) {
        case '\n':
            nvi.exitFromComandMode();
            break;

        case 3:
        case 27:
            nvi.mode = kEditMode;
            break;
            
        case '\t':
            self.fileCompetion(nvi);
            break;

        case 8:
        case 127:
        case KEY_BACKSPACE: {
            int len = strlen(nvi.commandString);
            if(len > 0) {
                nvi.commandString[len-1] = '\0';
            }
            }
            break;

        default: {
            strncat(nvi.commandString, a, 128);
            }
            break;
    }
}

void ViWin_view(ViWin* self, Vi* nvi) version 6
{
    if(nvi.mode == kCommandMode && self == nvi.activeWin) {
        self.commandModeView(nvi);
    }
    else {
        inherit(self, nvi);
    }
}

void ViWin_input(ViWin* self, Vi* nvi) version 6
{
    if(nvi.mode == kCommandMode) {
        self.commandModeInput(nvi);
    }
    else {
        inherit(self, nvi);
    }
}

void ViWin_subAllTextsFromCommandMode(ViWin* self, Vi* nvi) 
{
    /// parse command ///
    bool ignore_case = false;
    bool multiline = false;
    bool global = false;
    bool extended = false;
    bool dotall = false;
    bool anchored = false;
    bool dollar_endonly = false;
    bool ungreedy = false;

    regex_struct*% reg = regex("%s\/\(.+\)\/\(.*\)\/*?", ignore_case, multiline, global, extended, dotall, anchored, dollar_endonly, ungreedy);

    var command = string(nvi.commandString).scan(reg);

    var str = command.item(1, null);
    var replace = command.item(2, null);
    
    if(str != null && replace != null) {
        self.pushUndo();
        int it2 = 0;
        foreach(it, self.texts) {
            bool ignore_case = false;
            bool multiline = false;
            bool global = true;
            bool extended = false;
            bool dotall = false;
            bool anchored = false;
            bool dollar_endonly = false;
            bool ungreedy = false;

            regex_struct*% reg = regex(str, ignore_case, multiline, global, extended, dotall, anchored, dollar_endonly, ungreedy);

            var new_line = borrow it.to_string().sub(reg, replace, null).to_wstring();
            
            self.texts.replace(it2, new_line);

            it2++;
        }
    }
}

void Vi_enterComandMode(Vi* self) 
{
    self.mode = kCommandMode;
    strncpy(self.commandString, "", 128);
}

void Vi_exitFromComandMode(Vi* self) 
{
    if(string(self.commandString).index("sp", -1) == 0) {
        bool ignore_case = false;
        bool multiline = false;
        bool global = false;
        bool extended = false;
        bool dotall = false;
        bool anchored = false;
        bool dollar_endonly = false;
        bool ungreedy = false;

        regex_struct*% reg = regex("sp \(.+\)", ignore_case, multiline, global, extended, dotall, anchored, dollar_endonly, ungreedy);

        var file_name = clone string(self.commandString).scan(reg).item(1, null);

        if(file_name != null) {
            self.openNewFile(file_name);
        }
    }
    else {
        if(string(self.commandString).index("%", -1) != -1) {
            self.activeWin.subAllTextsFromCommandMode(self);
            self.mode = kEditMode;
        }
        if(string(self.commandString).index("w", -1) != -1) {
            self.activeWin.writeFile();
        }
        if(string(self.commandString).index("q", -1) != -1) {
            bool writed = self.activeWin.writed;

            if(!writed || string(self.commandString).index("!", -1) != -1) {
                if(self.wins.length() == 1) {
                    self.appEnd = true;
                }
                else {
                    self.closeActiveWin();
                }
            }
        }
        if(string(self.commandString).index("shell", -1) != -1) {
            endwin();
            
            (void)system("bash");

            self.init_curses();
        }
    }

    self.mode = kEditMode;
}

Vi*% Vi_initialize(Vi*% self) version 12
{
    var result = inherit(self);

    strncpy(result.commandString, "", 128);

    result.events.replace(':', lambda(Vi* self, int key) {
        self.enterComandMode();
    });

    return result;
}

