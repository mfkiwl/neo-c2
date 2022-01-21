#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>

void ViWin::toggleBraceForward(ViWin* self, wchar_t head, wchar_t tail) 
{
    int cursor_y = self.scroll + self.cursorY;
    int cursor_x = -1;

    int nest = 0;

    auto line = self.texts.item(cursor_y, null);

    wchar_t* p = line + self.cursorX+1;
    
    bool squort = false;
    bool dquort = false;

    while(p < line + line.length()) { 
        if(!dquort && *p == '\'') {
            p++;
            squort = !squort;
        }
        else if(!squort && *p == '"') {
            p++;
            dquort = !dquort;
        }
        else if(squort || dquort) {
            if(*p == '\\') {
                p+=2;
            }
            else {
                p++;
            }
        }
        else if(*p == tail) {
            if(nest == 0) {
                self.saveReturnPoint();

                cursor_x = (p - line);
                self.cursorX = cursor_x;
                return;
            }

            p++;
            nest--;
        }
        else if(*p == head) {
            p++;

            nest++;
        }
        else {
            p++;
        }
    }

    if(cursor_x == -1) {
        cursor_y++;

        int it2 = 0;
        foreach(it, self.texts.sublist(self.scroll+self.cursorY+1, -1)) {
            wchar_t* p = it;

            while(p < it + it.length()) {
                if(!dquort && *p == '\'') {
                    p++;
                    squort = !squort;
                }
                else if(!squort && *p == '"') {
                    p++;
                    dquort = !dquort;
                }
                else if(squort || dquort) {
                    if(*p == '\\') {
                        p+=2;
                    }
                    else {
                        p++;
                    }
                }
                else if(*p == tail) {
                    if(nest == 0) {
                        self.saveReturnPoint();

                        self.scroll = it2 + self.scroll + self.cursorY + 1;
                        self.cursorY = 0;
                        self.cursorX = p - it;
                        self.modifyOverCursorXValue();
                        self.centeringCursor();
                        return;
                    }

                    p++;
                    nest--;
                }
                else if(*p == head) {
                    p++;

                    nest++;
                }
                else {
                    p++;
                }
            }

            cursor_y++;
            it2++;
        }
    }
}

void ViWin::toggleBraceBack(ViWin* self, wchar_t head, wchar_t tail) 
{
    int nest = 0;

    auto line = self.texts.item(self.scroll + self.cursorY, null);

    wchar_t* p = line + self.cursorX-1;
    
    bool dquort = false;
    bool squort = false;

    while(p >= line) {
        if(!dquort && *p == '\'') {
            p--;
            if(*(p-1) != '\\' && *p == '\'') {
                squort = !squort;
            }
        }
        else if(!squort && *p == '"') {
            p--;
            if(*(p-1) != '\\' && *p == '"') {
                dquort = !dquort;
            }
        }
        else if(squort || dquort) {
            p--;
        }
        else if(*p == head) {
            if(nest == 0) {
                self.saveReturnPoint();
                
                self.cursorX = p -line;
                self.modifyOverCursorXValue();
                return;
            }

            p--;
            nest--;
        }
        else if(*p == tail) {
            p--;

            nest++;
        }
        else {
            p--;
        }
    }

    for(int i=self.scroll+self.cursorY-1; i>=0; i--) {
        wstring it = self.texts.item(i, null);
        
        wchar_t* p = it + it.length();
        
        while(p >= it) {
            if(!dquort && *p == '\'') {
                p--;
                if(*(p-1) != '\\' && *p == '\'') {
                    squort = !squort;
                }
            }
            else if(!squort && *p == '"') {
                p--;
                if(*(p-1) != '\\' && *p == '"') {
                    dquort = !dquort;
                }
            }
            else if(squort || dquort) {
                p--;
            }
            else if(*p == head) {
                if(nest == 0) {
                    self.saveReturnPoint();

                    self.scroll = i;
                    self.cursorY = 0;
                    self.modifyUnderCursorYValue();
                    self.cursorX = p - it;
                    self.modifyOverCursorXValue();
                    self.centeringCursor();
                    return ;
                }

                p--;
                nest--;
            }
            else if(*p == tail) {
                p--;

                nest++;
            }
            else {
                p--;
            }
        }
    }
}

void ViWin::toggleCommentForward(ViWin* self)
{
    int head = self.scroll + self.cursorY;
    int tail = -1;
    
    int nest = 0;
    
    int it2 = 0;
    foreach(it, self.texts.sublist(head, tail)) {
        int index = it.to_string().index("*/", -1);
        
        int index2 = it.to_string().index("/*", -1);
        
        if(index2 != -1) {
            nest++;
        }
        
        if(index != -1) {
            nest--;
            
            if(nest <= 0) {
                self.saveReturnPoint();
                self.cursorX = index;
                self.scroll = 0;
                self.cursorY = it2 + head;
                self.modifyOverCursorYValue();
                break;
            }
        }

        it2++;
    }
}

void ViWin::toggleCommentBackward(ViWin* self)
{
    int head = 0;
    int tail = self.scroll + self.cursorY + 1;
    
    int nest = 0;
    
    int it2 = 0;
    foreach(it, self.texts.sublist(head, tail).reverse()) {
        int index = it.to_string().index("/*", -1);
        
        int index2 = it.to_string().index("*/", -1);
        
        if(index2 != -1) {
            nest++;
        }
        
        if(index != -1) {
            nest--;
            
            if(nest == 0) {
                self.saveReturnPoint();
                self.cursorX = index;
                self.scroll = 0;
                self.cursorY = tail - it2 -1;
                self.modifyOverCursorYValue();
                self.centeringCursor();
                break;
            }
        }

        it2++;
    }
}

void ViWin::gotoBraceEnd(ViWin* self, Vi* nvi) version 11
{
    auto line = self.texts.item(self.scroll+self.cursorY, null);

    auto c = line[self.cursorX];
    wchar_t c1 = 0;
    wchar_t c2 = 0;
    if(self.cursorX - 1 >= 0) {
        c1 = line[self.cursorX-1];
    }
    if(self.cursorX + 1 < line.length()) {
        c2 = line[self.cursorX+1];
    }
    
    switch(c) {
        case '*':
            if(c1 == '/') {
                self.toggleCommentForward();
            }
            if(c2 == '/') {
                self.toggleCommentBackward();
            }
            break;
            
        case '/':
            if(c1 == '*') {
                self.toggleCommentBackward();
            }
            if(c2 == '*') {
                self.toggleCommentForward();
            }
            break;
            
        case '(':
            self.toggleBraceForward('(', ')');
            break;

        case '{':
            self.toggleBraceForward('{', '}');
            break;

        case '[':
            self.toggleBraceForward('[', ']');
            break;

        case '<':
            self.toggleBraceForward('<', '>');
            break;

        case ')':
            self.toggleBraceBack('(', ')');
            break;

        case '}':
            self.toggleBraceBack('{', '}');
            break;

        case ']':
            self.toggleBraceBack('[', ']');

        case '>':
            self.toggleBraceBack('<', '>');
            break;
    }
}

void ViWin::gotoFunctionTop(ViWin* self, Vi* nvi) 
{
    bool ignore_case = false;
    bool multiline = false;
    bool global = false;
    bool extended = false;
    bool dotall = false;
    bool anchored = false;
    bool dollar_endonly = false;
    bool ungreedy = false;

    regex_struct* reg = regex("^{", ignore_case, multiline, global, extended, dotall, anchored, dollar_endonly, ungreedy);

    int it2 = 0;
    foreach(it, self.texts.sublist(0, self.scroll+self.cursorY).reverse()) {
        if(it.to_string().match(reg))
        {
            self.saveReturnPoint();

            self.cursorY = self.cursorY - it2 -1;
            self.modifyUnderCursorYValue();
            self.modifyOverCursorYValue();
            break;
        }

        it2++;
    }
}

void ViWin::gotoFunctionBottom(ViWin* self, Vi* nvi) 
{
    int cursor_y = self.scroll+self.cursorY + 1;

    bool ignore_case = false;
    bool multiline = false;
    bool global = false;
    bool extended = false;
    bool dotall = false;
    bool anchored = false;
    bool dollar_endonly = false;
    bool ungreedy = false;

    regex_struct* reg = regex("^}", ignore_case, multiline, global, extended, dotall, anchored, dollar_endonly, ungreedy);

    int it2 = 0;
    foreach(it, self.texts.sublist(self.scroll+self.cursorY+1, -1)) {
        if(it.to_string().match(reg)) 
        {
            self.saveReturnPoint();

            self.cursorY += it2 + 1;
            self.cursorX = 0;
            self.modifyOverCursorYValue();
            break;
        }

        cursor_y++;
        it2++;
    }
}

Vi* Vi::initialize(Vi* self) version 11
{
    auto result = inherit(self);

    result.events.replace('%', void lambda(Vi* self, int key) {
        self.activeWin.gotoBraceEnd(self);
        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });

    result.events.replace('[', void lambda(Vi* self, int key) {
        auto key2 = self.activeWin.getKey(false);

        switch(key2) {
            case '[':
                self.activeWin.gotoFunctionTop(self);
                self.activeWin.centeringCursor();
                self.activeWin.saveInputedKeyOnTheMovingCursor();
                break;
        }
    });

    result.events.replace(']', void lambda(Vi* self, int key) {
        auto key2 = self.activeWin.getKey(false);

        switch(key2) {
            case ']':
                self.activeWin.gotoFunctionBottom(self);
                self.activeWin.centeringCursor();
                self.activeWin.saveInputedKeyOnTheMovingCursor();
                break;
        }
    });

    return result;
}
