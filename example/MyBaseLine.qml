import QtQuick 2.0
import CLine 1.0

CLine {
    id: root

    property string myColor: "black"

    penWidth: 15

    clickable: true
    onClicked: { color = "orange"; anim.start() }

    ColorAnimation on color {
        id: anim
        to: root.myColor
        duration: 500
    }
}
