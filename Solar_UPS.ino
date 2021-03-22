#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C _lcd1(0x27, 20, 4);
int _dispTempLength1=0;
boolean _isNeedClearDisp1;
bool _gtv1 = 0;
int _disp1oldLength = 0;
int _disp3oldLength = 0;
int _disp4oldLength = 0;
int _disp2oldLength = 0;
void setup()
{
    pinMode(5, OUTPUT);
    digitalWrite(5, 1);
    Wire.begin();
    delay(10);
    _lcd1.init();
    _lcd1.backlight();
}
void loop()
{
    if (_isNeedClearDisp1) 
    {
        _lcd1.clear();
        _isNeedClearDisp1= 0;
    }
    //Плата:1
    _gtv1 = (4) > ((map(((analogRead (0))), (0), (1023), (0), (5))));
    digitalWrite(5, (4) > ((map(((analogRead (0))), (0), (1023), (0), (5)))));
    //Плата:2
    if (_gtv1 == 1) 
    {
        if (1) 
        {
            _dispTempLength1 = (String("Energy level - low")).length();
            if (_disp1oldLength > _dispTempLength1) 
            {
                _isNeedClearDisp1 = 1;
            }
            _disp1oldLength = _dispTempLength1;
            _lcd1.setCursor(int((20 - _dispTempLength1)/2), 1);
            _lcd1.print(String("Energy level - low"));
        }
         else 
        {
            if (_disp1oldLength > 0) 
            {
                _isNeedClearDisp1 = 1;
                _disp1oldLength = 0;
            }
        }
        if (1) 
        {
            _dispTempLength1 = (String("Relay ON")).length();
            if (_disp3oldLength > _dispTempLength1) 
            {
                _isNeedClearDisp1 = 1;
            }
            _disp3oldLength = _dispTempLength1;
            _lcd1.setCursor(int((20 - _dispTempLength1)/2), 2);
            _lcd1.print(String("Relay ON"));
        }
         else 
        {
            if (_disp3oldLength > 0) 
            {
                _isNeedClearDisp1 = 1;
                _disp3oldLength = 0;
            }
        }
    }
    //Плата:3
    if (_gtv1 == 0) 
    {
        if (1) 
        {
            _dispTempLength1 = (String("Energy level - high")).length();
            if (_disp2oldLength > _dispTempLength1) 
            {
                _isNeedClearDisp1 = 1;
            }
            _disp2oldLength = _dispTempLength1;
            _lcd1.setCursor(int((20 - _dispTempLength1)/2), 1);
            _lcd1.print(String("Energy level - high"));
        }
         else 
        {
            if (_disp2oldLength > 0) 
            {
                _isNeedClearDisp1 = 1;
                _disp2oldLength = 0;
            }
        }
        if (1) 
        {
            _dispTempLength1 = (String("Relay OFF")).length();
            if (_disp4oldLength > _dispTempLength1) 
            {
                _isNeedClearDisp1 = 1;
            }
            _disp4oldLength = _dispTempLength1;
            _lcd1.setCursor(int((20 - _dispTempLength1)/2), 2);
            _lcd1.print(String("Relay OFF"));
        }
         else 
        {
            if (_disp4oldLength > 0) 
            {
                _isNeedClearDisp1 = 1;
                _disp4oldLength = 0;
            }
        }
    }
}
