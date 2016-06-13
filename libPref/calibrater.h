#ifndef CALIBRATER_H
#define CALIBRATER_H

#include "jmrijframe.h"
#include "libpref_global.h"

class QVBoxLayout;
class QCheckBox;
class RosterSpeedProfile;
class BlockOrder;
class Warrant;
class LIBPREFSHARED_EXPORT Calibrater : public JmriJFrame
{
 Q_OBJECT
public:
 //explicit Calibrater(QWidget *parent = 0);
 Calibrater(Warrant* w, bool isForward, QPoint pt, QWidget *parent = 0);

signals:

public slots:
private:
 /*private*/ int _calibrateIndex;
 /*private*/ Warrant* _warrant;
 /*private*/ float _maxSpeed;
 /*private*/ long _entryTime;
 /*private*/ float _factor;
 /*private*/ float _rawSpeed;
 /*private*/ BlockOrder* _calibBlockOrder;
 RosterSpeedProfile*  _speedProfile;
 bool _isForward;

 /*private*/ QWidget* _mainPanel;
 /*private*/ QCheckBox* _addBox;// = new JCheckBox(Bundle.getMessage("addFactor"));
 /*private*/ QCheckBox* _ignoreBox;// = new JCheckBox(Bundle.getMessage("ignoreFactor"));
 /*private*/ QCheckBox* _clearBox;// = new JCheckBox(Bundle.getMessage("clearFactor"));
 /*private*/ QWidget* makeButtonPanel();
 /*private*/ QWidget* makeEntryPanel(QString name, bool isForward);
 /*private*/ QWidget* makeExitPanel(bool init);
 Logger* log;
 QVBoxLayout* _mainPanelLayout;

private slots:
 /*private*/ void dofactor();


protected:
 /*protected*/ QString verifyCalibrate();
 /*protected*/ void calibrateAt(int index);

 friend class NXFrame;
};

#endif // CALIBRATER_H
