#ifndef MYTABLEDIALOG_H
#define MYTABLEDIALOG_H

#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QDialog>
#include <QWidget>

#include <QLabel>

struct DataNM
{
    int32_t n;
    int32_t m;
    DataNM() {}
    DataNM(int32_t n, int32_t m) : n(n), m(m) {}
};//struct DataNM

class MyTableDialog : public QDialog
{
    Q_OBJECT
public:
    MyTableDialog(QWidget *parent = nullptr);
    ~MyTableDialog();
    DataNM getData();

private:
    QSpinBox *n;
    QSpinBox *m;
};//class MyTableDialog : public QDialog

#endif // MYTABLEDIALOG_H
