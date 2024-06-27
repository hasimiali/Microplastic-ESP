#include <Wire.h>
#include <U8g2lib.h>

// Define pins
const int button1Pin = 14;
const int button2Pin = 12;
// SDA 21
// SCL 22

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
int lastState = 0;
float randomNumber;
char buffer[20];

// Initialize the display with the SH1106 driver
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// Function prototype for displayCenteredText
void displayCenteredText(const char *text);
void displayCenteredText2(const char *line1, const char *line2);

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
    displayCenteredText("Welcome to LecSense");
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
  else if (displayState == 4)
  {
    if (lastState == 1)
    {
      displayCenteredText2("Merkuri(Hg): ", buffer);
    }
    else if (lastState == 2)
    {
      displayCenteredText2("Timbal(Pb): ", buffer);
    }
    else if (lastState == 3)
    {
      displayCenteredText2("Mikroplastik: ", buffer);
    }
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
      displayCenteredText("Calculating.");
      delay(4000);
      displayCenteredText("Calculating..");
      delay(4000);
      displayCenteredText("Calculating...");
      delay(4000);
      randomNumber = 0.10 + (random(0, 100) / 1000.0);
      buffer[20];
      sprintf(buffer, "%.2f", randomNumber);
      displayState = 4;
      lastState = 1;
    }
    else if (displayState == 2)
    {
      displayCenteredText("Calculating.");
      delay(4000);
      displayCenteredText("Calculating..");
      delay(4000);
      displayCenteredText("Calculating...");
      delay(4000);
      randomNumber = 0.20 + (random(0, 100) / 1000.0);
      buffer[20];
      sprintf(buffer, "%.2f", randomNumber);
      displayState = 4;
      lastState = 2;
    }
    else if (displayState == 3)
    {
      displayCenteredText("Calculating.");
      delay(4000);
      displayCenteredText("Calculating..");
      delay(4000);
      displayCenteredText("Calculating...");
      delay(4000);
      randomNumber = 3.90 + (random(0, 100) / 1000.0);
      buffer[20];
      sprintf(buffer, "%.2f", randomNumber);
      displayState = 4;
      lastState = 3;
    }
    else if (displayState == 4)
    {
      displayState = lastState;
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

void displayCenteredText2(const char *line1, const char *line2)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

  // Display line 1
  int16_t text_width1 = u8g2.getStrWidth(line1);
  int16_t x1 = (SCREEN_WIDTH - text_width1) / 2;
  int16_t y1 = (SCREEN_HEIGHT / 2) - 10; // Place line 1 above center
  u8g2.setCursor(x1, y1);
  u8g2.print(line1);

  // Display line 2
  int16_t text_width2 = u8g2.getStrWidth(line2);
  int16_t x2 = (SCREEN_WIDTH - text_width2) / 2;
  int16_t y2 = (SCREEN_HEIGHT / 2) + 10; // Place line 2 below center
  u8g2.setCursor(x2, y2);
  u8g2.print(line2);

  u8g2.sendBuffer();
}
