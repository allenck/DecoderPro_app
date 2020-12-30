#ifndef VSDCONTROL_H
#define VSDCONTROL_H

#include <QFrame>
#include "liblayouteditor_global.h"
class JActionEvent;
class QGridLayout;
class Logger;
class Insets;
class PropertyChangeEvent;
class GridBagConstraints;
class SoundEvent;
class QPushButton;
class QLabel;
class VSDConfig;
class LIBLAYOUTEDITORSHARED_EXPORT VSDControl : public QFrame
{
 Q_OBJECT
public:
 explicit VSDControl(QWidget *parent = 0);
 static /*public*/ QWidget* generateBlank();
 /*public*/ /*static*/ enum PropertyChangeID {

     ADDRESS_CHANGE, CONFIG_CHANGE, OPTION_CHANGE, PROFILE_SELECT, HORN, BELL, NOTCH, COUPLER, BRAKE, ESTART, _DELETE
 };
 Q_ENUMS(PropertyChangeID)
 /*public*/ static /*final*/ QMap<PropertyChangeID, QString> PCIDMap;
 /*public*/ VSDControl(QString title, QWidget *parent = 0);
 /*public*/ VSDControl(VSDConfig* c, QWidget *parent = 0);
 /*public*/ void addSoundButtons(QList<SoundEvent*> elist);
 /*public*/ void firePropertyChange(PropertyChangeID id, QVariant oldProp, QVariant newProp);

signals:
 void propertyChange(PropertyChangeEvent*);
public slots:
private:
 QString address;

 //Border tb;
 QLabel* addressLabel;
 QPushButton* configButton;
 QPushButton* optionButton;
 QPushButton* deleteButton;

 QWidget* soundsPanel;
 QWidget* configPanel;

 /*private*/ VSDConfig* config;
 /*private*/ GridBagConstraints setConstraints(int x, int y);
 // /*private*/ GridBagConstraints setConstraints(int x, int y, int fill) ;
 /*private*/ GridBagConstraints setConstraints(int x, int y, int fill, Insets* ins, int anchor);
  void firePropertyChange(PropertyChangeEvent* evt);
 Logger* log;
 QGridLayout* soundsPanelLayout;
 void common();

protected:
 /*protected*/ void initComponents(QString title);
protected slots:
 /*protected*/ void optionButtonPressed(JActionEvent* e = 0);
 /*protected*/ void configButtonPressed(JActionEvent* e = 0);
 /*protected*/ void deleteButtonPressed(JActionEvent* e = 0);
 /*protected*/ void configDialogPropertyChange(PropertyChangeEvent* event);
 /*protected*/ void optionsDialogPropertyChange(PropertyChangeEvent* event);

};

#endif // VSDCONTROL_H
