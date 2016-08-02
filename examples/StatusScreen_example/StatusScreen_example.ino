///
/// @mainpage  StatusScreen on Graphic display
///
/// @details  Version 1.0 - developped for Teensy 3.2 and SSD1322 OLED SCREEN
/// @n        
/// @n        Under development, see ReadMe.txt for details and log
///
/// @author   Christophe Persoz
/// @date     14/07/2016 20:40
/// @version  1.0a
///
/// @copyright  (c) Christophe Persoz, 2016
/// @copyright  All rights reserved
///
/// @file     StatusScreen_example.ino
/// @brief    Example of use for StatusScreen on Graphic Display with U8GLib and ClickEncoder
///


// Core library for code-sense - IDE-based
#if defined(TEENSYDUINO) // Teensy specific
    #include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
    #include "Arduino.h"
#else // error
    #   error Platform not defined
#endif // end IDE


/* _____ INCLUDES _____ application, user and local libraries */

#include <SPI.h>                // SPI transaction library
#include <U8g_teensy.h>         // OLED display driver
#include <ClickEncoder.h>       // Quad encoder
#include <TimerOne.h>           // ISR on Quad encoder
#include <StatusScreen.h>       // Page which display all the status informations


// Define structures and classes


/* ______ DEFINES _____ */

#define VERSION     "VERSION 1.0"
#define RELEASE     "RELEASED ON 01.08.2016"
#define AUTHOR      "C. PERSOZ (c) 2016"

#define OLED_CS     10
#define OLED_A0     9
#define OLED_RST    8

#define CK_ENC      2 // Quand encoder on an ISR capable input
#define DT_ENC      7
#define SW_ENC      6
//#define SER_OUT     // Print serial for debug, uncomment for Serial Output


/* _____ VARS _____ */

boolean redraw = true;
boolean inStatusPage = true;   // true when inside Status Page

signed char curPage = 0;       // Current Page for Status screen
signed char prvPage = -1;      // Previous Page for Status screen
signed char maxPage = -1;      // Max number of Pages

// TEST VARS
uint8_t nBYTE = 128;
uint16_t nINT = 192;
uint16_t nINT2 = 21939;
uint32_t nLONG = 429496728;
float nFLOAT1 = 55.32017814;
float nFLOAT2 = 3.141592653589793;
float nFLOAT3 = 2.71828182845;
float nFLOAT4 = 1.4142135623;
boolean nBOOL1 = true;
boolean nBOOL2 = false;
boolean nBOOL3 = false;
boolean nBOOL4 = true;
    


/* _____ PROTOTYPES _____ */

U8GLIB _U8G(&u8g_dev_ssd1322_nhd31oled_2x_gr_hw_spi, u8g_com_hw_spi_fn); // HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
ClickEncoder qEnc(DT_ENC, CK_ENC, SW_ENC, 4, LOW);
StatusScreen sScreen(&_U8G, &qEnc);


/* _____ FUNCTIONS _____ */


/*  timerISR()
    Interrupt timer for the Encoder
 */
void timerIsr()
{
    qEnc.service();
}

/*  drawStatusScreen()
    Display all necessaries informations on screen
    Click to exit screen
 */
void drawStatusScreen()
{
    sScreen.draw();
    
    if (prvPage != curPage)
        prvPage = curPage;
    
    redraw = false;
}


/* _____ SETUP _____ */
void setup()
{
#ifdef SER_OUT
    Serial.begin(115200);
    while (!Serial1)
    {}
#endif


    /* _____ STATUS SCREEN DEFINITION _____ */
    // DO NOT FORGET to set the NBSTATUS AND NBTITLES defines in StatusScreen.h 

    sScreen.newScreen(0, 0, true );

    // The special font 04b03e "~" correspond to "º" and "^" correspond to "mm", available on request
    sScreen.addTitle("TITLE 1");
        sScreen.addByte("BYTE", &nBYTE,"");
        sScreen.addInt("INTEGER", &nINT2,"");
        sScreen.addLong("LONG", &nLONG,"");
        sScreen.addFloat("FLOAT", &nFLOAT1," unit"); 
    sScreen.addTitle("TITLE 2");
        sScreen.addBool("BOOLEAN", "TRUE", "FALSE", &nBOOL1);
        sScreen.addFloat("PI", &nFLOAT2,(nBOOL1)?"~":"^"); 
        sScreen.addFloat("RANDOM", &nFLOAT1,(nBOOL2)?"~":" ^");
        sScreen.addFloat("e", &nFLOAT3,"");
        sScreen.addBlank();
    sScreen.addTitle("TITLE 3");
        sScreen.addField("TEXT FIELD", DGREY);
        sScreen.addFloat("2 SQUARE ROOT", &nFLOAT4, "");
        sScreen.addBool("BOOLEAN", "YES", "NO", &nBOOL2);
        sScreen.addBool("BOOLEAN", "UP", "DOWN", &nBOOL3);
        sScreen.addBool("BOOLEAN", "OK", "ERR", &nBOOL4);
    sScreen.addTitle("TITLE 4");
        sScreen.addField("TEST 1", WHITE);
        sScreen.addField("TEST 2", WHITE);
        sScreen.addField("TEST 3", WHITE);
    sScreen.addTitle("TITLE 5");
        sScreen.addField("TEXT FIELD", WHITE);
        sScreen.addBlank();
        sScreen.addField("TEXT FIELD WITH BLANK ABOVE", DGREY);
    sScreen.activatePageNav(240,58);
    
#ifdef SER_OUT
    Serial.print("Nb pages max : ");
    Serial.println(maxPage);
#endif
    
    // Encoder init
    qEnc.setAccelerationEnabled(false);
    qEnc.setDoubleClickEnabled(true);
    
    // OLED init
    _U8G.setHardwareBackup(u8g_backup_avr_spi); // set SPI backup if required
    _U8G.setColorIndex(3); // clear screen, avoiding glitch on display at startup
    _U8G.setContrast(255); // high constrast

    // ISR init
    Timer1.initialize(5000); // every 0.05 seconds
    Timer1.attachInterrupt(timerIsr);
    
}

/* _____ LOOP _____ */
void loop()
{
    
    // Button encoder behavior
    ClickEncoder::Button swEnc = qEnc.getButton();
    if (swEnc != ClickEncoder::Open)
    {
        switch (swEnc)
        {
                case ClickEncoder::Held:
#ifdef SER_OUT
                    Serial.println(F("Bt Held"));
#endif
                break;
            case ClickEncoder::Released:
#ifdef SER_OUT
                    Serial.println(F("Bt Released"));
#endif
                break;

            case ClickEncoder::DoubleClicked:
#ifdef SER_OUT
                    Serial.println(F("Enter status screen"));
#endif
                break;
            
            case ClickEncoder::Clicked:
#ifdef SER_OUT
                    Serial.println(F("Leave status screen"));
#endif
                 break;
        }
    }
    
   // if (inStatusPage)
   // {
        // ON STATUS SCREEN
        curPage += qEnc.getValue();
        
        if (curPage > sScreen.getMaxPage())
            curPage = 0;
        else if (curPage < 0)
            curPage = sScreen.getMaxPage();
            
        if (curPage != prvPage)
        {
            sScreen.setPage(curPage);
            redraw = true;
#ifdef SER_OUT
       Serial.print("curPage : ");Serial.println(curPage);
#endif
        }
    //}

    // Display refresh
    if (redraw)
    {
        _U8G.firstPage();
        do {
                drawStatusScreen();
        } while( _U8G.nextPage() );
    }
}

