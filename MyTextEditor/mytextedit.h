#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QContextMenuEvent>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTextEdit>
#include <QObject>
#include <QString>
#include <QStack>
#include <QMenu>

#include <QTextCharFormat>

#define STACK_MAX_SIZE 50

enum BDKey {Backspace = 1, Delete};

struct Changes
{
    int32_t pos; //position
    QString data;
    bool del;    //is delete?
    Changes() {}
    Changes(int32_t p, QString d, bool de = false) : pos(p), data(d), del(de) {}
};//struct Changes

class MyTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit MyTextEdit(QWidget *parent = nullptr);
    void pushChanges(QStack<Changes> &st, Changes ch);
    void saveTextFormat();
    void setFormatNeedsInserted(bool needs);
    void setTextFormat(QTextCharFormat f);
    QTextCharFormat getTextFormat();
    bool getFNI();

protected:
    void contextMenuEvent(QContextMenuEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

public slots:
    void on_textEdit_textChanged();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

signals:
    void charFormatChanged(bool);

private:
    bool undoRedoFlag = false;
    QList<QAction*> my_action;
    QStack<Changes> undo;
    QStack<Changes> redo;
    QString twc;    //text without changes
    BDKey key;
    QMenu *m;
    QTextCharFormat f;
    bool fni = false;    //The format needs to be inserted?
};//class MyTextEdit : public QTextEdit

#endif // MYTEXTEDIT_H
