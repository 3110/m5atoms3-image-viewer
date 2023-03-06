#include "ImageViewer.hpp"

#include <string.h>

const char* ImageViewer::VERSION = "v0.0.2";

const float ImageViewer::GRAVITY_THRESHOLD = 0.65;
const String ImageViewer::ROOT_DIR("/");

static const bool FORMAT_SPIFFS_IF_FAILED = true;

ImageViewer::ImageViewer(bool isAutoMode)
    : _isAutoMode(isAutoMode),
      _imageFiles{""},
      _nImageFiles(0),
      _pos(0),
      _prevUpdate(0),
      _orientation(OrientationNormal) {
}

ImageViewer::~ImageViewer(void) {
}

bool ImageViewer::begin(void) {
    auto cfg = M5.config();
    cfg.internal_imu = true;
    M5.begin(cfg);
    updateOrientation();
    M5.Lcd.clear();

    M5.update();
    M5.Lcd.printf("Image Viewer %s", VERSION);
    M5.Lcd.println();
    this->_isAutoMode = M5.BtnA.isPressed();
    M5.Lcd.println(this->_isAutoMode ? "** Auto Mode **" : "** Manual Mode **");

    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        M5.Lcd.println("Failed to mount SPIFFS");
        return false;
    }
    File root = SPIFFS.open(ROOT_DIR.c_str(), "r");
    if (!root) {
        M5.Lcd.printf("Failed to open \"%s\"", ROOT_DIR);
        M5.Lcd.println();
        return false;
    }
    File f = root.openNextFile();
    while (f && this->_nImageFiles < MAX_IMAGE_FILES) {
        if (!f.isDirectory() && isImageFile(f)) {
            this->_imageFiles[this->_nImageFiles] = ROOT_DIR + f.name();
            ++this->_nImageFiles;
        }
        f = root.openNextFile();
    }
    if (this->_nImageFiles == 0) {
        M5.Lcd.println("No image files found");
        return false;
    }
    M5.Lcd.println("Image Files:");
    for (size_t c = 0; c < this->_nImageFiles; ++c) {
        M5.Lcd.print("  ");
        M5.Lcd.println(this->_imageFiles[c]);
    }
    delay(DEFAULT_START_INTERVAL_MS);

    if (!this->_isAutoMode) {
        showImage(this->_imageFiles, this->_pos);
    }
    return true;
}

bool ImageViewer::update(void) {
    M5.update();
    const bool orientationChanged = updateOrientation(GRAVITY_THRESHOLD);
    const uint32_t t = millis();
    if ((this->_isAutoMode &&
         t - this->_prevUpdate >= DEFAULT_AUTO_MODE_INTERVAL_MS) ||
        M5.BtnA.wasClicked()) {
        this->_prevUpdate = t;
        this->_pos = (this->_pos + 1) % this->_nImageFiles;
        showImage(this->_imageFiles, this->_pos);
        return true;
    } else {
        if (orientationChanged) {
            showImage(this->_imageFiles, this->_pos);
        }
        return false;
    }
}

bool ImageViewer::updateOrientation(float threshold) {
    const Orientation o = detectOrientation(threshold);
    if (this->_orientation != o) {
        this->_orientation = o;
        M5.Lcd.setRotation(this->_orientation);
        return true;
    }
    return false;
}

void ImageViewer::showImage(const String images[], size_t p) {
    const char* filename = images[p].c_str();
    M5.Lcd.startWrite();
    if (isJpeg(filename)) {
        M5.Lcd.drawJpgFile(SPIFFS, filename, 0, 0);
    } else if (isPng(filename)) {
        M5.Lcd.drawPngFile(SPIFFS, filename, 0, 0);
    } else if (isBmp(filename)) {
        M5.Lcd.drawBmpFile(SPIFFS, filename, 0, 0);
    } else {
        M5.Lcd.printf("ignore: %s", filename);
        M5.Lcd.println();
    }
    M5.Lcd.endWrite();
}

bool ImageViewer::hasExt(const char* filename, const char* ext) {
    if (filename == nullptr) {
        return false;
    }
    if (ext == nullptr) {
        return false;
    }
    const char* p = strrchr(filename, '.');
    return p != nullptr && strcasecmp(ext, p) == 0;
}

bool ImageViewer::isJpeg(const char* filename) {
    if (filename == nullptr) {
        return false;
    }
    return hasExt(filename, ".jpg") || hasExt(filename, ".jpeg");
}

bool ImageViewer::isPng(const char* filename) {
    if (filename == nullptr) {
        return false;
    }
    return hasExt(filename, ".png");
}

bool ImageViewer::isBmp(const char* filename) {
    if (filename == nullptr) {
        return false;
    }
    return hasExt(filename, ".bmp");
}

bool ImageViewer::isImageFile(const File& f) {
    const char* name = f.name();
    return isJpeg(name) || isPng(name) || isBmp(name);
}

ImageViewer::Orientation ImageViewer::detectOrientation(float threshold) {
    if (M5.Imu.isEnabled()) {
        float ax, ay, az;
        M5.Imu.getAccel(&ax, &ay, &az);
        if (ay >= threshold) {
            return OrientationNormal;
        } else if (ax >= threshold) {
            return OrientationRight;
        } else if (ax <= -threshold) {
            return OrientationLeft;
        } else if (ay <= -threshold) {
            return OrientationUpsideDown;
        }
    }
    return OrientationNormal;
}
