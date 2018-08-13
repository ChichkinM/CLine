# CLine
Component for drawing a line point by point.

## Get Started
Copy the src folder in your project or connect them with git.

### Include the .pri file in the .pro file
    include(Some/Path/CLine.pri)

### Include the cline.h and register the components in the C++ code
    #include "cline.h"

    int main() {
        CLine::registerComponents();
        ...
    }

### Include the newly registered components in the QML
    import CLine 1.0
    import CPoint 1.0

### Using
    CLine {
        clipType: CLine.CLIP_LEFT | CLine.CLIP_RIGHT | CLine.CLIP_TOP | CLine.CLIP_BOTTOM

        points: [
            CPoint { x: 10; y: 10 },
            CPoint { x: 50; y: 50 }
        ]
    }
