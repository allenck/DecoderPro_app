#include "qtindxcvtablemodel.h"
#include "indexedcvtablemodel.h"

QtIndxCvTableModel::QtIndxCvTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

QtIndxCvTableModel::QtIndxCvTableModel(IndexedCvTableModel* model, QObject* parent)
{
 _model = model;
}

int QtIndxCvTableModel::rowCount(const QModelIndex &parent) const
{
 return _model->rowCount(parent);
}
int QtIndxCvTableModel::columnCount(const QModelIndex &parent) const
{
 return _model->columnCount(parent);
}

QVariant QtIndxCvTableModel::data(const QModelIndex &index, int role) const
{
 if (!index.isValid())
  return QVariant();

 if (index.row() >= _model->rowCount(QModelIndex()) || index.row() < 0)
  return QVariant();

 if (role == Qt::DisplayRole || role == Qt::EditRole)
 {
  CvValue* val = _model->getCvByRow(index.row());

  switch(index.column())
  {
   case 0:
      return val->number();
   case 1:
      return val->getValue();
  case 2:
      return val->getState();
  }
 }
 return QVariant();
}
QVariant QtIndxCvTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if (role != Qt::DisplayRole)
  return QVariant();
 if (orientation == Qt::Horizontal)
 {
  return _model->getColumnName(section);
 }
 return QVariant();
}
bool QtIndxCvTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
 Q_UNUSED(index);
 beginInsertRows(QModelIndex(), position, position+rows-1);

 for (int row=0; row < rows; row++)
 {
//     segmentInfo si;
//     listOfSegments.insert(position, si);
 }

 endInsertRows();
 return true;
}
bool QtIndxCvTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
//        listOfSegments.removeAt(position);
    }

    endRemoveRows();
    return true;
}
bool QtIndxCvTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if (index.isValid() && role == Qt::EditRole)
 {
  int row = index.row();

  CvValue* val = _model->getCvByRow(row);

//         switch (index.column())
//             p.first = value.toString();
//         else if (index.column() == 1)
//             p.second = value.toString();
//         else
//             return false;
//        QDateTime dt;
//  switch(index.column())
//  {
//        case 8:
//            dt = QDateTime::fromString((QString&)value, "yyyy/MM/dd");
//            if(dt.isValid())
//            {
//                si.startDate = (QString&)value;
//            }
//            break;
//        case 9:
//            dt = QDateTime::fromString((QString&)value, "yyyy/MM/dd");
//            if(dt.isValid())
//            {
//                si.endDate = (QString&)value;
//            }
//            break;

//        }
//        listOfSegments.replace(row, si);

//        selectedRow = row;
//        bSelectedRowChanged =true;
//        rowChanged changeEntry;
//        changeEntry.row = row;
//        changeEntry.index = index;
//        changeEntry.bChanged=true;
//        changeEntry.bDeleted = false;
//        changeEntry.segmentId = si.SegmentId;
//        int i;
//        for(i=0; i < changedRows.count(); i++)
//        {
//            if(changedRows.at(i).index == index)
//               break;
//        }
//        if(i >= changedRows.count())
//        {
//            changedRows.append(changeEntry);
//            emit rowChange(row, si.SegmentId, false, true);
//        }
//        listOfSegments.replace(row, si);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}
//void QtIndxCvTableModel::reset()
//{
//    QAbstractTableModel::reset();
//}
Qt::ItemFlags QtIndxCvTableModel::flags(const QModelIndex &index) const
{
 if (!index.isValid())
  return Qt::ItemIsEnabled;
// switch(index.column())
// {
//  case 1:
//   return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
// }
 if(_model->isCellEditable(index.row(), index.column()))
     return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
 // all other columns non-editable
 return QAbstractTableModel::flags(index);
}
void QtIndxCvTableModel::deleteRow(qint32 segmentId, const QModelIndex &index)
{

}
void QtIndxCvTableModel::unDeleteRow(qint32 segmentId, const QModelIndex &index)
{

}
