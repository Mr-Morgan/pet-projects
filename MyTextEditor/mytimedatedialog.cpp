#include "mytimedatedialog.h"

MyTimeDateDialog::MyTimeDateDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Дата и время"));
    setFixedSize(500, 400);

    QGridLayout *layout = new QGridLayout();
    setLayout(layout);

    calendar = new QCalendarWidget(this);
    timeEnabled = new QCheckBox(this);
    time = new QTimeEdit(this);
    time->setTime(QTime::currentTime());

    time->setDisplayFormat("HH:mm:ss");

    QHBoxLayout *hLayout = new QHBoxLayout(this);

    timeEnabled->setText("Время");
    hLayout->addWidget(timeEnabled);
    hLayout->addWidget(time, 1);

    time->setEnabled(false);

    layout->addWidget(calendar, 0, 0, 4, 4);
    layout->addLayout(hLayout, 5, 0, 1, 4);

    QPushButton *ok = new QPushButton ("&Ok");
    QPushButton *cancel = new QPushButton ("&Cancel");

    connect(ok, SIGNAL(clicked()), SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), SLOT(reject()));
    connect(timeEnabled, SIGNAL(clicked(bool)), time, SLOT(setEnabled(bool)));

    layout->addWidget(cancel, 6, 0, 1, 2);
    layout->addWidget(ok, 6, 2, 1, 2);
}//MyTimeDateDialog(QWidget *parent = nullptr);

QDateTime MyTimeDateDialog::getData() const
{
    QDateTime d;
    d.setDate(calendar->selectedDate());
    if (time->isEnabled()) d.setTime(time->time());
    return d;
}//QDateTime getData() const
