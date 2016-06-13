#ifndef PLAYEDITOR_H
#define PLAYEDITOR_H
#include "sdfmacroeditor.h"

class QComboBox;
class QCheckBox;
class QSpinBox;
class PlayEditor : public SdfMacroEditor
{
 Q_OBJECT
public:
 //explicit PlayEditor(QWidget *parent = 0);
 /*public*/ PlayEditor(SdfMacro* inst, QWidget *parent = 0);
 /*public*/ void update();

signals:

public slots:
 void guiChanged();
private:
 //SpinnerNumberModel handleModel = new SpinnerNumberModel(0, 0, 63, 1);
 QSpinBox* handle;// = new JSpinner(handleModel);
 QComboBox* loop;// = new JComboBox<String>(SdfConstants.loopNames);
 QCheckBox* wavbrk1;// = new JCheckBox("Invert Loop Reason");
 QCheckBox* wavbrk2;// = new JCheckBox("Global Loop Reason");

};

#endif // PLAYEDITOR_H
