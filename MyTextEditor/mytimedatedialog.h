#ifndef MYTIMEDATEDIALOG_H
#define MYTIMEDATEDIALOG_H

#include <QCalendarWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QDateTime>
#include <QTimeEdit>
#include <QDialog>
#include <QObject>
#include <QWidget>

#include <QHBoxLayout>

class MyTimeDateDialog : public QDialog
{
    Q_OBJECT
public:
    MyTimeDateDialog(QWidget *parent = nullptr);
    QDateTime getData() const;

private:
    QCalendarWidget *calendar;
    QCheckBox *timeEnabled;
    QTimeEdit *time;
};//class MyTimeDateDialog : public QDialog

#endif // MYTIMEDATEDIALOG_H
