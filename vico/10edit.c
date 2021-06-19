#include "common.h"

ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi) version 6
{
    var result = inherit(self, y, x, width, height, vi);
    
    result.mRepeatFowardNextCharacterKind = kRFNCNone;
    result.mRepeatFowardNextCharacter = 0;

    return result;
}

void ViWin_modifyCursorOnDeleting(ViWin* self) 
{
    self.modifyOverCursorYValue();
    self.modifyOverCursorXValue2();
}

void ViWin_deleteOneLine(ViWin* self, Vi* nvi) version 2
{
    if(self.digitInput > 0) {
        self.pushUndo();
        
        nvi.yank.reset();
        nvi.yankKind = kYankKindLine;
        
        for(int i=0; i<self.digitInput+1; i++) {
            var line = self.texts.item(self.scroll+self.cursorY, null);
            
            if(line != null) {
                nvi.yank.push_back(clone line);
                
                self.texts.delete(self.scroll+self.cursorY, self.scroll+self.cursorY+1);
        
                self.modifyCursorOnDeleting();
            }
        }
        
        self.saveYankToFile(nvi);
        self.digitInput = 0;
    }
    else {
        var line = self.texts.item(self.scroll+self.cursorY, null);
        if(line != null) {
            self.pushUndo();
            nvi.yank.reset();
            nvi.yank.push_back(clone line);
            nvi.yankKind = kYankKindLine;
            self.saveYankToFile(nvi);
            self.texts.delete(self.scroll+self.cursorY, self.scroll+self.cursorY+1);
    
            self.modifyCursorOnDeleting();
        }
    }
}

void ViWin_deleteOneLine2(ViWin* self, Vi* nvi) 
{
    if(self.digitInput > 0) {
        self.pushUndo();
        
        nvi.yank.reset();
        nvi.yankKind = kYankKindLine;
        
        for(int i=0; i<self.digitInput+1; i++) {
            var line = self.texts.item(self.scroll+self.cursorY, null);
            
            if(line != null) {
                nvi.yank.push_back(clone line);
                
                self.texts.delete(self.scroll+self.cursorY, self.scroll+self.cursorY+1);
        
                self.modifyCursorOnDeleting();
            }
        }
        
        self.digitInput = 0;
        self.saveYankToFile(nvi);
    }
    else {
        var line = self.texts.item(self.scroll+self.cursorY, null);
        if(line != null) {
            self.pushUndo();
            self.texts.delete(self.scroll+self.cursorY, self.scroll+self.cursorY+1);
            self.texts.insert(self.scroll+self.cursorY, wstring(""));
    
            self.modifyCursorOnDeleting();
        }
    }
}

void ViWin_deleteWord(ViWin* self, Vi* nvi) 
{
    self.pushUndo();
    
    if(self.digitInput > 0) {
        var line = self.texts.item(self.scroll+self.cursorY, wstring(""));
    
        if(wcslen(line) == 0) {
            self.deleteOneLine(nvi);
        }
        else {
            int count = self.digitInput + 1;
            
            int x = self.cursorX;
    
            for(int i=0; i<count; i++) {
                wchar_t* p = line + x;
        
                if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || *p == '_')
                {
                    while((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || *p == '_')
                    {
                        p++;
                        x++;
        
                        if(x >= line.length())
                        {
                            break;
                        }
                    }
                }
                else if((*p >= '!' && *p <= '/') || (*p >= ':' && *p <= '@') || (*p >= '{' && *p <= '~' ))
                {
                    while((*p >= '!' && *p <= '/') || (*p >= ':' && *p <= '@') || (*p >= '{' && *p <= '~' ))
                    {
                        p++;
                        x++;
        
                        if(x >= line.length())
                        {
                            break;
                        }
                    }
                }
                else if(xiswalpha(*p)) {
                    while(xiswalpha(*p)) {
                        p++;
                        x++;
        
                        if(x >= line.length())
                        {
                            break;
                        }
                    }
                }
                else if(xiswblank(*p)) {
                    while(xiswblank(*p)) {
                        p++;
                        x++;
        
                        if(x >= line.length())
                        {
                            break;
                        }
                    }
                }
                else if(xiswdigit(*p)) {
                    while(xiswdigit(*p)) {
                        p++;
                        x++;
        
                        if(x >= line.length())
                        {
                            break;
                        }
                    }
                }
            }
    
            nvi.yank.reset();
            nvi.yank.push_back(line.substring(self.cursorX, x));
            nvi.yankKind = kYankKindNoLine;
            self.saveYankToFile(nvi);
            line.delete(self.cursorX, x);
    
            self.modifyCursorOnDeleting();
        }
        
        self.digitInput = 0;
    }
    else {
        var line = self.texts.item(self.scroll+self.cursorY, wstring(""));
    
        if(wcslen(line) == 0) {
            self.deleteOneLine(nvi);
        }
        else {
            int x = self.cursorX;
    
            wchar_t* p = line + x;
    
            if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || *p == '_')
            {
                while((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || *p == '_')
                {
                    p++;
                    x++;
    
                    if(x >= line.length())
                    {
                        break;
                    }
                }
            }
            else if((*p >= '!' && *p <= '/') || (*p >= ':' && *p <= '@') || (*p >= '{' && *p <= '~' ))
            {
                while((*p >= '!' && *p <= '/') || (*p >= ':' && *p <= '@') || (*p >= '{' && *p <= '~' ))
                {
                    p++;
                    x++;
    
                    if(x >= line.length())
                    {
                        break;
                    }
                }
            }
            else if(xiswalpha(*p)) {
                while(xiswalpha(*p)) {
                    p++;
                    x++;
    
                    if(x >= line.length())
                    {
                        break;
                    }
                }
            }
            else if(xiswblank(*p)) {
                while(xiswblank(*p)) {
                    p++;
                    x++;
    
                    if(x >= line.length())
                    {
                        break;
                    }
                }
            }
            else if(xiswdigit(*p)) {
                while(xiswdigit(*p)) {
                    p++;
                    x++;
    
                    if(x >= line.length())
                    {
                        break;
                    }
                }
            }
    
            nvi.yank.reset();
            nvi.yank.push_back(line.substring(self.cursorX, x));
            nvi.yankKind = kYankKindNoLine;
            self.saveYankToFile(nvi);
            line.delete(self.cursorX, x);
    
            self.modifyCursorOnDeleting();
        }
    }
}

void ViWin_deleteForNextCharacter(ViWin* self) 
{
    self.pushUndo();
    
    if(self.digitInput > 0) {
        var key = self.getKey(false);
    
        var line = self.texts.item(self.scroll+self.cursorY, wstring(""));
    
        if(wcslen(line) > 0) {
            int x = self.cursorX;
            
            int count = self.digitInput + 1;
            
            wchar_t* p;
    
            for(int i=0; i<count; i++) {
                p = line + x;
        
                while(*p != key) {
                    p++;
                    x++;
        
                    if(x >= line.length())
                    {
                        break;
                    }
                }
                
                if(i != count -1) {
                    x++;
                }
            }
            
            if(*p == key) {
                line.delete(self.cursorX, x+1);
            }
        }
        
        self.digitInput = 0;
    }
    else {
        var key = self.getKey(false);
    
        var line = self.texts.item(self.scroll+self.cursorY, wstring(""));
    
        if(wcslen(line) > 0) {
            int x = self.cursorX;
    
            wchar_t* p = line + x;
    
            while(*p != key) {
                p++;
                x++;
    
                if(x >= line.length())
                {
                    break;
                }
            }
            
            if(*p == key) {
                line.delete(self.cursorX, x+1);
            }
        }
    }
}

void ViWin_deleteForNextCharacter2(ViWin* self) 
{
    self.pushUndo();
    
    if(self.digitInput > 0) {
        var key = self.getKey(false);
    
        var line = self.texts.item(self.scroll+self.cursorY, wstring(""));
    
        if(wcslen(line) > 0) {
            int x = self.cursorX;
            
            int count = self.digitInput + 1;
            
            wchar_t* p;
    
            for(int i=0; i<count; i++) {
                p = line + x;
        
                while(*p != key) {
                    p++;
                    x++;
        
                    if(x >= line.length())
                    {
                        break;
                    }
                }
                
                if(i != count -1) {
                    x++;
                }
            }
            
            if(*p == key) {
                line.delete(self.cursorX, x);
            }
        }
        
        self.digitInput = 0;
    }
    else {
        var key = self.getKey(false);
    
        var line = self.texts.item(self.scroll+self.cursorY, wstring(""));
    
        if(wcslen(line) > 0) {
            int x = self.cursorX;
    
            wchar_t* p = line + x;
    
            while(*p != key) {
                p++;
                x++;
    
                if(x >= line.length())
                {
                    break;
                }
            }
            
            if(*p == key) {
                line.delete(self.cursorX, x);
            }
        }
    }
}

void ViWin_deleteCursorCharactor(ViWin* self) 
{
    self.pushUndo();
    
    if(self.digitInput > 0) {
        int num = self.digitInput + 1;
        
        var line = self.texts.item(self.scroll+self.cursorY, null);
        
        for(int i= 0; i<num; i++) {
            line.delete(self.cursorX, self.cursorX+1);
        }
    
        self.modifyOverCursorXValue();
        
        self.digitInput = 0;
    }
    else {
        var line = self.texts.item(self.scroll+self.cursorY, null);
        line.delete(self.cursorX, self.cursorX+1);
    
        self.modifyOverCursorXValue();
    }
}

void ViWin_deleteBack(ViWin* self) 
{
    self.pushUndo();
    
    if(self.digitInput > 0) {
        int num = self.digitInput + 1;
        
        var line = self.texts.item(self.scroll+self.cursorY, null);
        
        for(int i= 0; i<num; i++) {
            if(self.cursorX > 0) {
                self.cursorX--;
                line.delete(self.cursorX, self.cursorX+1);
            }
        }
    
        self.modifyOverCursorXValue();
        
        self.digitInput = 0;
    }
    else {
        var line = self.texts.item(self.scroll+self.cursorY, null);
        
        if(self.cursorX > 0) {
            self.cursorX--;
            line.delete(self.cursorX, self.cursorX+1);
        }
    
        self.modifyOverCursorXValue();
    }
}

void ViWin_getCursorNumber(ViWin* self, int* head, int* tail) 
{
    var line = self.texts.item(self.scroll+self.cursorY, null);
    
    var c = line[self.cursorX];

    if(xiswdigit(c)) {
        /// back ///
        *head = self.cursorX;

        if(*head > 0) {
            while(true) {
                if(*head < 0) {
                    break;
                }

                var c = line[*head];
                
                if(xiswdigit(c)) {
                    (*head)--;
                }
                else {
                    (*head)++;
                    break;
                }
            }
        }
        
        if(*head < 0) {
            *head = 0;
        };

        *tail = self.cursorX;
        
        while(true) {
            var c = line[*tail];
            
            if(xiswdigit(c)) {
                (*tail)++;
            }
            else {
                break;
            }
        }
    }
    else {
        *head = -1;
        *tail = -1;
    }
}

void ViWin_incrementNumber(ViWin* self) 
{
    self.pushUndo();
    
    if(self.digitInput > 0) {
        int num = self.digitInput + 1;
        
        var line = self.texts.item(self.scroll+self.cursorY, null);
        
        int head;
        int tail;
        self.getCursorNumber(&head, &tail);
        
        if(head != -1 && tail != -1) {
            string number_string = line.substring(head, tail).to_string();
            
            int n = atoi(number_string);
            
            n += num;
            
            var new_line = borrow xsprintf("%ls%d%ls", line.substring(0, head), n, line.substring(tail, -1)).to_wstring();
            
            self.texts.replace(self.scroll+self.cursorY, new_line);
        }
    
        self.modifyOverCursorXValue();
        
        self.digitInput = 0;
    }
    else {
        var line = self.texts.item(self.scroll+self.cursorY, null);
        
        int head;
        int tail;
        self.getCursorNumber(&head, &tail);
        
        if(head != -1 && tail != -1) {
            string number_string = line.substring(head, tail).to_string();
            
            int n = atoi(number_string);
            
            n++;
            
            var new_line = borrow xsprintf("%ls%d%ls", line.substring(0, head), n, line.substring(tail, -1)).to_wstring();
            
            self.texts.replace(self.scroll+self.cursorY, new_line);
        }

        self.modifyOverCursorXValue();
    }
}

void ViWin_replaceCursorCharactor(ViWin* self) 
{
    self.pushUndo();
    
    var key = self.getKey(false);
    
/*
    if(self.digitInput > 0) {
        int num = self.digitInput + 1;
        
        var line = self.texts.item(self.scroll+self.cursorY, null);
        
        for(int i= 0; i<num; i++) {
            line.replace(self.cursorX+i, (wchar_t)key);
        }
        
        self.digitInput = 0;
    }
    else {
*/
        var line = self.texts.item(self.scroll+self.cursorY, null);
        line[self.cursorX] = (wchar_t)key;
//    }
}

void ViWin_deleteUntilTail(ViWin* self) 
{
    self.pushUndo();
    
    if(self.digitInput > 0) {
        var line = self.texts.item(self.scroll+self.cursorY, null);
        
        line.delete(self.cursorX, -1);
        
        int num = self.digitInput + 1;
        
        for(int i=1; i<num; i++) {
            var line = self.texts.item(self.scroll+self.cursorY+1, null);
            
            if(line != null) {
                self.texts.delete(self.scroll+self.cursorY+1, self.scroll+self.cursorY+1+1);
        
                self.modifyCursorOnDeleting();
            }
        }
        
        self.modifyOverCursorXValue();
        
        self.digitInput = 0;
    }
    else {
        var line = self.texts.item(self.scroll+self.cursorY, null);
        line.delete(self.cursorX, -1);
        
        self.modifyOverCursorXValue();
    }
}

void ViWin_joinLines(ViWin* self) 
{
    self.pushUndo();

    if(self.scroll+self.cursorY+1 < self.texts.length()) {
        var line = self.texts.item(self.scroll+self.cursorY, null);
        var next_line = self.texts.item(self.scroll+self.cursorY+1, null);

        var line2 = borrow xsprintf("%ls %ls", line, next_line).to_wstring();

        self.texts.replace(self.scroll+self.cursorY, line2);
        self.texts.delete(self.scroll+self.cursorY+1, self.scroll+self.cursorY+1+1);
    }

    self.modifyOverCursorXValue();
}

void ViWin_yankOneLine(ViWin* self, Vi* nvi) 
{
    if(self.digitInput > 0) {
        self.pushUndo();
        
        nvi.yank.reset();
        nvi.yankKind = kYankKindLine;
        
        for(int i=0; i<self.digitInput+1; i++) {
            var line = self.texts.item(self.scroll+self.cursorY+i, null);
            
            if(line != null) {
                nvi.yank.push_back(clone line);
            }
        }
        
        self.digitInput = 0;
        self.saveYankToFile(nvi);
    }
    else {
        var line = self.texts.item(self.scroll+self.cursorY, null);

        if(line != null) {
            self.pushUndo();
            nvi.yank.reset();
            nvi.yank.push_back(clone line);
            nvi.yankKind = kYankKindLine;
            self.saveYankToFile(nvi);
        }
    }
}

void ViWin_joinLines2(ViWin* self) version 2
{
    self.pushUndo();

    if(self.scroll+self.cursorY+1 < self.texts.length()) {
        var line = self.texts.item(self.scroll+self.cursorY, null);
        var next_line = borrow clone self.texts.item(self.scroll+self.cursorY+1, null);

        self.texts.replace(self.scroll+self.cursorY, xsprintf("%ls%ls", line, next_line).to_wstring());
        self.texts.delete(self.scroll+self.cursorY+1, self.scroll+self.cursorY+1+1);
    }

    self.modifyOverCursorXValue();
}

void ViWin_forwardToNextCharacter1(ViWin* self, int key) 
{
    self.mRepeatFowardNextCharacterKind = kRFNC1;
    self.mRepeatFowardNextCharacter = key;
    
    var line = self.texts.item(self.scroll+self.cursorY, null);
    
    if(self.digitInput > 0) {
        for(int i=0; i<self.digitInput+1; i++) {
            var cursor_x = line.substring(self.cursorX+1, -1).index(xsprintf("%c", key).to_wstring(), -1);
            
            if(cursor_x != -1) {
                self.cursorX += cursor_x + 1;
            }
            else {
                break;
            }
        }
        
        self.digitInput = 0;
    }
    else {
        var cursor_x = line.substring(self.cursorX + 1, -1).index(xsprintf("%c", key).to_wstring(), -1);
        
        if(cursor_x != -1) {
            self.cursorX += cursor_x + 1;
        }
    }
}

void ViWin_forwardToNextCharacter2(ViWin* self, int key) 
{
    self.mRepeatFowardNextCharacterKind = kRFNC2;
    self.mRepeatFowardNextCharacter = key;
    
    var line = self.texts.item(self.scroll+self.cursorY, null);
    
    if(self.digitInput > 0) {
        for(int i=0; i<self.digitInput+1; i++) {
            var cursor_x = line.substring(self.cursorX + 2, -1).index(xsprintf("%c", key).to_wstring(), -1);
            
            if(cursor_x != -1) {
                self.cursorX += cursor_x + 1;
            }
            else {
                break;
            }
        }
        
        self.digitInput = 0;
    }
    else {
        var cursor_x = line.substring(self.cursorX+1, -1).index(xsprintf("%c", key).to_wstring(), -1);
        
        if(cursor_x != -1) {
            self.cursorX += cursor_x;
        }
    }
}

void ViWin_repeatForwardNextCharacter(ViWin* self) 
{
    switch(self.mRepeatFowardNextCharacterKind) {
        case kRFNC1:
            self.forwardToNextCharacter1(self.mRepeatFowardNextCharacter);
            break;
            
        case kRFNC2:
            self.cursorX++;
            self.forwardToNextCharacter2(self.mRepeatFowardNextCharacter);
            break;
    }
}

void ViWin_backwardToNextCharacter1(ViWin* self) 
{
    var key = self.getKey(false);
    
    var line = self.texts.item(self.scroll+self.cursorY, null);
    
    if(self.digitInput > 0) {
        for(int i=0; i<self.digitInput+1; i++) {
            var cursor_x = line.substring(0, self.cursorX).rindex(xsprintf("%c", key).to_wstring(), -1);
            
            if(cursor_x != -1) {
                self.cursorX = cursor_x;
            }
            else {
                break;
            }
        }
        
        self.digitInput = 0;
    }
    else {
        var cursor_x = line.substring(0, self.cursorX).rindex(xsprintf("%c", key).to_wstring(), -1);
        
        if(cursor_x != -1) {
            self.cursorX = cursor_x;
        }
    }
}

void ViWin_backwardToNextCharacter2(ViWin* self) 
{
    var key = self.getKey(false);
    
    var line = self.texts.item(self.scroll+self.cursorY, null);
    
    if(self.digitInput > 0) {
        for(int i=0; i<self.digitInput+1; i++) {
            var cursor_x = line.substring(0, self.cursorX-1).rindex(xsprintf("%c", key).to_wstring(), -1);
            
            if(cursor_x != -1) {
                self.cursorX = cursor_x + 1;
            }
            else {
                break;
            }
        }
        
        self.digitInput = 0;
    }
    else {
        var cursor_x = line.substring(0, self.cursorX).rindex(xsprintf("%c", key).to_wstring(), -1);
        
        if(cursor_x != -1) {
            self.cursorX = cursor_x + 1;
        }
    }
}

void ViWin_changeCase(ViWin* self) 
{
    self.pushUndo();

    var line = self.texts.item(self.scroll+self.cursorY, null);
    
    if(self.digitInput > 0) {
        for(int i=0; i<self.digitInput+1; i++) {
            wchar_t c = line[self.cursorX + i];
            
            if(c != -1) {
                if(c >= 'a' && c <= 'z') {
                    wchar_t c2 = c - 'a' + 'A';
                    
                    line[self.cursorX + i] = c2;
                }
                else if(c >= 'A' && c <= 'Z') {
                    wchar_t c2 = c - 'A' + 'a';
                    
                    line[self.cursorX + i] = c2;
                }
            }
            else {
                break;
            }
        }
        
        self.digitInput = 0;
    }
    else {
        wchar_t c = line[self.cursorX];
            
        if(c != -1) {
            if(c >= 'a' && c <= 'z') {
                wchar_t c2 = c - 'a' + 'A';
                
                line[self.cursorX] = c2;
            }
            else if(c >= 'A' && c <= 'Z') {
                wchar_t c2 = c - 'A' + 'a';
                
                line[self.cursorX] = c2;
            }
        }
    }
}

void ViWin_moveToHead(ViWin* self) 
{
    var line = self.texts.item(self.scroll+self.cursorY, null);
    
    int i;
    for(i=0; i<line.length(); i++) {
        if(!(line[i] == ' ' && line[i] == '\t')) {
            break;
        }
    }

    self.cursorX = i;
}

Vi*% Vi_initialize(Vi*% self) version 10
{
    var result = inherit(self);

    result.events.replace('d', lambda(Vi* self, int key) {
        var key2 = self.activeWin.getKey(true);

        switch(key2) {
            case 'd':
                self.activeWin.deleteOneLine(self);
                self.activeWin.writed = true;
                break;
            
            case 'w':
            case 'e':
                self.activeWin.deleteWord(self);
                self.activeWin.writed = true;
                break;
            
            case 'f':
                self.activeWin.deleteForNextCharacter();
                self.activeWin.writed = true;
                break;
                
            case 't':
                self.activeWin.deleteForNextCharacter2();
                self.activeWin.writed = true;
                break;
                
            case '$':
                self.activeWin.deleteUntilTail();
                self.activeWin.writed = true;
                break;
        }

        self.activeWin.saveInputedKey();
    });

    result.events.replace('c', lambda(Vi* self, int key) {
        var key2 = self.activeWin.getKey(true);

        switch(key2) {
            case '$':
                self.activeWin.deleteUntilTail();
                self.enterInsertMode();
                if(self.activeWin.texts.length() != 0) {
                    self.activeWin.cursorX++;
                }
                self.activeWin.writed = true;
                break;
                
            case 'c':
                self.activeWin.deleteOneLine2(self);
                self.enterInsertMode();
                if(self.activeWin.texts.length() != 0) {
                    self.activeWin.cursorX = 0;
                }
                self.activeWin.writed = true;
                break;
                
                
            case 'w':
            case 'e':
                self.activeWin.deleteWord(self);
                self.enterInsertMode2();
                self.activeWin.writed = true;
                break;
                
            case 't':
                self.activeWin.deleteForNextCharacter2();
                self.enterInsertMode();
                self.activeWin.writed = true;
                break;
                
            case 'f':
                self.activeWin.deleteForNextCharacter();
                self.enterInsertMode();
                self.activeWin.writed = true;
                break;
        }
    });
    result.events.replace('y', lambda(Vi* self, int key) {
        var key2 = self.activeWin.getKey(true);

        switch(key2) {
            case 'y':
                self.activeWin.yankOneLine(self);
                break;
        }
    });
    result.events.replace('Y', lambda(Vi* self, int key) {
        self.activeWin.yankOneLine(self);
    });
    result.events.replace('D', lambda(Vi* self, int key) {
        self.activeWin.deleteUntilTail();
        self.activeWin.writed = true;

        self.activeWin.saveInputedKey();
    });

    result.events.replace('C', lambda(Vi* self, int key) {
        self.activeWin.deleteUntilTail();
        self.enterInsertMode();
        if(self.activeWin.texts.length() != 0) {
            self.activeWin.cursorX++;
        }
        self.activeWin.writed = true;
    });
    result.events.replace('x', lambda(Vi* self, int key) {
        self.activeWin.deleteCursorCharactor();
        self.activeWin.writed = true;

        self.activeWin.saveInputedKey();
    });
    result.events.replace('X', lambda(Vi* self, int key) {
        self.activeWin.deleteBack();
        self.activeWin.writed = true;

        self.activeWin.saveInputedKey();
    });
    result.events.replace('A'-'A'+1, lambda(Vi* self, int key) {
        self.activeWin.incrementNumber();
        self.activeWin.writed = true;

        self.activeWin.saveInputedKey();
    });
    result.events.replace('r', lambda(Vi* self, int key) {
        self.activeWin.replaceCursorCharactor();
        self.activeWin.writed = true;

        self.activeWin.saveInputedKey();
    });
    result.events.replace('s', lambda(Vi* self, int key) {
        self.activeWin.replaceCursorCharactor();
        self.activeWin.writed = true;
        self.enterInsertMode();
    });
    result.events.replace('S', lambda(Vi* self, int key) {
        self.activeWin.moveToHead();
        self.activeWin.deleteUntilTail();
        self.activeWin.writed = true;
        self.enterInsertMode();
        if(self.activeWin.cursorX != 0) {
            self.activeWin.cursorX++;
        }
    });
    result.events.replace('J', lambda(Vi* self, int key) {
        self.activeWin.joinLines();
        self.activeWin.writed = true;

        self.activeWin.saveInputedKey();
    });
    result.events.replace('~', lambda(Vi* self, int key) {
        self.activeWin.changeCase();

        self.activeWin.saveInputedKey();
    });
    result.events.replace('f', lambda(Vi* self, int key) {
        var key2 = self.activeWin.getKey(false);
        
        self.activeWin.forwardToNextCharacter1(key2);

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('t', lambda(Vi* self, int key) {
        var key2 = self.activeWin.getKey(false);

        self.activeWin.forwardToNextCharacter2(key2);

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace(';', lambda(Vi* self, int key) {
        self.activeWin.repeatForwardNextCharacter();

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('F', lambda(Vi* self, int key) {
        self.activeWin.backwardToNextCharacter1();

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('T', lambda(Vi* self, int key) {
        self.activeWin.backwardToNextCharacter2();

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('^', lambda(Vi* self, int key) {
        self.activeWin.moveToHead();

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('-', lambda(Vi* self, int key) {
        self.activeWin.moveToHead();

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('_', lambda(Vi* self, int key) {
        self.activeWin.moveToHead();

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('H', lambda(Vi* self, int key) {
        self.activeWin.cursorX = 0;
        self.activeWin.cursorY = 0;

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('L', lambda(Vi* self, int key) {
        self.activeWin.cursorY = self.activeWin.height-2;
        self.activeWin.modifyOverCursorYValue();
        
        self.activeWin.moveToHead();

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('+', lambda(Vi* self, int key) {
        self.activeWin.cursorY++;
        self.activeWin.modifyOverCursorYValue();
        self.activeWin.moveToHead();

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('Y'-'A'+1, lambda(Vi* self, int key) {
        self.activeWin.scroll--;
        if(self.activeWin.scroll < 0) {
            self.activeWin.scroll = 0;
        }

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });
    result.events.replace('E'-'A'+1, lambda(Vi* self, int key) {
        self.activeWin.scroll++;
        if(self.activeWin.scroll >= self.activeWin.texts.length()) {
            self.activeWin.scroll = self.activeWin.texts.length()-1;
        }
        self.activeWin.modifyOverCursorYValue();
        self.activeWin.modifyUnderCursorYValue();

        self.activeWin.saveInputedKeyOnTheMovingCursor();
    });

    return result;
}
