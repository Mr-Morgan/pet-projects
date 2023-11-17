import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Rectangle {
    id: _checkBox
    property int size: 30
    property bool checked: false
    property string back_color: Material.color(Material.Grey, Material.Shade200)
    color: back_color
    width: size
    height: size

    signal clicked
    signal dayNightModeChanged
    onDayNightModeChanged: { nigthMode = !nigthMode }

    MouseArea {
        id: _mArea
        anchors.fill: parent
        onPressed: _imgBut.source = (_checkBox.checked)? "qrc:/icons/checkbox_checked_pressed.png" : "qrc:/icons/checkbox_pressed.png"
        onReleased: _imgBut.source = (_checkBox.checked)? "qrc:/icons/checkbox_checked.png" : "qrc:/icons/checkbox.png"
        onClicked: {
            _checkBox.checked = !_checkBox.checked
            _imgBut.source = (_checkBox.checked)? "qrc:/icons/checkbox_checked.png" : "qrc:/icons/checkbox.png"
            parent.clicked()
        }//onClicked
        onVisibleChanged: {
            _imgBut.source = (_checkBox.checked)? "qrc:/icons/checkbox_checked.png" : "qrc:/icons/checkbox.png"
        }//onVisibleChanged
    }//_mArea

    Image {
        id: _imgBut
        source: (_checkBox.checked)? "qrc:/icons/checkbox_checked.png" : "qrc:/icons/checkbox.png"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }//_imgBut
}//_checkBox
