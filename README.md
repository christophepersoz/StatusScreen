# StatusScreen
Allows to display graphic status pages and browse them with rotary encoder.

I developped this library to run it on a Teensy 3.2 ARM board but it should be compatible with Arduino.
The display I use is a OLED SSD 1322 (256x64 pixels) with grey shade, but you can change that and take advantage of all the displays supported by U8Glib.


![ER-OLEDM032-1W.jpg](https://github.com/christophepersoz/StatusScreen/blob/master/screenshots/ER-OLEDM032-1W.jpg)

Display : SSD1322 Buy Display ER-OLEDM032-1W fully compatible with NHD1322



This library use U8Glib.h and ClickEncoder.h in order to work, they are included in a separate ZIP file.

Links :
 * U8Glib [supported devices](https://github.com/olikraus/u8glib/wiki/device)
 * [U8glib for Arduino](https://bintray.com/olikraus/u8glib/Arduino)
 * [U8g2 for Arduino](https://bintray.com/olikraus/u8g2)
 * Converter for BDF fonts: [bdf2u8g_101.exe on google drive](https://drive.google.com/folderview?id=0B5b6Dv0wCeCRLWJkYTh2TUlYVDg&usp=sharing).
 * U8glib [documentation and tutorials](https://github.com/olikraus/u8glib/wiki)
 
 * Arduino [ClickEncoder library](https://github.com/0xPIT/encoder/tree/arduino)
 * Original [ClickEncoder library](https://github.com/robogeek78/SparkCore-ClickEncoder) for SparkCore
