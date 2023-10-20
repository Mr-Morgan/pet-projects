#include "mysubwindow.h"

MySubWindow::MySubWindow(QWidget *parent) : QWidget(parent)
{
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    textEdit = new MyTextEdit(this);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setUndoRedoEnabled(false);

    gridLayout->addWidget(textEdit, 0, 0, 1, 1);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setTextFormat(Qt::RichText);

    horizontalLayout->addWidget(label);

    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setText("Author Name");

    horizontalLayout->addWidget(lineEdit);

    gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

    connect(textEdit, SIGNAL(charFormatChanged(bool)), this, SLOT(on_charFormatChanged(bool)));
}//MySubWindow(QWidget *parent, MyTextEdit *te, QLineEdit *le, QLabel *l)

MySubWindow::~MySubWindow()
{
    delete label;
    delete lineEdit;
    delete textEdit;
}//~MySubWindow()

void MySubWindow::undo()
{
    textEdit->on_actionUndo_triggered();
}//void undo()

void MySubWindow::redo()
{
    textEdit->on_actionRedo_triggered();
}//void redo()

void MySubWindow::printText(QTextStream &s, bool binary, bool readonly)
{
    if (binary) lineEdit->setText(s.readLine());
    textEdit->setPlainText(QString(s.readAll()));
    textEdit->moveCursor(QTextCursor::Start);
    textEdit->setReadOnly(readonly);
    lineEdit->setReadOnly(readonly);
}//void printText(QString text, bool bynary = false, bool readonly = false)

void MySubWindow::scanText(QTextStream &s, bool binary)
{
    if (binary) s << lineEdit->text() << '\n';
    s << textEdit->toPlainText();
}//void scanText(QTextStream *s, bool bynary = false)

void MySubWindow::setLabelText(QString text)
{
    label->setText(text);
}//void setLabelText(QString text)

void MySubWindow::print(QPrinter *p)
{
    textEdit->print(p);
}//void print(QPrinter *p)

void MySubWindow::insertTable(int32_t n, int32_t m)
{
    QTextTableFormat f;
    f.setAlignment(Qt::AlignCenter);
    f.setCellPadding(10);
    f.setCellSpacing(0);
    f.setBorderBrush(QBrush(QColor("#828989")));
    textEdit->textCursor().insertTable(n, m, f);
}//void insertTable(int32_t m, int32_t n)

void MySubWindow::setCursor(const QCursor &c)
{
    textEdit->viewport()->setCursor(c);
}//void setCursor(const QCursor &c)

void MySubWindow::setFormatNeedsInserted(bool needs)
{
    textEdit->setFormatNeedsInserted(needs);
}//void setFormatNeedsInserted(bool needs)

void MySubWindow::saveTextFormat()
{
    textEdit->saveTextFormat();
}//void saveTextFormat()

void MySubWindow::setTextFormat(QTextCharFormat f)
{
    textEdit->setTextFormat(f);
}//void setTextFormat(QTextCharFormat f)

QTextCharFormat MySubWindow::getTextFormat()
{
    return textEdit->getTextFormat();
}//QTextCharFormat getTextFormat()


void MySubWindow::setAlign(Qt::Alignment a)
{
    textEdit->setAlignment(a);
}//void setAlign(Qt::Alignment a)

bool MySubWindow::getFNI()
{
    return textEdit->getFNI();
}//bool getFNI()

void MySubWindow::insertDateTime(QDateTime &d)
{
    if (d.time() == QTime(0,0)) textEdit->insertPlainText(d.date().toString("ddd MMM dd yyyy"));
    else textEdit->insertPlainText(d.date().toString("ddd MMM dd yyyy") + " " + d.time().toString());
}//void insertDateTime(QDateTime d)

void MySubWindow::on_charFormatChanged(bool b)
{
    emit charFormatChanged(b);
}//void on_charFormatChanged(bool b)
