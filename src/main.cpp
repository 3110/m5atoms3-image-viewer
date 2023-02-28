// clang-format off
#include <SPIFFS.h>
#include <M5Unified.h>
// clang-format on
#include <string.h>

extern bool hasExt(const char* filename, const char* ext);
extern bool isJpeg(const char* filename);
extern bool isPng(const char* filename);
extern bool isBmp(const char* filename);
extern bool isImageFile(const File& f);
extern void showImage(const String* images, size_t p);
extern void forever(void);

const bool FORMAT_SPIFFS_IF_FAILED = true;

const uint32_t START_INTERVAL_MS = 3000;
const uint32_t AUTO_MODE_INTERVAL_MS = 3000;
const uint32_t BUTTON_MODE_INTERVAL_MS = 100;

const String ROOT_DIR("/");

const size_t MAX_IMAGE_FILES = 50;
String imageFiles[MAX_IMAGE_FILES];
size_t nImageFiles = 0;
size_t pos = 0;

bool isAutoMode = false;

void setup(void) {
    M5.begin();
    M5.Lcd.setRotation(2);
    M5.Lcd.clear();

    M5.update();
    isAutoMode = M5.BtnA.isPressed();
    M5.Lcd.println(isAutoMode ? "** Auto Mode **" : "** Button Mode **");

    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        M5.Lcd.println("Failed to mount SPIFFS");
        forever();
    }
    File root = SPIFFS.open(ROOT_DIR.c_str(), "r");
    if (!root) {
        M5.Lcd.printf("Failed to open \"%s\"", ROOT_DIR);
        M5.Lcd.println();
        forever();
    }
    File f = root.openNextFile();
    while (f && nImageFiles < MAX_IMAGE_FILES) {
        if (!f.isDirectory() && isImageFile(f)) {
            imageFiles[nImageFiles] = ROOT_DIR + f.name();
            ++nImageFiles;
        }
        f = root.openNextFile();
    }
    if (nImageFiles == 0) {
        M5.Lcd.println("No image files found");
        forever();
    }

    M5.Lcd.println("Image Files:");
    for (size_t c = 0; c < nImageFiles; ++c) {
        M5.Lcd.print("  ");
        M5.Lcd.println(imageFiles[c]);
    }
    delay(START_INTERVAL_MS);

    if (!isAutoMode) {
        showImage(imageFiles, pos);
    }
}

void loop(void) {
    M5.update();
    if (isAutoMode || M5.BtnA.wasClicked()) {
        pos = (pos + 1) % nImageFiles;
        showImage(imageFiles, pos);
    }
    delay(isAutoMode ? AUTO_MODE_INTERVAL_MS : BUTTON_MODE_INTERVAL_MS);
}

bool hasExt(const char* filename, const char* ext) {
    if (filename == nullptr) {
        return false;
    }
    if (ext == nullptr) {
        return false;
    }
    const char* p = strrchr(filename, '.');
    return p != nullptr && strcasecmp(ext, p) == 0;
}

bool isJpeg(const char* filename) {
    if (filename == nullptr) {
        return false;
    }
    return hasExt(filename, ".jpg") || hasExt(filename, ".jpeg");
}

bool isPng(const char* filename) {
    if (filename == nullptr) {
        return false;
    }
    return hasExt(filename, ".png");
}

bool isBmp(const char* filename) {
    if (filename == nullptr) {
        return false;
    }
    return hasExt(filename, ".bmp");
}

bool isImageFile(const File& f) {
    const char* name = f.name();
    return isJpeg(name) || isPng(name) || isBmp(name);
}

void showImage(const String images[], size_t p) {
    const char* filename = images[p].c_str();
    M5.Lcd.startWrite();
    if (isJpeg(filename)) {
        M5.Lcd.drawJpgFile(SPIFFS, filename, 0, 0);
    } else if (isPng(filename)) {
        M5.Lcd.drawPngFile(SPIFFS, filename, 0, 0);
    } else if (isBmp(filename)) {
        M5.Lcd.drawBmpFile(SPIFFS, filename, 0, 0);
    } else {
        M5.Lcd.clear();
        M5.Lcd.printf("ignore: %s", filename);
        M5.Lcd.println();
    }
    M5.Lcd.endWrite();
}

void forever(void) {
    while (true) {
        delay(1);
    }
}