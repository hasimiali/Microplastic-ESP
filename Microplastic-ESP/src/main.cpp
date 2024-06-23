#include <Wire.h>
#include <U8g2lib.h>

// Define button pins
const int button1Pin = 14;
const int button2Pin = 12;

// Variables to store the button state
int button1State = 0;
int button2State = 0;

// Variables to store the previous button state for edge detection
int lastButton1State = HIGH;
int lastButton2State = HIGH;

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

int displayState = 0;
float randomNumber;
char buffer[20];

// Initialize the display with the SH1106 driver
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// Function prototype for displayCenteredText
void displayCenteredText(const char *text);

void setup()
{
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initialize the button pins as input
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  // Initialize the OLED display
  u8g2.begin();

  // Display initial message
  displayCenteredText("Press buttons");
}

void loop()
{

  if (displayState == 0)
  {
    displayCenteredText("Welcome to I-Tongue");
  }
  else if (displayState == 1)
  {
    displayCenteredText("Merkuri Mode");
  }
  else if (displayState == 2)
  {
    displayCenteredText("Timbal Mode");
  }
  else if (displayState == 3)
  {
    displayCenteredText("Mikro Plastik Mode");
  }

  // Read the state of button 1
  button1State = digitalRead(button1Pin);

  // Read the state of button 2
  button2State = digitalRead(button2Pin);

  // Check if button 1 is pressed (state changed from HIGH to LOW)
  if (button1State == LOW && lastButton1State == HIGH)
  {
    Serial.println("Button 1 pressed!");

    if (displayState == 0)
    {
      displayCenteredText("Loading.");
      delay(1000);
      displayCenteredText("Loading..");
      delay(1000);
      displayCenteredText("Loading...");
      delay(1000);
      displayState = 1;
    }
    else if (displayState == 1)
    {
      randomNumber = 0.10 + (random(0, 100) / 1000.0);
      buffer[20];
      sprintf(buffer, "Merkuri(Hg): %.2f", randomNumber);
      displayCenteredText(buffer);
      delay(3000);
    }
    else if (displayState == 2)
    {
      randomNumber = 0.20 + (random(0, 100) / 1000.0);
      buffer[20];
      sprintf(buffer, "Timbal(Pb): %.2f", randomNumber);
      displayCenteredText(buffer);
      delay(3000);
    }
    else if (displayState == 3)
    {
      randomNumber = 3.90 + (random(0, 100) / 1000.0);
      buffer[20];
      sprintf(buffer, "Mikroplastik: %.2f", randomNumber);
      displayCenteredText(buffer);
      delay(3000);
    }
    // Debounce delay
    delay(200);
  }

  // Check if button 2 is pressed (state changed from HIGH to LOW)
  if (button2State == LOW && lastButton2State == HIGH)
  {
    Serial.println("Button 2 pressed!");
    if (displayState == 1)
    {
      displayState = 2;
    }
    else if (displayState == 2)
    {
      displayState = 3;
    }
    else if (displayState == 3)
    {
      displayState = 1;
    }
    // Debounce delay
    delay(200);
  }

  // Save the current state as the last state for the next loop iteration
  lastButton1State = button1State;
  lastButton2State = button2State;
}

void displayCenteredText(const char *text)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  int16_t text_width = u8g2.getStrWidth(text);
  int16_t x = (SCREEN_WIDTH - text_width) / 2;
  int16_t y = (SCREEN_HEIGHT / 2);
  u8g2.setCursor(x, y);
  u8g2.print(text);
  u8g2.sendBuffer();
}
