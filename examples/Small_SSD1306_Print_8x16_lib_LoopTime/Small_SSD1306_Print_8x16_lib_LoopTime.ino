// Small_SSD1306_Print_8x16_lib_HelloWorld.ino
// Prints "Hello World"
//
// connect display SCL to pin A5, and SDA to pin A4
// connect LED to pin 4 (it will blink in case of I2C error)


#include <Small_SSD1306_Print_8x16_lib.h>

Small_SSD1306_Print_8x16_lib lcd = Small_SSD1306_Print_8x16_lib();

void setup() {
  lcd.begin();
  lcd.setCursorMode(true);
}

void loop() {
//  printFloat();
//  delay(2000);
//  lcd.setPrint8x16CharacterMode(false);
//  loopTime();
//  delay(2000);
  lcd.setPrint8x16CharacterMode(true);
  loopFloat();
  delay(2000);
}

void printHelloWorld(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello");
  lcd.setCursor(10,1);
  lcd.print("World");
}

void scrollHelloWorld(){
  lcd.clear();
  for (int x=0;x<11;x++)
    for (int y=0;y<3;y++){
      lcd.setCursor(x,y);
      lcd.print(" Hello ");
      lcd.setCursor(x+1,y+1);
      lcd.print(" World ");
      delay(100);
    }
}

void printFloat(){
  lcd.clear();
  float f = 0.1;
  lcd.setCursor(5,0);
  lcd.print(f);
}

void loopFloat(){
  lcd.clear();
  float f = 0.01;
  float inc=f;
  do {
  lcd.setCursor(5,0);
  lcd.print(f2s2(f,5,2));
  f=f+inc;
  delay (100);
  } while (f<100);
}

void loopTime(){
  int startTime=millis();
  lcd.clear();
//  for (int n=1;n<100000;n++){
  for (int n=1;n<1000;n++){
    int printTime=millis();
    do{
      
    } while(millis()-printTime < 100);
      printTime=millis();
      float f;
 //     f = (millis()-startTime)/1000;
       f = (millis()-startTime);
       f = f/1000;
      lcd.setCursor(5,0);
      lcd.print(f);
    
  }
}

/*============================================================================*/
/* Convert unsigned long value to d-digit long string in local buffer         */
/*============================================================================*/
char *ul2s(unsigned long x, unsigned d)
{  static char b[7];
   char *p;
   unsigned digits = 0;
   unsigned long t = x;

   do ++digits; while (t /= 10);
   // if (digits > d) d = digits; // uncomment to allow more digits than spec'd
   *(p = b + d) = '\0';
   do *--p = x % 10 + '0'; while (x /= 10);
   while (p != b) *--p = ' ';
   return b;
}

/*============================================================================*/
/* Convert float value to d-digit long string in local buffer                 */
/* d includes decimal place and preceding '0'                                 */
/*============================================================================*/

char *f2s2(float x, unsigned d, unsigned dp)
{  
  const int buffMaxSize = 7;
  static char b[buffMaxSize];
  char *p;
//   unsigned digits = 0;

  // Error checks
  if (d > buffMaxSize-2) return ("STL");  // Sanity check - "String Too Long" - d is more than maximum string length, plus terminating '\0' (plus preceding '0'?)
  if (d < dp + 2) return ("STS");         // Sanity check - "String Too Short" - d is less than number of decimal places plus preceding '0'
  if (dp < 1) return("NDP");              // Sanity check - "No Decimal Places" - must have at least one decimal place
  
  unsigned dp_count=dp;
  unsigned magnitude = pow(10, dp); 
  unsigned long ul = x*magnitude;

  strcpy (b, ul2s(ul, d));
   
//   *(p = b + d + 1 + (x<magnitude)) = '\0';
//#define __Original__
#ifdef __Original__
  *(p = b + d + 1) = '\0';    // shift end of string along by one, to give space for decimal place (this line is redundant, can subsume into next line)
  do *--p = *(p-1); while (dp_count--);  // shift all characters after decimal place along by one, to give space for decimal place
  *p = '.';  // insert decimal point
// need to add preceding 0s, both before AND after the decimal point
//  if (ul<magnitude) *--p = '0'; 
  if (ul<magnitude){
    *--p = '0';                   // put 0 preceding decimal point 0
    while (p++ < b + d)  // Is it possible to change to stop incrementing p after non '0' characters, by calculating the number of decimal places, in order to remove else
      if (*p == ' ') *p = '0';    // replace any spaces after decimal point
      else if (*p != '.') break;  // stop incrementing p (and checking) after non '0' characters after the decimal point
  }
#else
  p = b + d + 1;    // shift end of string along by one, to give space for decimal place (this line is redundant, can subsume into next line)
//  do *p-- = *p; while (dp_count--);  // shift all characters after decimal place along by one, to give space for decimal place
  do *p-- = *p; while (dp_count--);  // shift all characters after decimal place along by one, to give space for decimal place
//  do {*p = *(p-1); p--;} while (dp_count--);  // shift all characters after decimal place along by one, to give space for decimal place
  *p-- = '.';  // insert decimal point
// need to add preceding 0s, both before AND after the decimal point
  if (ul<magnitude){
    *p++ = '0';                    // put 0 preceding decimal point 0
    while (p++ < b + d - (dp -1))  // Stop incrementing p after non '0' characters, by calculating the number of decimal places
      if (*p == ' ') *p = '0';     // replace any spaces after decimal point
  }
#endif
  return b;
}


