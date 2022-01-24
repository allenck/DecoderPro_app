#ifndef VSDMANAGERFRAME_H
#define VSDMANAGERFRAME_H

#include "jmrijframe.h"
#include "libPr3_global.h"
#include "vsdecoder.h"
#include "propertychangeevent.h"
#include "propertychangelistener.h"

class VSDConfigDialog;
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
 /*public*/ void initComponents()override;
 /*public*/ void initGUI();
// /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
 /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);
 /*public*/ void firePropertyChange(PropertyChangeID id, QVariant oldProp, QVariant newProp);
 /*public*/ static /*final*/ QMap<PropertyChangeID, QString> PCIDMap;
 /*public*/ void addHelpMenu(QString ref, bool direct)override;
 /*public*/ void windowClosing(QCloseEvent* e) override;
 /*public*/ QString getClassName()override;

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
 /*private*/ VSDConfigDialog* cd;
 /*private*/ QList<QMenu*> menuList;
 /*private*/ bool is_auto_loading;
 /*private*/ bool is_viewing;
 /*private*/ QList<VSDecoder*> vsdlist;

 static Logger* log;
 /*private*/ void buildMenu();
 QVBoxLayout* decoderPaneLayout;
 void firePropertyChange(PropertyChangeEvent* evt);
 QSlider* volume;
 /*private*/ int master_volume;

protected:
 /*protected*/ void vsdControlPropertyChange(PropertyChangeEvent* event);

protected slots:
 /*protected*/ void closeButtonPressed(JActionEvent* e = 0);
 /*protected*/ void muteButtonPressed(JActionEvent* e = 0);
 /*protected*/ void addButtonPressed(JActionEvent* e = 0);
 /*protected*/ void addButtonPropertyChange(PropertyChangeEvent* event);
 /*protected*/ void volumeChange(ChangeEvent* e = 0);

 friend class VSDMFPropertyChangeListener;
};

class VSDMFPropertyChangeListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
  VSDManagerFrame* vsdmf;

 public:
  VSDMFPropertyChangeListener(VSDManagerFrame* vsdmf) {this->vsdmf = vsdmf;}

  QObject* self() override {return (QObject*)this;}
//@Override
/*public*/ void propertyChange(PropertyChangeEvent* event)override {
    vsdmf->log->debug(tr("property change name %1, old: %2, new:%3").arg(
            event->getPropertyName(), event->getOldValue().toString(), event->getNewValue().toString()));
    vsdmf->vsdControlPropertyChange(event);
  }
};

#endif // VSDMANAGERFRAME_H
