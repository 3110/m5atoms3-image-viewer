#pragma once

// clang-format off
#include <SPIFFS.h>
#include <M5Unified.h>
// clang-format on

class ImageViewer {
public:
    enum Orientation
    {
        OrientationNormal = 0,
        OrientationRight,
        OrientationUpsideDown,
        OrientationLeft,
    };

    static const char* VERSION;

    static const char* DEFAULT_CONFIG_NAME;
    static const char* KEY_AUTO_MODE;
    static const char* KEY_AUTO_MODE_INTERVAL;

    static const size_t MAX_IMAGE_FILES = 50;
    static const bool DEFAULT_AUTO_MODE = false;
    static const uint32_t DEFAULT_START_INTERVAL_MS = 3000;
    static const uint32_t DEFAULT_AUTO_MODE_INTERVAL_MS = 3000;

    static const float GRAVITY_THRESHOLD;
    static const String ROOT_DIR;

    ImageViewer(bool isAutoMode = DEFAULT_AUTO_MODE,
                uint32_t autoModeInterval = DEFAULT_AUTO_MODE_INTERVAL_MS);
    virtual ~ImageViewer(void);

    virtual bool begin(void);
    virtual bool update(void);

    virtual bool updateOrientation(float threshold = GRAVITY_THRESHOLD);

protected:
    virtual bool setImageFileList(void);
    virtual void showImage(const String images[], size_t p);
    virtual bool hasExt(const char* filename, const char* ext);
    virtual bool isJpeg(const char* filename);
    virtual bool isPng(const char* filename);
    virtual bool isBmp(const char* filename);
    virtual bool isImageFile(const File& f);
    virtual Orientation detectOrientation(float threshold);
    virtual bool parse(const char* config = DEFAULT_CONFIG_NAME);

private:
    bool _isAutoMode;
    uint32_t _autoModeInterval;
    String _imageFiles[MAX_IMAGE_FILES];
    size_t _nImageFiles;
    size_t _pos;
    uint32_t _prevUpdate;
    Orientation _orientation;
};