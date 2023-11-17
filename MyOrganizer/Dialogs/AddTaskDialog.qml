import QtQuick 2.5
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12
import "../Model" as Model;

Dialog {
    id: _addDialog
    visible: false

    property int _id: 0
    property string task_name: "Название задания"
    property string task_description: "Описание задания"
    property string start_date: "Дата начала"
    property string end_date: "Дата окончания"
    property string progress: "0%"
    property bool nigthMode: false

    width: 840
    height: 130
    anchors.centerIn: parent
    standardButtons: StandardButton.Cancel | StandardButton.Ok

    signal dayNightModeChanged
    onDayNightModeChanged: { nigthMode = !nigthMode }

    Model.TableLine {
        id: _tLine
        _index: _id
        nigthMode: _addDialog.nigthMode
        _id_text: if (_id != 0) _id
        task_name: parent.task_name
        task_description: parent.task_description
        start_date: parent.start_date
        end_date: parent.end_date
        prog: progress
        line_height: 50
        anchors.left: parent.left
    }//_tLine

    onAccepted: {
        task_name = _tLine.task_name
        task_description = _tLine.task_description
        start_date = _tLine.start_date
        end_date = _tLine.end_date
        progress = _tLine.prog
    }//onAccepted
}//_addDialog
