#include "common.h"
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi) version 4
{
    var result = inherit(self, y, x, width, height, vi);

    strncpy(result.fileName, "a.txt", PATH_MAX);

    return result;
}

void ViWin_statusBarView(ViWin* self, Vi* nvi) version 2
{
    int maxy = getmaxy(self.win);
    int maxx = getmaxx(self.win);

    wattron(self.win, A_REVERSE);
    mvwprintw(self.win, self.height-1, 0, "x %d y %d scroll %d file %s writed %d", self.cursorX, self.cursorY, self.scroll, self.fileName, (self.writed ? 1:0));
    wattroff(self.win, A_REVERSE);

    wrefresh(self.win);
}

void ViWin_saveCursorPosition(ViWin* self, char* file_name) 
{
    char* home = getenv("HOME");
    
    if(home == null) {
        return;
    }
    
    char file_name2[PATH_MAX];
    
    snprintf(file_name2, PATH_MAX, "%s/.vico", home);
    
    (void)mkdir(file_name2, 0755);
    
    var bname = xbasename(file_name);  

    snprintf(file_name2, PATH_MAX, "%s/.wi/%s.pos", home, bname);
    
    FILE* f = fopen(file_name2, "w");

    if(f == null) {
        return;
    }
    
    fprintf(f, "%d %d\n", self.scroll, self.cursorY);
    
    fclose(f);
}

void ViWin_readCursorPosition(ViWin* self, char* file_name) 
{
    char* home = getenv("HOME");
    
    if(home == null) {
        self.scroll = 0;
        self.cursorY = 0;
        return;
    }
    
    char file_name2[PATH_MAX];
    
    var bname = xbasename(file_name); 
    snprintf(file_name2, PATH_MAX, "%s/.wi/%s.pos", home, bname);
    
    FILE* f = fopen(file_name2, "r");

    if(f == null) {
        self.cursorY = 0;
        return;
    }
    
    char line[4096];

    int scroll = 0;
    int cursor_y = 0;
    fscanf(f, "%d %d", &scroll, &cursor_y);
    
    fclose(f);
    
    self.scroll = scroll;
    self.cursorY = cursor_y;
    
    if(self.scroll >= self.texts.length()) {
        self.scroll = self.texts.length() - 1;
        self.cursorY = 0;
    }
    
    self.modifyUnderCursorYValue();
    self.modifyOverCursorYValue();
}

void ViWin_openFile(ViWin* self, char* file_name, int line_num) version 2
{
    FILE* f = fopen(file_name, "r");
    
    if(f == null) {
        char cmd[PATH_MAX+128];
        
        snprintf(cmd, PATH_MAX+128, "echo \"\" > %s", file_name);

        self.texts.push_back(wstring(""))
        
        int rc = system(cmd);
        
        if(rc != 0) {
            endwin();
            fprintf(stderr, "can't open file %s\n", file_name);
            exit(2);
        }

        strncpy(self.fileName, file_name, PATH_MAX);
        
        self.cursorY = 0;
        self.cursorX = 0;
        self.scroll = 0;
    }
    else {
        char line[4096];

        while(fgets(line, 4096, f) != NULL)
        {
            line[strlen(line)-1] = '\0';
            self.texts.push_back(wstring(line))
        }

        fclose(f);

        if(self.texts.length() == 0) {
            self.texts.push_back(wstring(""))
        }

        strncpy(self.fileName, file_name, PATH_MAX);

        if(line_num == -1) {
            self.readCursorPosition(file_name);
        }
        else {
            self.cursorY = line_num;
            
            self.modifyUnderCursorYValue();
            self.modifyOverCursorYValue();
            self.centeringCursor();
        }
    }
}

void ViWin_writeFile(ViWin* self) 
{
    /// back up /// 
    char* home = getenv("HOME");
    
    if(home == null) {
        return;
    }
    
    char path[PATH_MAX];
    
    snprintf(path, PATH_MAX, "%s/.vico", home);
    
    (void)mkdir(path, 0755);
    
    snprintf(path, PATH_MAX, "%s/.wi/backup", home);
    
    (void)mkdir(path, 0755);
    
    char cmd[BUFSIZ];
    
    snprintf(cmd, BUFSIZ, "cp %s %s/.wi/backup", self.fileName, home);
    
    (void)system(cmd);
    
    /// write ///
    FILE* f = fopen(self.fileName, "w");

    if(f != null) {
        foreach(it, self.texts) {
            fprintf(f, "%ls\n", it);
        }

        fclose(f);

        self.writed = false;
        self.saveCursorPosition(self.fileName);
        self.saveDotToFile(self.vi);
    }
}

void ViWin_writedFlagOn(ViWin* self) version 2
{
    self.writed = true;
}

bool ViWin_saveDotToFile(ViWin* self, Vi* nvi) version 1
{
    /// implementad after layer
}

void Vi_openNewFile(Vi* self, char* file_name) 
{
    int maxy = xgetmaxy();
    int maxx = xgetmaxx();

    int height = maxy / (self.wins.length() + 1);

    var win = borrow new ViWin.initialize(0,0, maxx-1, height, self);
    
    win.openFile(file_name, -1);

    self.activeWin = win;

    self.wins.push_back(win);

    self.repositionWindows();

    int it2 = 0;
    foreach(it, self.wins) {
        if(!it.equals(self.activeWin)) {
            self.toggleWin = it2;
        }
        it2++;
    }
}

void Vi_closeActiveWin(Vi* self) 
{
    int active_pos = self.wins.find(self.activeWin, -1);
    
    self.wins.delete(active_pos, active_pos+1);

    self.repositionWindows();

    self.activeWin = self.wins.item(0, null);
}

void Vi_exitFromApp(Vi* self) version 2
{
    foreach(it, self.wins) {
        it.writeFile();
    }
    self.appEnd = true;
}

void Vi_toggleWin(Vi* self) {
    if(self.toggleWin >= 0 && self.toggleWin < self.wins.length()) {
        int toggle_win = self.wins.find(self.activeWin, -1);
        self.activeWin = self.wins.item(self.toggleWin, null);
        self.toggleWin = toggle_win;
    }
}
void Vi_nextWin(Vi* self) {
    int next_win = self.wins.find(self.activeWin, -1) + 1;
    if(next_win >= 0 && next_win < self.wins.length()) 
    {
        int toggle_win = self.wins.find(self.activeWin, -1);
        self.activeWin = self.wins.item(next_win, null);
        self.toggleWin = toggle_win;
    }
}

void Vi_prevWin(Vi* self) {
    int prev_win = self.wins.find(self.activeWin, -1) - 1;
    if(self.toggleWin >= 0 && self.toggleWin < self.wins.length()) {
        int toggle_win = self.wins.find(self.activeWin, -1);
        self.activeWin = self.wins.item(prev_win, null);
        self.toggleWin = toggle_win;
    }
}

Vi*% Vi_initialize(Vi*% self) version 6
{
    var result = inherit(self);

    result.events.replace('W'-'A'+1, lambda(Vi* self, int key) 
    {
        var key2 = self.activeWin.getKey(false);

        switch(key2) {
            case 'W'-'A'+1:
            case 'w':
                self.toggleWin();
                break;
            case 'j':
                self.nextWin();
                break;
            case 'k':
                self.prevWin();
                break;
        }
    });

    return result;
}

void Vi_repositionWindows(Vi* self) version 2
{
    int maxy = xgetmaxy();
    int maxx = xgetmaxx();

    int height = maxy / self.wins.length();

    /// determine the position ///
    int it2 = 0;
    foreach(it, self.wins) {
        it.height = height;
        it.y = height * it2;

        delwin(it.win);
        var win = newwin(it.height, it.width, it.y, it.x);
        keypad(win, true);
        it.win = win;

        it.centeringCursor();
        it.cursorX = 0;

        it2++;
    }
}

void Vi_saveLastOpenFile(Vi* self, char* file_name) 
{
    char* home = getenv("HOME");
    
    if(home == null) {
        return;
    }
    
    char file_name2[PATH_MAX];
    
    snprintf(file_name2, PATH_MAX, "%s/.vico", home);
    
    (void)mkdir(file_name2, 0755);
    
    snprintf(file_name2, PATH_MAX, "%s/.vico/last_open_file", home, file_name);
    
    FILE* f = fopen(file_name2, "w");

    if(f == null) {
        return;
    }
    
    fprintf(f, "%s\n", file_name);
    
    fclose(f);
}

string Vi_readLastOpenFile(Vi* self) 
{
    char* home = getenv("HOME");
    
    if(home == null) {
        return null;
    }
    
    char file_name2[PATH_MAX];
    
    snprintf(file_name2, PATH_MAX, "%s/.wi/last_open_file", home);
    
    FILE* f = fopen(file_name2, "r");

    if(f == null) {
        return null;
    }

    char file_name[PATH_MAX];

    if(fgets(file_name, PATH_MAX, f) == NULL) {
        fclose(f);

        return string("");
    }
    
    file_name[strlen(file_name)-1] = '\0';
    
    fclose(f);

    return string(file_name);
}

void Vi_openFile(Vi* self, char* file_name, int line_num) version 2
{
    if(file_name == null) {
        var file_name = self.readLastOpenFile();
        
        if(access(file_name, R_OK) == 0) {
            int active_pos = self.wins.find(self.activeWin, -1);
            self.wins.delete(active_pos, active_pos+1);
    
            var maxx = xgetmaxx();
            var maxy = xgetmaxy();
            
            var win = borrow new ViWin.initialize(0,0, maxx-1, maxy, self);
    
            self.activeWin = win;
            self.wins.push_back(win);
            
            self.activeWin.openFile(file_name, -1);
            
            self.repositionWindows();
        }
    }
    else {
        if(access(file_name, R_OK) == 0) {
            int active_pos = self.wins.find(self.activeWin, -1);
            self.wins.delete(active_pos, active_pos+1);
    
            var maxx = xgetmaxx();
            var maxy = xgetmaxy();
            
            var win = borrow new ViWin.initialize(0,0, maxx-1, maxy, self);
    
            self.activeWin = win;
            self.wins.push_back(win);
            
            self.activeWin.openFile(file_name, line_num);
            self.saveLastOpenFile(file_name);
            
            self.repositionWindows();
        }
        else {
            char cmd[PATH_MAX+128];
            
            snprintf(cmd, PATH_MAX+128, "echo \"\" > %s", file_name);

            int rc = system(cmd);
            
            if(rc != 0) {
                endwin();
                fprintf(stderr, "can't open file %s\n", file_name);
                exit(2);
            }

            strncpy(self.activeWin.fileName, file_name, PATH_MAX);
            
            self.activeWin.cursorY = 0;
            self.activeWin.cursorX = 0;
            self.activeWin.scroll = 0;
        }
    }
}
