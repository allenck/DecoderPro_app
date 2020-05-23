#ifndef TRAINTYPE_H
#define TRAINTYPE_H

#include <QObject>

namespace TimeTable
{

class TimeTableDataManager;
class TrainType : public QObject
{
 Q_OBJECT
public:
 /*public*/ TrainType(int layoutId,QObject *parent = nullptr);
 /*public*/ TrainType(int typeId, int layoutId, QString typeName, QString typeColor, QObject *parent = nullptr);
 /*public*/ int getTypeId();
 /*public*/ int getLayoutId();
 /*public*/ QString getTypeName();
 /*public*/ void setTypeName(QString newName);
 /*public*/ QString getTypeColor();
 /*public*/ void setTypeColor(QString newColor);
 /*public*/ QString toString();


signals:

public slots:
private:
 /*private*/ /*final*/ int _typeId;
 /*private*/ /*final*/ int _layoutId;
 /*private*/ QString _typeName = "New Type";  // NOI18N
 /*private*/ QString _typeColor = "#000000";  // NOI18N
 TimeTableDataManager* _dm;// = TimeTableDataManager::getDataManager();
};
}
#endif // TRAINTYPE_H
