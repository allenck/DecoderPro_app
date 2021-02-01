#ifndef PROGSERVICEMODECOMBOBOX_H
#define PROGSERVICEMODECOMBOBOX_H
#include "progmodeselector.h"
#include "logger.h"
#include <QBoxLayout>
#include "jlabel.h"
#include "jcombobox.h"

class JActionEvent;
class GlobalProgrammerManager;
class PropertyChangeEvent;
class ProgServiceModeComboBox : public ProgModeSelector
{
    Q_OBJECT
public:
    explicit ProgServiceModeComboBox(QBoxLayout::Direction direction = QBoxLayout::LeftToRight, QWidget *parent = 0);
    /*public*/ Programmer* getProgrammer();

signals:

public slots:
//    void On_boxCurrentIndexChanged(int);
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void dispose();
    /*public*/ void actionPerformed(JActionEvent* e = 0);

private:
    // GUI member declarations
    JLabel* progLabel = new JLabel(tr("Program on:"));
    QComboBox/*<GlobalProgrammerManager> */* progBox;
    QComboBox/*<ProgrammingMode>*/*          modeBox;
    QList<int> modes;// = new qList<int>();
    Logger* log;
protected:
//    /*protected*/ QList<GlobalProgrammerManager*>* getMgrList();
protected slots:
    void programmerSelected();

};

#endif // PROGSERVICEMODECOMBOBOX_H
