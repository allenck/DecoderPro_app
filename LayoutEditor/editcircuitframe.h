#ifndef EDITCIRCUITFRAME_H
#define EDITCIRCUITFRAME_H
#include "jmrijframe.h"

class Sensor;
class Positionable;
class QFrame;
class QPushButton;
class JTextField;
class OBlock;
class CircuitBuilder;
class EditCircuitFrame : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit EditCircuitFrame(QWidget *parent = 0);
    /*public*/ EditCircuitFrame(QString _title, CircuitBuilder* parent, OBlock* block, QWidget *parentWidget = 0);
    static int STRUT_SIZE;// = 10;
    static bool _firstInstance;// = true;
    static QPoint _loc;// = null;
    static QSize _dim;// = null;

signals:

public slots:
 private:
    /*private*/ OBlock* _block;
    /*private*/ CircuitBuilder* _parent;

    /*private*/ JTextField*  _blockName;// = new JTextField();
    /*private*/ JTextField*  _detectorSensorName;// = new JTextField();
    /*private*/ JTextField*  _errorSensorName;// = new JTextField();
    /*private*/ JTextField*  _blockState;//  = new JTextField();
    /*private*/ JTextField*  _numTrackSeg;// = new JTextField();
    /*private*/ JTextField*  _numTurnouts;// = new JTextField();

    // Sensor list
    /*private*/ JmriJFrame*      _pickFrame;
    /*private*/ QPushButton* _openPicklistButton;
    /*private*/ void makeContentPanel();
    /*private*/ QWidget* MakePickListPanel();
    void openPickList();
    void closePickList();
    /*private*/ QWidget* MakeButtonPanel();
    /*private*/ QWidget* MakeDoneButtonPanel();
    Logger* log;
    /*private*/ Sensor* getSensor(QString sensorName);

private slots:
    void openPickListButton_clicked();
protected:
    /*protected*/ void updateContentPanel();
    /*protected*/ OBlock* getBlock();
    /*protected*/ void updateIconList(QList<Positionable*>* icons);
protected slots:
    /*protected*/ void closingEvent();
friend class CircuitBuilder;
};

#endif // EDITCIRCUITFRAME_H
