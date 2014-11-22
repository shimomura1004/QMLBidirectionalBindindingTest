#include "testcaselistmodel.h"
#include <QStringList>
#include <QDebug>

TestcaseListModel::TestcaseListModel(QAbstractListModel *parent) :
    QAbstractListModel(parent)
{
    beginInsertRows(QModelIndex(), 0, 3);

    for (int i = 0; i < 10; ++i) {
        QString name = QStringLiteral("test_%1").arg(QString::number(i));
        testcases_.push_back(QPair<bool, QString>(false, name));
    }

    endInsertRows();

    emit countChanged(testcases_.length());
}

QVariant TestcaseListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int i = index.row();
    if (i < 0 || i > rowCount())
        return QVariant();

    switch(role) {
    case CheckedRole:
        return QVariant(testcases_[i].first);
    case NameRole:
        return QVariant(testcases_[i].second);
    }

    return QVariant();
}

Qt::ItemFlags TestcaseListModel::flags(const QModelIndex &) const
{
    qDebug() << "flags called";
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}

bool TestcaseListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int i = index.row();
    if (i < 0 || i > rowCount())
        return false;


    switch(role) {
    case CheckedRole:
    {
        bool checked = value.toBool();
        if (testcases_[i].first != checked) {
            testcases_[i].first = checked;
            emit dataChanged(index, index);
        }
        break;
    }
    case NameRole:
    {
        QString name = value.toString();
        if (testcases_[i].second != name) {
            testcases_[i].second = name;
            emit dataChanged(index, index);
        }
        break;
    }
    }

    return true;
}

QHash<int, QByteArray> TestcaseListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CheckedRole] = "checked";
    roles[NameRole] = "name";
    return roles;
}

void TestcaseListModel::check()
{
    qDebug() << "check:" << testcases_;
}

void TestcaseListModel::selectall()
{
    for(int i=0; i < testcases_.length(); i++)
        setData(this->index(i), QVariant(true), CheckedRole);
}

void TestcaseListModel::deselectall()
{
    for(int i=0; i < testcases_.length(); i++)
        setData(this->index(i), QVariant(false), CheckedRole);
}

void TestcaseListModel::resettitle()
{
    for (int i=0; i < testcases_.length(); i++)
        setData(this->index(i), QVariant(QStringLiteral("test_%1").arg(QString::number(i))), NameRole);
}

void TestcaseListModel::set(int i, bool checked)
{
    setData(this->index(i), QVariant(checked), CheckedRole);
}
