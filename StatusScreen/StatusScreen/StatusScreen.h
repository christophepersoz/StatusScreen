///
/// @mainpage	StatusScreen Library
///
/// @details	Display vars on graphical screens splited in pages
/// @n			Library
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Christophe Persoz
/// @author		Christophe Persoz
///
/// @date		27/09/2016 17:47
/// @version	<#version#>
///
/// @copyright	(c) Christophe Persoz, 2016
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
///


///
/// @file		StatusScreen_Library.h
/// @brief		Library header
/// Project 	StatusScreen Library
///
/// @details	<#details#>
/// @n
/// @n @b		Project StatusScreen
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Christophe Persoz
/// @author		Christophe Persoz
///
/// @date		27/09/2016 17:47
/// @version	<#version#>
///
/// @copyright	(c) Christophe Persoz, 2016
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
///


// Core library for code-sense - IDE-based
#if defined(WIRING) // Wiring specific
    #include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
    #include "WProgram.h"
#elif defined(ROBOTIS) // Robotis specific
    #include "libpandora_types.h"
    #include "pandora.h"
#elif defined(MPIDE) // chipKIT specific
    #include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
    #include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
    #include "Energia.h"
#elif defined(LITTLEROBOTFRIENDS) // LittleRobotFriends specific
    #include "LRF.h"
#elif defined(MICRODUINO) // Microduino specific
    #include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
    #include "Arduino.h"
#elif defined(REDBEARLAB) // RedBearLab specific
    #include "Arduino.h"
#elif defined(RFDUINO) // RFduino specific
    #include "Arduino.h"
#elif defined(SPARK) || defined(PARTICLE) // Particle / Spark specific
    #include "application.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
    #include "Arduino.h"
#else // error
    #error Platform not defined
#endif // end IDE

#ifndef StatusScreen_RELEASE
    #define StatusScreen_RELEASE 100


#endif
