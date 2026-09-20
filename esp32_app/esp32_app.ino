#include <SD.h>
#include <SPI.h>

#include <GxEPD2_BW.h>
#include "GxEPD2_display_selection_new_style.h"
#include "GxEPD2_display_selection.h"
#include "GxEPD2_display_selection_added.h"

unsigned char* image = nullptr;
const size_t page_size = 81600;


/*
---------------------TODO--------------------
* Double click to jump to next or previous song
* Switch to song when removing SD card on sleep mode
* 


---------------------------------------------
*/


enum class PageLoadStatus {
  Loaded,
  LoadFailed
};

// File format: "/music[page]_gxepd2.bin";
PageLoadStatus loadMusicImage(uint8_t& currentPage) {
  SPI.begin(18, 19, 23, 4);

  File file = SD.open(("/music" + String(currentPage) + "_gxepd2.bin").c_str());
  if (!file) {
    Serial.println(("Failed to open music" + String(currentPage) + "_gxepd2.bin").c_str());
    return PageLoadStatus::LoadFailed;
  }
  file.read(image, page_size);
  file.close();

  SPI.endTransaction();
  Serial.println("Image loaded into C-style array successfully.");
  return PageLoadStatus::Loaded;
}

void renderPage(bool& sleepMode, uint8_t& currentPage) {
  // display.setFullWindow();

  display.setPartialWindow(0, 0, 960, 680);  // Set a a window the size of the full display,
  display.setRotation(2);                    // but with partial refresh enabled.
  display.firstPage();
  do {
    if (sleepMode) {
      display.fillScreen(GxEPD_WHITE);
      continue;
    }
    display.drawXBitmap(0, 0, image, 960, 680, GxEPD_BLACK);
  } while (display.nextPage());
}

void toggleSleep(bool& sleepMode) {
  sleepMode = !sleepMode;
  if (sleepMode) {
    display.setFullWindow();
    display.firstPage();
    do {
      display.fillScreen(GxEPD_WHITE);
    } while (display.nextPage());
    display.hibernate();
  } else {
    display.init(115200);  // Initialize the display again
  }
}

// Load the next right valid page from the SD card.
void turnPageRight(uint8_t& currentPage) {
  uint8_t rightPage = currentPage + 1;
  if (loadMusicImage(rightPage) == PageLoadStatus::Loaded) {
    currentPage += 1;
  }
}

// Load the next left valid page from the SD card.
void turnPageLeft(uint8_t& currentPage) {
  uint8_t leftPage = currentPage - 1;
  if (loadMusicImage(leftPage) == PageLoadStatus::Loaded) {
    currentPage = leftPage;
  }
}

void waitForButtonPress(bool& sleepMode, uint8_t& currentPage) {
  Serial.println(digitalRead(A4));
  while (1) {
    if (digitalRead(A5) == LOW) {
      delay(50);
      toggleSleep(sleepMode);
      return;
    }
    if (digitalRead(A4) == LOW) {
      delay(50);
      turnPageLeft(currentPage);
      return;
    }
    if (digitalRead(A3) == LOW) {
      delay(50);
      turnPageRight(currentPage);
      return;
    }
    delay(10);
  }
}

void setup() {
  uint8_t initialPage = 0;

  // Buttons
  pinMode(A5, INPUT);  //ToggleSleep
  pinMode(A4, INPUT);  //PageLeft
  pinMode(A3, INPUT);  //PageRight

  Serial.begin(115200);
  display.init(115200);  // Initialize the display

  Serial.println("Mounting SD...");
  SPI.begin(18, 19, 23, 4);
  if (SD.begin(4)) {
    Serial.println("SD OK.");
  }
  image = (unsigned char*)malloc(page_size);
  loadMusicImage(initialPage);
}

void loop() {
  static bool sleepMode = false;
  static uint8_t currentPage = 0;

  if (image == nullptr) {
    return;
  }
  if (!sleepMode) {
    renderPage(sleepMode, currentPage);
  }
  waitForButtonPress(sleepMode, currentPage);
}
