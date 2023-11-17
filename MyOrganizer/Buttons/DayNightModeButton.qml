import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Rectangle {
    id: _dayNightMode
    property int size: 30
    property bool nightMode: false
    property string back_color: (nigthMode)? "#303030" : "#FAFAFA"
    color: back_color
    width: size
    height: size
    radius: 100

    signal clicked

    MouseArea {
        id: _mArea
        anchors.fill: parent
        onPressed: _imgBut.source = (_dayNightMode.nightMode)? "qrc:/icons/night_pressed.png" : "qrc:/icons/classic_pressed.png"
        onReleased: _imgBut.source = (_dayNightMode.nightMode)? "qrc:/icons/night.png" : "qrc:/icons/classic.png"
        onClicked: {
            _dayNightMode.nightMode = !_dayNightMode.nightMode
            _imgBut.source = (_dayNightMode.nightMode)? "qrc:/icons/night.png" : "qrc:/icons/classic.png"
            parent.clicked()
        }//onClicked
        onVisibleChanged: {
            _imgBut.source = (_dayNightMode.nightMode)? "qrc:/icons/night.png" : "qrc:/icons/classic.png"
        }//onVisibleChanged
    }//_mArea

    Image {
        id: _imgBut
        source: (_dayNightMode.nightMode)? "qrc:/icons/night.png" : "qrc:/icons/classic.png"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }//_imgBut
}//_dayNightMode
