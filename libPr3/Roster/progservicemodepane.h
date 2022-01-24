#ifndef PROGSERVICEMODEPANE_H
#define PROGSERVICEMODEPANE_H
#include "progmodeselector.h"
#include "logger.h"
#include <QButtonGroup>
#include <QBoxLayout>

class JActionEvent;
class QBoxLayout;
class GlobalProgrammerManager;
class ProgrammingMode;
class QComboBox;
class PropertyChangeEvent;
class QButtonGroup;
class QRadioButton;
class ProgServiceModePane : public ProgModeSelector
{
    Q_OBJECT
public:
    //explicit ProgServiceModePane(QWidget *parent = 0);
    /*public*/ ProgServiceModePane(QBoxLayout::Direction direction, QButtonGroup* group = new QButtonGroup, QWidget *parent = 0);
    /*public*/ Programmer* getProgrammer();
    /*public*/ bool isSelected();
    /*public*/ void dispose();

signals:

public slots:
//    void OnRadioButton();
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    void programmerSelected();
    /*public*/ void actionPerformed(JActionEvent* /*e*/ = 0);

private:
    void init();
    // GUI member declarations
    QComboBox* progBox;
    QButtonGroup* modeGroup;// 		= new QButtonGroup();
    QMap<QString, QRadioButton*>* buttonMap;// = new QMap<ProgrammingMode*, QRadioButton*>();
    QList<QRadioButton*>* buttonPool;// = new ArrayList<JRadioButton>();
    Logger* log;
    QBoxLayout* layout;
    void setGuiFromProgrammer();

protected:
    /*protected*/ void setButtonMode(int mode);
/*protected*/ QList<GlobalProgrammerManager*>* getMgrList();

    friend class ProgModePane;
};

#endif // PROGSERVICEMODEPANE_H
