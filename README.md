# EinkSheetMusic

> *This repo contains code for the EinkSheetMusic tablet.*

## 🌟Highlights
- Light and portable
- Easy access to PDF sheet music
- No more carrying around stacks of paper music or bright LCDs

## ℹ️ Overview
The EinkSheetMusic tablet is a device meant for viewing sheet music on an e-ink display. Paper sheet music is too cluttered
and LCD displays are too bright to stare at. It renders any PDF, so reading digital sheet music is easy. It has an SD card
for saving files and buttons to turn the page left, turn the page right, and put the device in sleep mode. Soon, there will
be a remote file sending feature to transfer and convert PDFs wirelessly (from a phone/laptop) and a foot pedal to turn pages
wirelessly.

**Included Software:**
1. **esp32_app**: Renders .bin images on the Good Display ESP32-L Series e-ink driver board from a connected SD card.
2. **pdf_to_bin_app**: Converts PDFs to .bin image files. Has server and web interface as well as command-line executable.

## ✍️ Author
I'm Panagiotis Mentis and I developed this passion project as a solution to my music problems as a musician.

Developer: Panagiotis Mentis - Sophomore, Computer Engineering @ Virginia Tech

## 🚀 Usage
> [!NOTE]
> Additional READMEs for the **esp32_app** and **pdf_to_bin_app** are in each respective folder.

1. Flash the driver board with the **esp32_app** .ino
2. Convert desired PDFs to .bin files with the **pdf_to_bin_app**
3. Use a USB flash drive to load output .bin files to the tablet's SD card.
4. Insert the SD card and read music on the tablet!

![Tablet Picture](./assets/tablet.png)
