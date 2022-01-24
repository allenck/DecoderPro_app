#ifndef SENSORGROUPFRAME_H
#define SENSORGROUPFRAME_H
#include "jmrijframe.h"
#include "liblayouteditor_global.h"

class JActionEvent;
class Logix;
class QListView;
class JTextField;
class SensorTableModel;
class LIBLAYOUTEDITORSHARED_EXPORT SensorGroupFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit SensorGroupFrame(QWidget *parent = 0);
    /*public*/ /*final*/ static QString logixSysName;// = "SYS";
    /*public*/ /*final*/ static QString logixUserName;// = "System Logix";
    /*public*/ /*final*/ static QString ConditionalSystemPrefix;// = logixSysName+"_SGC_";
 /*public*/ void initComponents();
 /*public*/ QString getClassName();

private:

 SensorTableModel* _sensorModel;
//    //JScrollPane _sensorScrollPane;
 JTextField* _nameField;
 QListView*  _sensorGroupList;
 Logix* getSystemLogix();
 void clear();
 Logger* log;
 void deleteGroup(bool showMsg);

signals:

public slots:
 void addPressed();
 void viewPressed();
 void donePressed(JActionEvent* e = 0);
 void undoGroupPressed();

private:
    /*private*/ /*final*/ static QString namePrefix;//  = "SENSOR GROUP:";  // should be upper case
    /*private*/ /*final*/ static QString nameDivider;// = ":";

    /*private*/ /*final*/ static QString ConditionalUserPrefix;// = "Sensor Group ";
    /*private*/ int rowHeight;

};

#endif // SENSORGROUPFRAME_H
