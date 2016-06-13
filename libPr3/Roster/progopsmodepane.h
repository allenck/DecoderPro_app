#ifndef PROGOPSMODEPANE_H
#define PROGOPSMODEPANE_H

#include <QWidget>
#include "logger.h"
#include <QButtonGroup>
#include <QBoxLayout>

class ActionEvent;
class PropertyChangeEvent;
class ProgrammingMode;
class QBoxLayout;
class QComboBox;
class AddressedProgrammer;
class Programmer;
class QButtonGroup;
class QRadioButton;
class JTextField;
class QCheckBox;
class ProgOpsModePane : public QWidget
{
    Q_OBJECT
public:
    //explicit ProgOpsModePane(QWidget *parent = 0);
    /*public*/ ProgOpsModePane(QBoxLayout::Direction direction, QButtonGroup* group = new QButtonGroup(), QWidget *parent = 0);
//    /*public*/ Programmer* getProgrammer();
//    /*public*/ bool isSelected();
    /*public*/ void dispose();
    /*public*/ bool isSelected();
    /*public*/ Programmer* getProgrammer();

signals:

public slots:
    void programmerSelected();
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void actionPerformed(ActionEvent* e);

private:
    QButtonGroup* mModeGroup;
    QRadioButton* mOpsByteButton;//  	= new QRadioButton();
    JTextField* mAddrField;//           = new JTextField(4);
    QCheckBox* mLongAddrCheck;//        = new QCheckBox("Long address");
    void init();
    Logger* log;
    /*private*/ int getMode();
//    /*private*/ void setProgrammerMode(int mode);
    AddressedProgrammer* programmer;
    QString  oldAddrText;//
    bool oldLongAddr;//             = false;= "";
    QComboBox/*<AddressedProgrammerManager>*/*   progBox;
    QBoxLayout* layout;
    QList<QRadioButton*> buttonPool;// = new QList<QRadioButton*>();
    QMap<ProgrammingMode*, QRadioButton*> buttonMap;// = new QMap<ProgrammingMode*,QRadioButton>();
    QButtonGroup* modeGroup;// 		    = new QButtonGroup();
    void setGuiFromProgrammer();
    void setProgrammerFromGui(Programmer* programmer);


};

#endif // PROGOPSMODEPANE_H
