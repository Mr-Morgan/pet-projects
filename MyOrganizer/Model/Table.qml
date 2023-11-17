import QtQuick 2.0
import Table 1.0
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12


ListView {
    id: rootView
    width: parent.width
    height: contentHeight
    anchors.fill: parent

    property bool delMode: false
    property bool nigthMode: false
    signal dayNightModeChanged
    onDayNightModeChanged: {
        nigthMode = !nigthMode
    }//onDayNightModeChanged

    model: MyTableModel {

    }//MyTableModel

    delegate: TableLine {
        nigthMode: rootView.nigthMode
        _id_text: (model.index !== 0)? taskID : "ID"
        task_name: name
        task_description: description
        start_date: start
        end_date: end
        prog: progress
        line_height: (model.index !== 0)? 50 : 25
        onDataChanged: { rootView.model.changeLineData(index, task_name, task_description, start_date, end_date, prog) }
    }//TableLine
}//rootView
