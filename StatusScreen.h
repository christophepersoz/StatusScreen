///
/// @file		StatusScreen.h
/// @brief		Library header
/// @details	Display informations on sceen with a label, position and dynamic value
/// @n
/// @n @b		Related to project MOCO
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Christophe Persoz
///
/// @date		20/07/2016 16:16
/// @version	1.0
///
/// @copyright	(c) Christophe Persoz, 2016
/// @copyright	All Right Reserved (c)
///
/// @see		ReadMe.txt for references
///

#ifndef __StatusScreen_cpp__
#define __StatusScreen_cpp__

// ::::::: INCLUDES

// Core library for code-sense - IDE-based
#if defined(TEENSYDUINO) // Teensy specific
    #include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
    #include "Arduino.h"
#else // error
    #error Platform not defined
#endif // end IDE
#include <U8g_teensy.h>
#include <ClickEncoder.h>


// ::::::: DEFINES

#define NBSTATUS   25   // Number of status items
#define NBTITLES    5   // Number of titles items

    // DISPLAY DETAILS
#define WDISP   256                     // display's width
#define HDISP   64                      // display's height
#define NBROW   2                       // number of colonnes to display
#define WHITE   3                       // White level on OLED
#define MGREY   2                       // Gray level on OLED
#define DGREY   1                       // Dark gray level on OLED
#define BLACK   0                       // Black level on OLED

#define TYPEFACE u8g_font_04b_03e       // U8G Typeface used for display
                                        //  # -> Square, $ -> Right arrow
                                        //  & -> Left arrow, ~ -> º
                                        //  ^ -> mm

#define FONTH   9                       // Font height
#define FONTW   7                       // Font width
#define LSPACE  10                      // Line spacing
#define OFFSETT 2                       // Offset under titles


    // CONSTANTS
#define TTITLE  0
#define TBYTE   1
#define TINT    2
#define TLONG   3
#define TFLOAT  4
#define TBOOL   5
#define TFIELD  6

#define TYPE    uint8_t

// ::::::: CLASS Status
class _item {
public:
    _item();
    
    TYPE        type;
    const char* label;
    const char* tBool;
    const char* fBool;
    const char* unit;
    TYPE        color;
    void*       value;
private:
    
protected:

};


// ::::::: CLASS StatusScreen
class StatusScreen {

public:

    StatusScreen(U8GLIB* gfx, ClickEncoder* enc);
    
    void*       newScreen(uint8_t, uint8_t, boolean);
    void        addTitle(const char*); // section title
    void        addField(const char*, uint8_t); // text value
    void        addByte(const char*, uint8_t*, const char*); // uint8_t value
    void        addInt(const char*, uint16_t*, const char*); // uint16_t value
    void        addLong(const char*, uint32_t*, const char*); // uint32_t value
    void        addFloat(const char*, float*, const char*); // float value
    void        addBool(const char*, const char*, const char*, boolean*); // boolean value with personnalized labels for 0:1
    void        addBlank(); // blank line
    
    void        setPage(uint8_t);  // Set the current page to draw
    uint8_t     getPage();         // Get the current page to draw
    uint8_t     getMaxPage();      // Get the number of available pages
    void        activatePageNav(uint8_t, uint8_t);  //Activate the page index on display
    
    void        draw(); // Draw page
    
    uint8_t     idx_s;  // index status
    _item       s[NBSTATUS];
    void        *var;
private:
    U8GLIB*     u8g;
    ClickEncoder* qenc;
    uint8_t     dispRow[NBROW] = { 0, 128 }; //, 172}; // Rows on display
    char*       obuf;   // Print out screen buffer (line witdh of chars)
    
    uint8_t     nbT;    // Nb AddTitles in definition
    uint8_t     nPage;  // Nb Pages
    uint8_t     cPage;  // Current Page
    uint8_t     idxT[NBTITLES];
    uint8_t     nT;     // Nb Titles
    
    uint8_t     sI; // start idx for items on pages
    uint8_t     eI; // stop idx for items on pages
    uint8_t     encV;
    boolean     activePageNav;
    
    void        drawPageNav(); // Show current page on pages
    
protected:
    uint8_t     xO;         // origin for the title
    uint8_t     yO;
    uint8_t     xN;
    uint8_t     yN;
    boolean     ttNewRow;   // titles create a new row
};

#endif
