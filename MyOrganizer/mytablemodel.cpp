#include "mytablemodel.h"

#define QREC(n) query.record().value(n).toString()
#define SCI(n) static_cast<int>(n)
#define SCIDS SCI(m_data.size())

MyTableModel::MyTableModel(QObject *parent) : QSqlTableModel(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tasks");
    if (!db.open()) qCritical() << "Cannot open database";

    QSqlQuery query(db);
    setQuery(query);

    this->query().exec("CREATE TABLE tasks (id INTEGER PRIMARY KEY NOT NULL, name VARCHAR(500), description VARCHAR(1000), "
                       "start VARCHAR(10), end VARCHAR(10), progress VARCHAR(4));");
    setTable("tasks");
    select();

    query = this->query();
    if (!query.exec("SELECT * FROM tasks;")) qCritical() << "Unable to select table";

    m_data.push_back(MyLine("Название задания","Описание задания","Дата начала","Дата окончания","Прогресс"));
    for (;query.next();) m_data.push_back(MyLine(QREC(1),QREC(2),QREC(3),QREC(4),QREC(5)));
}//MyTableModel(QObject *parent = nullptr);

MyTableModel::~MyTableModel()
{
    if (!this->query().exec("DELETE FROM tasks;")) qCritical() << "Unable to drop table";

    QString str = "INSERT INTO tasks (id, name, description, start, end, progress)"
                          "VALUES('%1','%2','%3','%4','%5','%6');";
    for (int i = 1; i < SCIDS; ++i)
        this->query().exec(str.arg(i).arg(m_data[i].name).arg(m_data[i].description).arg(m_data[i].start).arg(m_data[i].end).arg(m_data[i].progress));
    db.close();
}//~MyTableModel();

int MyTableModel::rowCount(const QModelIndex &) const
{
    return SCIDS;
}//int rowCount(const QModelIndex &parent) const override;

#define SCU(n) static_cast<unsigned>(n)
#define UIR SCU(index.row())

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    switch (role) {
    case IdRole: return QVariant(UIR);
    case NameRole: return QVariant(m_data[UIR].name);
    case DescRole: return QVariant(m_data[UIR].description);
    case StartRole: return QVariant(m_data[UIR].start);
    case EndRole: return QVariant(m_data[UIR].end);
    case ProgRole: return QVariant(m_data[UIR].progress);
    case IsDelRole: return QVariant(m_data[UIR].isDelete);
    default: return QVariant();
    }//switch (role)
}//QVariant data(const QModelIndex &index, int role) const override;

QHash<int, QByteArray> MyTableModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles[IdRole]     = "taskID";
    roles[NameRole]   = "name";
    roles[DescRole]   = "description";
    roles[StartRole]  = "start";
    roles[EndRole]    = "end";
    roles[ProgRole]   = "progress";
    roles[IsDelRole]  = "isDelete";
    return roles;
}//QHash<int, QByteArray> roleNames() const override;

void MyTableModel::addLine(QString n, QString d, QString s, QString e, QString p)
{
    beginInsertRows(QModelIndex(), SCIDS, SCIDS);
    m_data.push_back(MyLine(n, d, s, e, p));
    endInsertRows();
    emit dataChanged(createIndex(0,0), createIndex(SCIDS, 0));
}//Q_INVOKABLE void addLine(QString n, QString d, QString s, QString e, QString p);

#define MyRemoveIfWithLambda std::remove_if(m_data.begin(), m_data.end(),[](auto& i){ return i.isDelete; } )

void MyTableModel::delLines()
{
    beginRemoveRows(QModelIndex(), 0, SCIDS);
    endRemoveRows();
    m_data.erase(MyRemoveIfWithLambda, m_data.end());
    beginInsertRows(QModelIndex(), 0, SCIDS - 1);
    endInsertRows();
    emit dataChanged(createIndex(0,0), createIndex(SCIDS, 0));
}//Q_INVOKABLE void delLines();

void MyTableModel::setIsDel(int index)
{
    m_data[SCU(index)].isDelete = !m_data[SCU(index)].isDelete;
}//Q_INVOKABLE void setIsDel(int index);

void MyTableModel::changeLineData(int index, QString n, QString d, QString s, QString e, QString p)
{
    m_data[SCU(index)] = MyLine(n, d, s, e, p);
    emit dataChanged(createIndex(0,0), createIndex(SCIDS, 0));
}//Q_INVOKABLE void changeLineData(int index);
