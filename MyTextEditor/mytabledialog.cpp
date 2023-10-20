#include "mytabledialog.h"

MyTableDialog::MyTableDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Таблица"));
    setFixedSize(200, 100);

    QGridLayout *layout = new QGridLayout();
    setLayout(layout);

    n = new QSpinBox (this);
    m = new QSpinBox (this);
    n->setValue(1);
    m->setValue(1);
    layout->addWidget(n, 1, 1, 1, 2);
    layout->addWidget(m, 1, 3, 1, 2);

    QPushButton *ok = new QPushButton ("&Ok");
    QPushButton *cancel = new QPushButton ("&Cancel");

    connect(ok, SIGNAL(clicked()), SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), SLOT(reject()));

    layout->addWidget(cancel, 2, 1, 1, 2);
    layout->addWidget(ok, 2, 3, 1, 2);
}//MyTableDialog(QWidget *parent = nullptr)

MyTableDialog::~MyTableDialog()
{
    delete n;
    delete m;
}//~MyTableDialog()

DataNM MyTableDialog::getData()
{
    return DataNM(n->value(), m->value());
}//DataNM getData()
