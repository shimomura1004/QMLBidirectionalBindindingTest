#ifndef TESTCASELISTMODEL_H
#define TESTCASELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

class TestcaseListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Role {
        CheckedRole = Qt::UserRole,
        NameRole
    };

protected:
    QList< QPair<bool, QString> > testcases_;
    int count(){return testcases_.length();}

public:
    explicit TestcaseListModel(QAbstractListModel *parent = 0);

    int rowCount(const QModelIndex & = QModelIndex()) const override {return testcases_.length();}
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void check();
    Q_INVOKABLE void selectall();
    Q_INVOKABLE void deselectall();
    Q_INVOKABLE void resettitle();
    Q_INVOKABLE void set(int i, bool checked);

signals:
    void countChanged(int);

public slots:

};

#endif // TESTCASELISTMODEL_H
