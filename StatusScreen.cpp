//
// StatusScreen.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode+
// http://embedXcode.weebly.com
//
// Project 		StatusScreen
//
// Created on 	22/07/2016
//
// Copyright 	Christophe Persoz, 2016
// Licence		All Right Reserved (c) - GNU 3.0 Licence
//
// See 			StatusScreen.h and ReadMe.txt for references
//


// ::::::: LIBRARY Header
#include <StatusScreen.h>


// ::::::: DEFINES
#define PRINT(x,y,t,c) u8g->setColorIndex(c);u8g->drawStr(x,y,t);
#define SPRINT(x,y,t,c) u8g->setColorIndex(c);u8g->setPrintPos(x,y);u8g->print(t);
#define CONCATSTR(b,f,v,s,u); sprintf(b, f, v); sprintf(b + strlen(b), s); sprintf(b + strlen(b),u)
#define CLAMP(v,l,h)  ((v > h) ? h : ((v < l) ? l : v))


// ::::::: CLASS StatusScreen
StatusScreen::StatusScreen(U8GLIB* gfx) :
u8g(gfx)
{}

void* StatusScreen::newScreen(uint8_t x = 0, uint8_t y = 0, boolean TTRow = true) {
    
    xO = (x >= 0 && x < u8g->getWidth()) ? x:0;
    yO = (y >= 0 && y < u8g->getHeight()) ? y:0;
    idx_s = 0;
    nT = 0;
    
    nPage = 0;
    cPage = 0;
    sI, eI = 0;
    
    ttNewRow = TTRow;
    activePageNav = false;
}


void StatusScreen::addTitle(const char* _label) {
    if ( idx_s <= NBSTATUS)
    {
        s[idx_s].type = TTITLE;
        s[idx_s].label = _label;
        if (nT%NBROW == 0)
            nPage++;
        
        idxT[nT++] = idx_s++; // set the idx array for titles
    }
}

void StatusScreen::addField(const char* _label, uint8_t _color) {
    if ( idx_s <= NBSTATUS)
    {
        s[idx_s].type = TFIELD;
        s[idx_s].color = _color;
        s[idx_s++].label = _label;
    }
}

void StatusScreen::addByte(const char* _label, uint8_t* val, const char* _unit) {
    if ( idx_s <= NBSTATUS)
    {
        s[idx_s].type = TBYTE;
        s[idx_s].label = _label;
        s[idx_s].unit = _unit;
        s[idx_s++].value = val; // store the pointer to the uint8_t passed variable
    }
}

void StatusScreen::addInt(const char* _label, uint16_t* val, const char* _unit) {
    if ( idx_s <= NBSTATUS)
    {
        s[idx_s].type = TINT;
        s[idx_s].label = _label;
        s[idx_s].unit = _unit;
        s[idx_s++].value = val; // store the pointer to the uint16_t passed variable
    }
}

void StatusScreen::addLong(const char* _label, uint32_t* val, const char* _unit) {
    if ( idx_s <= NBSTATUS)
    {
        s[idx_s].type = TLONG;
        s[idx_s].label = _label;
        s[idx_s].unit = _unit;
        s[idx_s++].value = val; // store the pointer to the uint32_t passed variable
    }
}

void StatusScreen::addFloat(const char* _label, float_t* val, const char* _unit,  uint8_t _fprec=4) {
    if ( idx_s <= NBSTATUS)
    {
        s[idx_s].type = TFLOAT;
        s[idx_s].label = _label;
        s[idx_s].unit = _unit;
        s[idx_s].fprec = _fprec;
        s[idx_s++].value = val; // store the pointer to the float passed variable
    }
}

void StatusScreen::addBool(const char* _label, const char* _tBool, const char* _fBool, boolean* val) {
    if ( idx_s <= NBSTATUS)
    {
        s[idx_s].type = TBOOL;
        s[idx_s].label = _label;
        s[idx_s].tBool = _tBool;
        s[idx_s].fBool = _fBool;
        s[idx_s++].value = val; // store the pointer to the boolean passed variable
    }
}

void StatusScreen::addBlank() {
    if ( idx_s <= NBSTATUS)
    {
        s[idx_s].type = TFIELD;
        s[idx_s++].label = " ";
    }
}

void StatusScreen::activatePageNav(uint8_t x, uint8_t y)
{
    activePageNav = !activePageNav;
    xN = CLAMP(x, 0, WDISP-1);
    yN = CLAMP(y, 0, HDISP-1);
}


void StatusScreen::drawPageNav()
{
    uint8_t buf_sz = 4; // Index current page + / + total pages
    obuf = (char*)malloc(buf_sz + 1);
    memset(obuf, ' ', buf_sz);
    obuf[buf_sz] = 0;
    
    sprintf(obuf, "%i/%i", cPage+1, nPage);
    
    PRINT(xN, yN, obuf, DGREY);
}


void StatusScreen::setPage(uint8_t cP)
{
    cPage = cP;
    
    if (ttNewRow)
    {
        sI = idxT[cPage*NBROW];
        if ((cPage*NBROW+2 >= sizeof(idxT)) || (cPage*NBROW+1 == NBTITLES))
            eI = NBSTATUS-1;
        else
            eI = idxT[cPage*NBROW+2]-1;
        
    } else {
        // Continuous display not yet supported
    }
}

uint8_t StatusScreen::getPage()
{
    return (cPage);
}

uint8_t StatusScreen::getMaxPage()
{
    return (nPage-1);
}

void StatusScreen::draw()
{
    uint8_t i;
    uint8_t nbLine, curLine = 0;
    int8_t curRow = -1;
    boolean newRow = false;
    uint8_t buf_sz = 0;
    uint8_t wd_val = 0;
    uint8_t offset = (ttNewRow)?OFFSETT:0;
    nbLine = ((HDISP-xO)/(LSPACE+offset));
    
    // memealloc for line buffer, where r and c are row and col values
    buf_sz = (WDISP/FONTW)/NBROW;
    
    obuf = (char*)malloc(buf_sz + 1); // Mem allocation for one line
    memset(obuf, ' ', buf_sz);
    obuf[buf_sz] = 0;
    
    // display settings
    u8g->setFont(TYPEFACE);
    u8g->setFontPosTop();
    
    // build display
    for (i = sI; i <= eI; i++)
    {
        // Row and Line calculations
        if ((curLine > nbLine && !ttNewRow) || (ttNewRow && s[i].type == TTITLE))
        {
            curLine = 0;
            if (curRow < NBROW)
                curRow++;
            else
                curRow = -1;
        }
        
        yO = (s[i].type == TTITLE) ? (curLine*LSPACE) : (curLine*LSPACE+offset);
        
        switch (s[i].type)
        {
            case TTITLE:
                strcpy(obuf, " # ");
                strcat(obuf, s[i].label);
                
                u8g->setColorIndex(MGREY);
                u8g->drawBox(dispRow[curRow], 0, (WDISP/NBROW - 10), LSPACE-1);
                PRINT(dispRow[curRow], yO+1, obuf, BLACK);
                break;
                
            case TBYTE:
                strcpy(obuf,s[i].label);
                strcat(obuf," ");
                PRINT(dispRow[curRow], yO, obuf, DGREY);
                wd_val = u8g->getStrWidth(obuf);
                CONCATSTR(obuf, "%d", *(uint8_t*)s[i].value, " ", s[i].unit);
                SPRINT(dispRow[curRow] + wd_val, yO, obuf, WHITE);
                break;
                
            case TINT:
                strcpy(obuf,s[i].label);
                strcat(obuf," ");
                PRINT(dispRow[curRow], yO, obuf, DGREY);
                wd_val = u8g->getStrWidth(obuf);
                CONCATSTR(obuf, "%d", *(uint16_t*)s[i].value, " ", s[i].unit);
                SPRINT(dispRow[curRow] + wd_val, yO, obuf, WHITE);
                break;
                
            case TLONG:
                strcpy(obuf,s[i].label);
                strcat(obuf," ");
                PRINT(dispRow[curRow], yO, obuf, DGREY);
                wd_val = u8g->getStrWidth(obuf);
                CONCATSTR(obuf, "%d", *(uint32_t*)s[i].value, " ", s[i].unit);
                SPRINT(dispRow[curRow] + wd_val, yO, obuf, WHITE);
                break;
                
            case TFLOAT:
                strcpy(obuf,s[i].label);
                strcat(obuf," ");
                PRINT(dispRow[curRow], yO, obuf, DGREY);
                wd_val = u8g->getStrWidth(obuf);
                dtostrf(*(float_t*)s[i].value, 4, s[i].fprec, obuf);
                sprintf(obuf + strlen(obuf), s[i].unit);
                SPRINT(dispRow[curRow] + wd_val, yO, obuf, WHITE);
                break;
                
            case TBOOL:
                strcpy(obuf,s[i].label);
                strcat(obuf," ");
                PRINT(dispRow[curRow], yO, obuf, DGREY);
                PRINT(dispRow[curRow] + (u8g->getStrWidth(obuf)), yO, (*(boolean*)s[i].value)?s[i].tBool:s[i].fBool, WHITE);
                break;
                
            case TFIELD:
                strcpy(obuf,s[i].label);
                PRINT(dispRow[curRow], yO, obuf, s[i].color);
                break;
        }
        
        (curLine <= nbLine) ? curLine++ : curLine=0;
    }
    if (activePageNav)
        drawPageNav();
}

// ::::::: CLASS _status

_item::_item() {}


