#ifndef EDITCIRCUITFRAME_H
#define EDITCIRCUITFRAME_H
#include "editframe.h"

class OpenPickListButton;
class LengthPanel;
class Sensor;
class Positionable;
class QFrame;
class QPushButton;
class JTextField;
class OBlock;
class CircuitBuilder;
class EditCircuitFrame : public EditFrame
{
    Q_OBJECT
public:
    //explicit EditCircuitFrame(QWidget *parent = 0);
    /*public*/ EditCircuitFrame(QString _title, CircuitBuilder* parent, OBlock* block);
    static int STRUT_SIZE;// = 10;
    static bool _firstInstance;// = true;
    static QPoint _loc;// = null;
    static QSize _dim;// = null;
    /*public*/ QString getClassName();

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
    /*private*/ OBlock* _block = nullptr;
    ///*private*/ CircuitBuilder* _parent;

    /*private*/ JTextField* _systemName;
    /*private*/ JTextField*  _blockName;// = new JTextField();
    /*private*/ JTextField*  _detectorSensorName;// = new JTextField();
    /*private*/ JTextField*  _errorSensorName;// = new JTextField();
    /*private*/ JTextField*  _blockState;//  = new JTextField();
    /*private*/ JTextField*  _numTrackSeg;// = new JTextField();
    /*private*/ JTextField*  _numTurnouts;// = new JTextField();
    LengthPanel* _lengthPanel;
    JPanel* _namePanel;
    /*private*/ JPanel* _buttonPanel;
    bool _create = false;

    // Sensor list
    /*private*/ JmriJFrame*      _pickFrame;
    /*private*/ QPushButton* _openPicklistButton;
    /*private*/ JPanel* makeContentPanel() override;
//    /*private*/ QWidget* MakePickListPanel();
//    void openPickList();
//    void closePickList();
//    /*private*/ QWidget* MakeButtonPanel();
    /*private*/ QWidget* MakeDoneButtonPanel();
    /*private*/ void convertIcons();
    Logger* log;
//    /*private*/ Sensor* getSensor(QString sensorName);

    // Sensor list
    OpenPickListButton/*<Sensor>*/* _pickTable;
    /*private*/ QString checkForSensors();
    /*private*/ JPanel* makeCreateBlockPanel();
    /*private*/ void createBlock();
    /*private*/ void deleteCircuit();
    /*private*/ void changeBlockName();
    /*private*/ JPanel* makeEditBlockPanel();
    /*private*/ void closeCreate();

private slots:
//    void openPickListButton_clicked();
protected:
    /*protected*/ void updateContentPanel(bool create);
//    /*protected*/ OBlock* getBlock();
    /*protected*/ void updateIconList(QList<Positionable*>* icons);
    /*protected*/ void closingEvent(bool close);

protected slots:

friend class CircuitBuilder;
};

#endif // EDITCIRCUITFRAME_H
