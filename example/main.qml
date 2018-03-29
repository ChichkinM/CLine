import QtQuick 2.0
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
                lineOne.color = "blue"
                flag = false
            }
            else {
                lineOne.color = "darkblue"
                flag = true
            }

    }

    MouseArea {
        anchors.fill: parent
        onClicked: recOne.x += 1
    }

    Rectangle {
        id: rectangle
        width: Math.round(parent.width - 50)
        height: Math.round(parent.height - 50)
        anchors.centerIn: parent
        color: "lavender"
    }

    Rectangle {
        id: bigRecOne
        width: 200
        height: rectangle.height
        y: rectangle.y
        x: Math.round(rectangle.width * 0.25)
        border.width: 1
    }

    Rectangle {
        id: bigRecTwo
        width: 200
        height: rectangle.height
        y: rectangle.y
        x: Math.round(rectangle.width * 0.75)
        border.width: 1
    }

    Rectangle {
        id: bigRecThree
        width: bigRecTwo.x - bigRecOne.x - bigRecOne.width
        height: 100
        y: Math.round(rectangle.y + rectangle.height * 0.2 - height)
        x: bigRecOne.x + bigRecOne.width
        border.width: 1
    }

    Rectangle {
        id: bigRecFore
        width: bigRecTwo.x - bigRecOne.x - bigRecOne.width
        height: 100
        y: Math.round(rectangle.y + rectangle.height * 0.8)
        x: bigRecOne.x + bigRecOne.width
        border.width: 1
    }

    Rectangle {
        id: recOne
        x: 150
        y: 150
        width: Math.round(50)
        height: Math.round(50)
        color: "lightgreen"
    }

    Rectangle {
        id: recTwo
        x: parent.width / 5
        y: 500
        width: Math.round(50)
        height: Math.round(50)
        color: "lightgreen"
    }



    CLine {
        id: lineOne
        color: "black"
        penWidth: 10

        clipType: CLine.CLIP_LEFT | CLine.CLIP_TOP | CLine.CLIP_BOTTOM

        points: [
            CPoint { x: recOne.x ; y: recOne.y },
            CPoint { x: recTwo.x; y: recTwo.y }
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
        color: "coral"
        penWidth: 15

        points: [
            CPoint { x: bigRecOne.x + bigRecOne.width; y: rectangle.y + 200 },
            CPoint { x: bigRecTwo.x; y: rectangle.y + 200 }
        ]
    }

    CLine {
        color: "coral"
        penWidth: 15

        points: [
            CPoint { x: bigRecTwo.x; y: rectangle.y + 300 },
            CPoint { x: bigRecOne.x + bigRecOne.width; y: rectangle.y + 300 }
        ]
    }

    CLine {
        color: "coral"
        penWidth: 15

        points: [
            CPoint { x: bigRecOne.x; y: rectangle.y + 250 },
            CPoint { x: bigRecOne.x + bigRecOne.width; y: rectangle.y + 250 }
        ]
    }



    CLine {
        color: "coral"
        penWidth: 15

        points: [
            CPoint { x: bigRecThree.x + 50; y: bigRecThree.y + bigRecThree.height },
            CPoint { x: bigRecThree.x + 50; y: bigRecFore.y }
        ]
    }

    CLine {
        color: "coral"
        penWidth: 15

        points: [
            CPoint { x: bigRecThree.x + 100; y: bigRecFore.y },
            CPoint { x: bigRecThree.x + 100; y: bigRecThree.y + bigRecThree.height }
        ]
    }

    CLine {
        color: "coral"
        penWidth: 15

        points: [
            CPoint { x: bigRecThree.x + 75; y: bigRecThree.y },
            CPoint { x: bigRecThree.x + 75; y: bigRecThree.y + bigRecThree.height }
        ]
    }



    CLine {
        penWidth: 10

        clipType: CLine.CLIP_RIGHT | CLine.CLIP_TOP | CLine.CLIP_BOTTOM

        points: [
            CPoint { x: rectangle.x + rectangle.width; y: rectangle.y + rectangle.height},
            CPoint { x: rectangle.x + rectangle.width * 0.75; y: rectangle.y + rectangle.height * 0.75 },
            CPoint { x: rectangle.x + rectangle.width * 0.75; y: rectangle.y + rectangle.height * 0.25},
            CPoint { x: rectangle.x + rectangle.width; y: rectangle.y  }
        ]
    }
}
