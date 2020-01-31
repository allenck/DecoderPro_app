#ifndef VSDECODERPANE_H
#define VSDECODERPANE_H
#include "jmripanel.h"
#include <QTabWidget>
#include "appslib_global.h"

class QSlider;
class ChangeEvent;
class JToggleButton;
class ActionEvent;
class QStatusBar;
class VSDecoderEvent;
class DccLocoAddress;
class locoAddress;
class PropertyChangeEvent;
class VSDecoder;
class VSDecoderFrame;
class VSDConfigPanel;
class VSDecoderManager;
class APPSLIBSHARED_EXPORT VSDecoderPane : public JmriPanel
{
 Q_OBJECT
public:
 //explicit VSDecoderPane(QWidget *parent = 0);
 /*public*/ /*static*/ enum PropertyChangeID {

     ADDRESS_CHANGE, PROFILE_SELECT, MUTE, VOLUME_CHANGE
 };
 /*public*/ static /*final*/ QMap<PropertyChangeID, QString> PCIDMap;
 /*public*/ VSDecoderPane(VSDecoderFrame* p);
 /*public*/ VSDecoderFrame* getFrame();
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 /*public*/ static QString getDefaultVSDecoderFolder();
 /*public*/ void init();
 /*public*/ void initContext(QObject* context);
 /*public*/ void initComponents();
 /*public*/ VSDecoder* getDecoder();
 /*public*/ VSDecoder* getDecoder(QString profile);
 /*public*/ void firePropertyChange(PropertyChangeID id, QVariant oldProp, QVariant newProp);
 /*public*/ void setDecoder(VSDecoder* dec);
 /*public*/ void setAddress(locoAddress* a);
 /*public*/ void setTitle(DccLocoAddress* a);

signals:
 void notifyProperyChange(PropertyChangeEvent*);
public slots:
 /*public*/ void muteButtonPressed(ActionEvent* e =0);
 /*public*/ void volumeChange(ChangeEvent* e =0);

private:
 QString decoder_id;
 VSDecoderManager* decoder_mgr;
 /*final*/ static QString BASICPANEL;// = "Basic";
 /*final*/ static QString COMBOPANEL;// = "Sounds";
 /*final*/ static QString OPTIONPANEL;// = "Options";
 // GUI Components
 /*private*/ VSDecoderFrame* parent;

 /*private*/ QTabWidget* tabbedPane;
 /*private*/ VSDConfigPanel* configPanel;
 /*private*/ QWidget* soundsPanel;
 /*private*/ QWidget* optionPanel;
 /*private*/ QWidget* volumePanel;
 /*private*/ QStatusBar* statusBar;
 Logger* log;
 /*private*/ static QString VSDecoderFileLocation;// = NULL;
 void firePropertyChange(PropertyChangeEvent* evt);\
 JToggleButton* mute_button;
 QSlider* volume;

protected slots:
 /*protected*/ void decoderEventAction(VSDecoderEvent* e);

};

#endif // VSDECODERPANE_H
