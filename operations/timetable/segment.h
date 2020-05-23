#ifndef SEGMENT_H
#define SEGMENT_H

#include <QObject>
namespace TimeTable
{

class TimeTableDataManager;
class Segment : public QObject
{
 Q_OBJECT
public:
 /*public*/ Segment(int layoutId, QObject *parent = nullptr);
 /*public*/ Segment(int segmentId, int layoutId, QString segmentName, QObject *parent= nullptr);
 /*public*/ int getSegmentId();
 /*public*/ int getLayoutId();
 /*public*/ QString getSegmentName();
 /*public*/ void setSegmentName(QString newName);
 /*public*/ QString toString();


signals:

public slots:
private:
 TimeTableDataManager* _dm;// = TimeTableDataManager::getDataManager();

 /*private*/ /*final*/ int _segmentId;
 /*private*/ /*final*/ int _layoutId;
 /*private*/ QString _segmentName = "New Segment";  // NOI18N

};
}
#endif // SEGMENT_H
