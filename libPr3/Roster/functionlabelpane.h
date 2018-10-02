#ifndef FUNCTIONLABELPANE_H
#define FUNCTIONLABELPANE_H

#include <QWidget>
#include "jtextfield.h"
#include <QCheckBox>
#include "rosterentry.h"
#include <QRadioButton>
#include "editableresizableimagepanel.h"
#include <QButtonGroup>

class Logger;
class FunctionLabelPane : public QWidget
{
 Q_OBJECT
public:
 explicit FunctionLabelPane(QWidget *parent = nullptr);
 /*public*/ FunctionLabelPane(RosterEntry* r, QWidget *parent = nullptr);

 /*public*/ bool guiChanged(RosterEntry* r);
 /*public*/ void update(RosterEntry* r);
 /*public*/ void dispose();
 /*public*/ bool includeInPrint();
 /*public*/ void includeInPrint(bool inc);
 /*public*/ void printPane(HardcopyWriter* w);

signals:

public slots:

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("FunctionLabelPane");
 RosterEntry* re;

 QVector<JTextField*> labels;
 QVector<QCheckBox*> lockable;
 QVector<QRadioButton*> shunterMode;
 QButtonGroup* shunterModeGroup;
 QVector<EditableResizableImagePanel*> _imageFilePath;
 QVector<EditableResizableImagePanel*> _imagePressedFilePath;

 // we're doing a manual allocation of position for
 // now, based on 28 labels
 // The references to maxfunction + 1 are due to F0
 /*private*/ /*final*/ int maxfunction = 28;
 bool print;// = false;

};

#endif // FUNCTIONLABELPANE_H
