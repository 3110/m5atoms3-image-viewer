#include "ImageViewer.hpp"

ImageViewer viewer;

void forever(void) {
    while (true) {
        delay(1);
    }
}

void setup(void) {
    if (!viewer.begin()) {
        forever();
    }
}

void loop(void) {
    viewer.update();
    delay(100);
}
