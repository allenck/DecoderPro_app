#ifndef TRAINICON_H
#define TRAINICON_H
#include "locoicon.h"
#include "train.h"
#include "liblayouteditor_global.h"

//class TrainTrain;
class ThrottleFrame;
class LIBLAYOUTEDITORSHARED_EXPORT TrainIcon : public LocoIcon
{
 Q_OBJECT
public:
 //explicit TrainIcon(QWidget *parent = 0);
 /*public*/ TrainIcon(Editor* editor, QWidget* parent = 0);
 /*public*/ void setShowTooltip(bool set);
 /*public*/ void setTrain(Operations::Train* train);
 /*public*/ Operations::Train* getTrain();
 /*public*/ void setConsistNumber(int cN);

signals:

public slots:
private:
 /*private*/ /*final*/ int range;// = 25; // how close the train icon needs to be to the next location coordinates in a train's
 ThrottleFrame* _tf;// = null;
 int _consistNumber;// = 0;
 /*private*/ int getConsistNumber();
 Operations::Train* _train;// = NULL;

};

#endif // TRAINICON_H
