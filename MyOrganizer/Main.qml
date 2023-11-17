import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "./Buttons" as Buttons;
import "./Dialogs" as Dialogs;
import "./Model" as Model;

ApplicationWindow {
    id: root
    visible: true
    minimumWidth: 840
    minimumHeight: 300
    width: 860
    height: 480
    title: qsTr("My Organaizer")

    property bool nigthMode: false
    Material.theme: (nigthMode)? Material.Dark : Material.Light
    Material.accent: Material.DeepPurple

    Model.Table {
        id: _table
        y: -_vbar.position * height
    }//_table

    ScrollBar {
        id: _vbar
        hoverEnabled: true
        width: 7
        active: hovered || pressed
        orientation: Qt.Vertical
        size: root.height / _table.height
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }//_vbar

    MouseArea {
        id: _mArea
        anchors.top: parent.top
        anchors.left: parent.left
        width: 50
        height: _table.height
        onClicked: {
            _setB.visible = false
            _addB.visible = false
            _dnmB.visible = false
            _delB.visible = true
            _backB.visible = true
            _table.delMode = true
        }//onClicked
    }//_mArea

    Buttons.AddButton {
        id: _addB
        size: 73
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onClicked: { _aTD.open() }
    }//_addB

    Buttons.DelButton {
        id: _delB
        visible: false
        size: 68
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onClicked: {
            _table.model.delLines()
            visible = false
            _backB.visible = false
            _table.delMode = false
            _addB.visible = true
            _setB.visible = true
            _dnmB.visible = (_setB.isPressed)? true : false
        }//onClicked
    }//_delB

    Buttons.BackButton {
        id: _backB
        visible: false
        size: 73
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onClicked: {
            visible = false
            _delB.visible = false
            _table.delMode = false
            _addB.visible = true
            _setB.visible = true
            _dnmB.visible = (_setB.isPressed)? true : false
        }//onClicked
    }//_backB

    Buttons.SettingsButton {
        id: _setB
        visible: true
        size: 73
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onClicked: {
            _dnmB.visible = isPressed
        }//onClicked
    }//_setB

    Buttons.DayNightModeButton {
        id: _dnmB
        visible: false
        size: 73
        anchors.left: _setB.right
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onClicked: {
            root.nigthMode = !root.nigthMode
            _setB.dayNightModeChanged()
            _backB.dayNightModeChanged()
            _delB.dayNightModeChanged()
            _addB.dayNightModeChanged()
            _table.dayNightModeChanged()
            _aTD.dayNightModeChanged()
        }//onClicked
    }//_dnmB

    Dialogs.AddTaskDialog {
        id: _aTD
        visible: false
        _id: _table.model.rowCount()
        onAccepted: {
            _table.model.addLine(task_name, task_description, start_date, end_date, progress)
            _id = _table.model.rowCount()
        }//onAccepted
    }//_aTD
}//root
