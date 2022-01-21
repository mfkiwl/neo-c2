#include <neo-c2.h>

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
            p++;
        }
        else if(*p == '\\') {
            p+=2;
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
                    p++;
                }
                else if(*p == '\\') {
                    p+=2;
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

