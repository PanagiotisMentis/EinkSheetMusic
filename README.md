# PDFtoBin E-ink Image Converter

A high-performance C++ backend utility integrated with a Python FastAPI server and GUI. This system converts PDF documents (such as sheet music) into dithered, bit-packed binary files formatted specifically for GxEPD2 e-paper displays driven by an ESP32, while also generating PNG previews.

## Overview

1. **C++ converter_app**: Dithers and packs the PDF data to a bitmap to be displayed on GXEPD2 e-ink screens.
2. **Python FastAPI Server**: Provides a web GUI to remotely upload PDFs (output bitmaps stored locally) 
3. **(In-Progress) ESP32 Integration**: Provides an HTTP server to serve image bitmaps to a requesting ESP32 e-ink board.

## Dependencies

### C++ Dependencies
* **Poppler C++** [libpoppler-cpp-dev](https://poppler.freedesktop.org/api/cpp/).
* Filesystem library (`<filesystem>`).

### Python Dependencies
* FastAPI
* Uvicorn

## Usage

### GUI
1. Start ./server/main.py
2. Connect to the appropriate machine IP
3. Upload PDF files and see bitmap results!

### converter_app

1. Run the executable, passing the output directory and input PDF as arguments.
```shell
.\build\PDFtoBin.exe "./binfiles" "nocturne.pdf"   
```
It should give something like:
```
TOTAL_PAGES:3
PROGRESS_PAGE:1
PROGRESS_PAGE:2
PROGRESS_PAGE:3
```

2. Check the output folder for binfiles and dithered png previews!
![example_output_files](./assets/example_output_files.png)
