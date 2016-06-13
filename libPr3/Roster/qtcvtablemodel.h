#ifndef QTCVTABLEMODEL_H
#define QTCVTABLEMODEL_H
#include <QAbstractTableModel>
#include "libPr3_global.h"

class CvTableModel;
class LIBPR3SHARED_EXPORT QtCvTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QtCvTableModel(QObject *parent = 0);
    QtCvTableModel(CvTableModel* model, QObject* parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    //void reset();
    void setSequenced(bool b);

    //QList<rowChanged> changedRows;
    void deleteRow(qint32 segmentId, const QModelIndex &index);
    void unDeleteRow(qint32 segmentId, const QModelIndex &index);
signals:
    void rowChange(qint32 row, qint32 segmentid, bool bDeleted, bool bChanged);

public slots:
private:
    CvTableModel* _model;

};

#endif // QTCVTABLEMODEL_H
