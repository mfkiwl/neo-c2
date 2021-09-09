#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>

bool ViWin::saveYankToFile(ViWin* self, Vi* nvi)
{
    char* home = getenv("HOME");
    if(home == null) {
        return false;
    }

    string path = xsprintf("%s/.vin/yank.txt", home);
    FILE* f = fopen(path, "w");

    if(f == null) {
        return false;
    }

    foreach(it, nvi.yank) {
        fputs(it.to_string(), f);
        fputs("\n", f);
    }

    fclose(f);

    return true;
}

bool ViWin::loadYankFromFile(ViWin* self, Vi* nvi)
{
    char* home = getenv("HOME");
    if(home == null) {
        return false;
    }

    string path = xsprintf("%s/.vin/yank.txt", home);
    FILE* f = fopen(path, "r");

    if(f == null) {
        return false;
    }

    char line[4096];

    nvi.yank.reset();

    while(fgets(line, 4096, f) != NULL)
    {
        char c = line[strlen(line)-1];
        line[strlen(line)-1] = '\0';
        nvi.yank.push_back(wstring(line))
    }

    fclose(f);

    return true;
}

void ViWin::pasteAfterCursor(ViWin* self, Vi* nvi) 
{
    self.loadYankFromFile(nvi);
    if(nvi.yankKind == kYankKindLine) {
        self.pushUndo();

        int it2 = 0;
        foreach(it, nvi.yank) {
            self.texts.insert(self.scroll+self.cursorY+it2+1, clone it);
            it2++;
        }
    }
    else {
        self.pushUndo();

        auto line = self.texts.item(self.scroll+self.cursorY, null);
        
        if(nvi.yank.length() == 1) {
            auto yank_first_line = nvi.yank.item(0, null);

            auto new_line = borrow xsprintf("%ls%ls%ls"
                            , line.substring(0, self.cursorX+1)
                            , yank_first_line
                            , line.substring(self.cursorX+1, -1)).to_wstring();
    
            self.texts.replace(self.scroll+self.cursorY, new_line);
        }
        else if(nvi.yank.length() == 2) {
            auto yank_first_line = nvi.yank.item(0, null);
    
            auto new_line = borrow xsprintf("%ls%ls"
                                , line.substring(0, self.cursorX+1)
                                , yank_first_line).to_wstring();

            auto after_line = line.substring(self.cursorX+1, -1);
    
            self.texts.replace(self.scroll+self.cursorY, new_line);
            
            auto yank_last_line = nvi.yank.item(-1, null);
            
            auto new_line2 = borrow xsprintf("%ls%ls"
                                , yank_last_line
                                , after_line).to_wstring();
            self.texts.insert(self.scroll+self.cursorY+1, new_line2);
        }
        else if(nvi.yank.length() > 2) {
            auto yank_first_line = nvi.yank.item(0, null);
    
            auto new_line = borrow xsprintf("%ls%ls"
                                    , line.substring(0, self.cursorX+1)
                                    , yank_first_line).to_wstring();
            auto after_line = line.substring(self.cursorX+1, -1);
    
            self.texts.replace(self.scroll+self.cursorY, new_line);

            int it2 = 0;
            foreach(it, nvi.yank.sublist(1,-2)) {
                self.texts.insert(self.scroll+self.cursorY+it2+1, clone it);
                it2++;
            }
            
            auto yank_last_line = nvi.yank.item(-1, null);
            
            auto new_line2 = borrow xsprintf("%ls%ls"
                                        , yank_last_line
                                        , after_line).to_wstring();
            self.texts.insert(self.scroll+self.cursorY+nvi.yank.length()-1, new_line2);
        }
    }
}

void ViWin::pasteBeforeCursor(ViWin* self, Vi* nvi) 
{
    self.loadYankFromFile(nvi);
    if(nvi.yankKind == kYankKindLine) {
        self.pushUndo();
        int it2 = 0;
        foreach(it, nvi.yank) {
            self.texts.insert(self.scroll+self.cursorY+it2, clone it);
            it2++;
        }
    }
    else {
        self.pushUndo();

        auto line = self.texts.item(self.scroll+self.cursorY, null);
        
        if(nvi.yank.length() == 1) {
            auto yank_first_line = nvi.yank.item(0, null);

            auto new_line = borrow xsprintf("%ls%ls%ls"
                                , line.substring(0, self.cursorX)
                                , yank_first_line
                                , line.substring(self.cursorX, -1)).to_wstring();
    
            self.texts.replace(self.scroll+self.cursorY, new_line);
        }
        else if(nvi.yank.length() == 2) {
            auto yank_first_line = nvi.yank.item(0, null);
    
            auto new_line = borrow xsprintf("%ls%ls"
                                , line.substring(0, self.cursorX) 
                                , yank_first_line).to_wstring();

            auto after_line = line.substring(self.cursorX, -1);
    
            self.texts.replace(self.scroll+self.cursorY, new_line);
            
            auto yank_last_line = nvi.yank.item(-1, null);
            
            auto new_line2 = borrow xsprintf("%ls%ls"
                                , yank_last_line
                                , after_line).to_wstring();
            self.texts.insert(self.scroll+self.cursorY+1, new_line2);
        }
        else if(nvi.yank.length() > 2) {
            auto yank_first_line = nvi.yank.item(0, null);
    
            auto new_line = borrow xsprintf("%ls%ls"
                                , line.substring(0, self.cursorX) 
                                , yank_first_line).to_wstring();
            auto after_line = line.substring(self.cursorX, -1);
    
            self.texts.replace(self.scroll+self.cursorY, new_line);
            int it2 = 0;
            foreach(it, nvi.yank.sublist(1,-2)) {
                self.texts.insert(self.scroll+self.cursorY+it2+1, clone it);
                it2++;
            }
            
            auto yank_last_line = nvi.yank.item(-1, null);
            
            auto new_line2 = borrow xsprintf("%ls%ls"
                                        ,yank_last_line
                                        , after_line).to_wstring();
            self.texts.insert(self.scroll+self.cursorY+nvi.yank.length()-1, new_line2);
        }
    }
}

Vi*% Vi::initialize(Vi*% self) version 7
{
    auto result = inherit(self);

    result.yank = borrow new list<wstring>.initialize();

    result.yankKind = 0;

    result.events.replace('p', void lambda(Vi* self, int key) 
    {
        self.activeWin.pasteAfterCursor(self);
        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });

    result.events.replace('P', void lambda(Vi* self, int key) 
    {
        self.activeWin.pasteBeforeCursor(self);
        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });

    return result;
}

void Vi::finalize(Vi* self) version 3
{
    inherit(self);

    delete self.yank;
}
