import QtQuick 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12

Dialog {
    id: _dialogCalendar

    property string date: ""
    property bool isStart: true
    property bool nigthMode: false
    property string back_color: (nigthMode)?  Material.color(Material.Grey, Material.Shade800) : "#FFFFFF"

    width: 350
    height: 400
    anchors.centerIn: parent
    standardButtons: StandardButton.Cancel | StandardButton.Ok

    signal dayNightModeChanged
    onDayNightModeChanged: { nigthMode = !nigthMode }

    Calendar {
        id: _calendar
        anchors.fill: parent

        style: CalendarStyle {
            gridColor: back_color
            navigationBar: Rectangle {
                height: 50
                color: back_color

                Button {
                    id: _previousMonth
                    width: parent.height - 8
                    height: width
                    text: "<"
                    font.bold: true
                    font.pixelSize: 25
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    Material.foreground: Material.color(Material.DeepPurple, (nigthMode)? Material.Shade100 : Material.Shade500)
                    onClicked: control.showPreviousMonth()
                }//_previousMonth

                Label {
                    id: _dateText
                    text: styleData.title
                    font.bold: true
                    color: Material.color(Material.DeepPurple, (nigthMode)? Material.Shade100 : Material.Shade500)
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 18
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: _previousMonth.right
                    anchors.leftMargin: 2
                    anchors.right: _nextMonth.left
                    anchors.rightMargin: 2
                }//_dateText

                Button {
                    id: _nextMonth
                    width: parent.height - 8
                    height: width
                    text: ">"
                    font.bold: true
                    font.pixelSize: 25
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    Material.foreground: Material.color(Material.DeepPurple, (nigthMode)? Material.Shade100 : Material.Shade500)
                    onClicked: control.showNextMonth()
                }//_nextMonth
            }//navigationBar

            dayDelegate: Rectangle {
                anchors.fill: parent
                anchors.margins: (styleData.selected)? -1 : 0
                color: (styleData.date !== undefined && styleData.selected)? selectedDateColor : back_color

                readonly property color sameMonthDateTextColor: Material.color(Material.Grey, (nigthMode)?Material.Shade100:Material.Shade900)
                readonly property color selectedDateColor: Material.color(Material.DeepPurple, (nigthMode)? Material.Shade100:Material.Shade500)
                readonly property color selectedDateTextColor: Material.color(Material.Grey, (nigthMode)?Material.Shade900:Material.Shade100)
                readonly property color differentMonthDateTextColor: Material.color(Material.Grey, (nigthMode)?Material.Shade700:Material.Shade400)
                readonly property color invalidDateColor: Material.color(Material.Grey, (nigthMode)?Material.Shade900:Material.Shade100)

                Label {
                    id: _dayDelegateText
                    font.pixelSize: 10
                    anchors.centerIn: parent
                    text: styleData.date.getDate()
                    horizontalAlignment: Text.AlignRight
                    color: {
                        var theColor = invalidDateColor;
                        if (styleData.valid) {
                            theColor = styleData.visibleMonth ? sameMonthDateTextColor : differentMonthDateTextColor;
                            if (styleData.selected)
                                theColor = selectedDateTextColor;
                        }//if (styleData.valid)
                        theColor;
                    }//color
                }//_dayDelegateText
            }//dayDelegate

            dayOfWeekDelegate: Rectangle {
                height: 25
                color: back_color
                Label {
                    anchors.centerIn: parent
                    font.bold: true
                    horizontalAlignment: Text.AlignRight
                    font.pixelSize: 12
                    text: {
                        switch(styleData.dayOfWeek) {
                        case Locale.Sunday: "вс";
                            break;
                        case Locale.Monday: "пн";
                            break;
                        case Locale.Tuesday: "вт";
                            break;
                        case Locale.Wednesday: "ср";
                            break;
                        case Locale.Thursday: "чт";
                            break;
                        case Locale.Friday: "пт";
                            break;
                        case Locale.Saturday: "сб";
                            break;
                        }//switch(styleData.dayOfWeek
                    }//text
                }//Label
            }//dayOfWeekDelegate
        }//style
    }//_calendar

    onAccepted: {
        date = Qt.formatDate(_calendar.selectedDate, "dd.MM.yyyy");
    }//onAccepted
}//dialogCalendar

