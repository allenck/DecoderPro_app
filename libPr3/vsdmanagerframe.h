#ifndef VSDMANAGERFRAME_H
#define VSDMANAGERFRAME_H

#include "jmrijframe.h"
#include "libPr3_global.h"

class QSlider;
class ChangeEvent;
class QVBoxLayout;
class PropertyChangeListener;
class JActionEvent;
class VSDConfig;
class LIBPR3SHARED_EXPORT VSDManagerFrame : public JmriJFrame
{
 Q_OBJECT
public:
 explicit VSDManagerFrame(QWidget *parent = 0);
 /*public*/ /*static*/ enum PropertyChangeID {

     MUTE, VOLUME_CHANGE, ADD_DECODER, REMOVE_DECODER, CLOSE_WINDOW
 };
 /*public*/ void initComponents();
 /*public*/ void initGUI();
 /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
 /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);
 /*public*/ void firePropertyChange(PropertyChangeID id, QVariant oldProp, QVariant newProp);
 /*public*/ static /*final*/ QMap<PropertyChangeID, QString> PCIDMap;
 /*public*/ void addHelpMenu(QString ref, bool direct);
 /*public*/ void windowClosing(QCloseEvent e);
 /*public*/ QString getClassName();

signals:
 void notifyPropertyChange(PropertyChangeEvent *event);

public slots:
 ///*public*/ void On_propertyChange(PropertyChangeEvent* event);
 /*public*/ void newControlPropertyChange(PropertyChangeEvent* event);
 /*public*/ void propertyChange(PropertyChangeEvent* event);

private:
 QWidget* decoderPane;
 QWidget* volumePane;
 QWidget* decoderBlank;
 /*private*/ VSDConfig* config;
 /*private*/ QList<QMenu*> menuList;
 Logger* log;
 /*private*/ void buildMenu();
 QVBoxLayout* decoderPaneLayout;
 void firePropertyChange(PropertyChangeEvent* evt);
 QSlider* volume;

protected:
 /*protected*/ void vsdControlPropertyChange(PropertyChangeEvent* event);

protected slots:
 /*protected*/ void closeButtonPressed(JActionEvent* e = 0);
 /*protected*/ void muteButtonPressed(JActionEvent* e = 0);
 /*protected*/ void addButtonPressed(JActionEvent* e = 0);
 /*protected*/ void addButtonPropertyChange(PropertyChangeEvent* event);
 /*protected*/ void volumeChange(ChangeEvent* e = 0);


};

#endif // VSDMANAGERFRAME_H
