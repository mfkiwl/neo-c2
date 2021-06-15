#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <wctype.h>

ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi) version 3
{
    var result = inherit(self, y, x, width, height, vi);

    result.undo = borrow new list<list<wstring>*%>.initialize();
    result.undoScroll = borrow new list<int>.initialize();
    result.undoCursorX = borrow new list<int>.initialize();
    result.undoCursorY = borrow new list<int>.initialize();
    result.undoIndex = 0;

    return result;
}

void ViWin_finalize(ViWin* self) version 3
{
    inherit(self);

    delete self.undo;
    delete self.undoScroll;
    delete self.undoCursorX;
    delete self.undoCursorY;
}

void ViWin_pushUndo(ViWin* self) version 2
{
    self.undo.delete(self.undoIndex, -1);
    self.undoScroll.delete(self.undoIndex, -1);
    self.undoCursorX.delete(self.undoIndex, -1);
    self.undoCursorY.delete(self.undoIndex, -1);

    var undo = borrow clone self.texts;

    self.undo.push_back(undo);

    self.undoCursorX.push_back(self.cursorX);
    self.undoScroll.push_back(self.scroll);
    self.undoCursorY.push_back(self.cursorY);
    self.undoIndex++;
}

void ViWin_redo(ViWin* self) 
{
    if(self.undoIndex < self.undo.length()-1) 
    {
        self.undoIndex++;

        var undo = borrow clone self.undo.item(self.undoIndex, null);
        var cursor_x = self.undoCursorX.item(self.undoIndex, -1);
        var scroll = self.undoScroll.item(self.undoIndex, -1);
        var cursor_y = self.undoCursorY.item(self.undoIndex, -1);

        if(undo != null && cursor_x != -1 && cursor_y != -1 && scroll != -1) 
        {
            self.texts = undo;
            self.cursorX = cursor_x;
            self.cursorY = cursor_y;
            self.scroll = scroll;
        }
    }
}

void ViWin_undo(ViWin* self) 
{
    if(self.undoIndex == self.undo.length())
    {
        self.pushUndo();
        self.undoIndex--;
    }

    if(self.undoIndex > 0) {
        self.undoIndex--;

        var undo = borrow clone self.undo.item(self.undoIndex, null);
        var cursor_x = self.undoCursorX.item(self.undoIndex, -1);
        var cursor_y = self.undoCursorY.item(self.undoIndex, -1);
        var scroll = self.undoScroll.item(self.undoIndex, -1);

        if(undo != null && cursor_x != -1 && cursor_y != -1 && scroll != -1) 
        {
            self.texts = undo;
            self.cursorX = cursor_x;
            self.cursorY = cursor_y;
            self.scroll = scroll;
        }
    }
}

Vi*% Vi_initialize(Vi*% self) version 5
{
    var result = inherit(self);

    result.events.replace('u', lambda(Vi* self, int key) 
    {
        self.activeWin.undo();
    });

    result.events.replace('r'-'a'+1, lambda(Vi* self, int key) 
    {
        self.activeWin.redo();
    });

    return result;
}

void Vi_enterInsertMode(Vi* self) version 2
{
    inherit(self);

    self.activeWin.pushUndo();
}
