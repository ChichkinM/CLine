import QtQuick 2.6
import QtQuick.Window 2.2

import CLine 1.0
import CPoint 1.0

Window {
    visible: true
    width: 960
    height: 720
    title: qsTr("Hello CLine")
    color: "darkslateblue"

    Timer {
        property bool flag: false

        interval: 800
        running: true
        repeat: true
        onTriggered:
            if (flag) {
                line_1.color = "blue"
                flag = false
            }
            else {
                line_1.color = "darkblue"
                flag = true
            }

    }

    MouseArea {
        anchors.fill: parent
        onClicked: rec_1.x += 1
    }

    Rectangle {
        id: rectangle
        width: Math.round(parent.width - 50)
        height: Math.round(parent.height - 50)
        anchors.centerIn: parent
        color: "lavender"
    }

    Rectangle {
        id: rec_1
        x: 150
        y: 150
        width: Math.round(50)
        height: Math.round(50)
        color: "lightgreen"
    }


    Rectangle {
        id: rec_2
        x: parent.width / 2
        y: 400
        width: Math.round(50)
        height: Math.round(50)
        color: "lightgreen"
    }

    CLine {
        id: line_1
        color: "black"
        penWidth: 10

        clipType: CLine.CLIP_LEFT | CLine.CLIP_TOP | CLine.CLIP_BOTTOM

        points: [
            CPoint { x: rec_1.x ; y: rec_1.y },
            CPoint { x: rec_2.x; y: rec_2.y }
        ]
    }

    CLine {
        color: "black"
        penWidth: 10

        points: [
            CPoint { x: rectangle.x + 100; y: rectangle.y },
            CPoint { x: rectangle.x + 100; y: rectangle.y + 100 },
            CPoint { x: rectangle.x; y: rectangle.y + 150 }
        ]
    }

    CLine {
        penWidth: 10

        clipType: CLine.CLIP_RIGHT | CLine.CLIP_TOP | CLine.CLIP_BOTTOM

        points: [
            CPoint { x: rectangle.x + rectangle.width; y: rectangle.y + rectangle.height},
            CPoint { x: rectangle.x + rectangle.width / 2 + 100; y: rectangle.y + rectangle.height * 0.75 },
            CPoint { x: rectangle.x + rectangle.width / 2 + 100; y: rectangle.y + rectangle.height * 0.25},
            CPoint { x: rectangle.x + rectangle.width; y: rectangle.y  }
        ]
    }
}
