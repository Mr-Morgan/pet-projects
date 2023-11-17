import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Rectangle {
    id: _delButton
    property int size: 75
    property bool nigthMode: false
    property string back_color: (nigthMode)? "#303030" : "#FAFAFA"
    color: back_color
    width: size
    height: size
    radius: 15

    signal clicked
    signal dayNightModeChanged
    onDayNightModeChanged: { nigthMode = !nigthMode }

    MouseArea {
        id: _mArea
        anchors.fill: parent
        onPressed: _imgBut.source = "qrc:/icons/delete_pressed.png"
        onReleased: _imgBut.source = "qrc:/icons/delete.png"
        onClicked: { parent.clicked() }
    }//_mArea

    Image {
        id: _imgBut
        source: "qrc:/icons/delete.png"
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
    }//_imgBut
}//_delButton

