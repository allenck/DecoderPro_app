#include "pythonwrappers.h"
#include "jframe.h"
#include "PythonQt.h"
#include <QDebug>
//#include <QtTest/QtTest>
#include "lntrafficcontroller.h"
#include "generated_cpp/jmri/jmri0.h"
#include "generated_cpp/jmri/jmri1.h"

void PythonQt_init_Jmri(PyObject*);

PythonWrappers::PythonWrappers(QObject *parent) :
  QObject(parent)
{
}

void PythonWrappers::defineClasses()
{
#if 0
// int iType = qRegisterMetaType<JFrame>("JFrame");
// qDebug() << "JFrame type =" + QString::number(iType);


 PythonQt::self()->registerCPPClass("JFrame",NULL,"jmri", PythonQtCreateObject<JFrame_Wrapper>);
// PythonQt::self()->registerClass(&JFrame::staticMetaObject, "jmri", PythonQtCreateObject<JFrameWrapper>);
 PythonQt::self()->registerCPPClass("LocoNetMessage", NULL, "jmri", PythonQtCreateObject<LocoNetMessage_Wrapper>);
 //PythonQt::self()->registerCPPClass("LnTrafficController", NULL, "jmri", PythonQtCreateObject<LnTrafficController_Wrapper>);

 QObjectList* list = InstanceManager::getList("SystemConnectionMemo");
 int i = 0;
 foreach (QObject* memo, *list)
 {
  if(qobject_cast<LocoNetSystemConnectionMemo*>(memo) != NULL)
  {
   LocoNetSystemConnectionMemo*  connectionMemo = (LocoNetSystemConnectionMemo*)memo;
   LnTrafficController* trafficController = connectionMemo->getLnTrafficController();
   //PythonQt::self()->getMainModule().addObject("LnTrafficController",(LnTrafficController*) trafficController);
   if(qobject_cast<LnPacketizer*>(trafficController) != NULL)
    PythonQt::self()->getMainModule().addObject("LnPacketizer", (LnPacketizer*)trafficController);
  }
  PythonQt::self()->addDecorators(new LnPacketizer_Decorators());
 }
 InstanceManager* instanceManager = InstanceManager::instance();
 PythonQt::self()->getMainModule().addObject("InstanceManager", instanceManager);
 PythonQt::self()->addDecorators(new InstanceManager_Decorators());

 PythonQt::self()->registerCPPClass("NamedBean", "QObject", "jmri", PythonQtCreateObject<NamedBean_Wrapper>);
 PythonQt::self()->registerCPPClass("AbstractNamedBean", "NamedBean", "jmri", PythonQtCreateObject<AbstractNamedBean_Wrapper>);
 PythonQt::self()->registerCPPClass("Turnout", "AbstractNamedBean", "jmri", PythonQtCreateObject<Turnout_Wrapper>);
 PythonQt::self()->registerCPPClass("AbstractTurnout", "Turnout", "jmri", PythonQtCreateObject<AbstractTurnout_Wrapper>);
 PythonQt::self()->registerCPPClass("LnTurnout", "AbstractTurnout", "jmri", PythonQtCreateObject<LnTurnout_Wrapper>);
 PythonQt::self()->addDecorators(new Turnout_Decorators());
 PythonQt::self()->addDecorators(new ProxyTurnoutManager_Decorators());

 PythonQt::self()->registerCPPClass("ProxySensorManager", NULL, "jmri", PythonQtCreateObject<ProxySensorManager_Wrapper> );
 PythonQt::self()->registerCPPClass("LnSensor", "AbstractSensor", "jmri", PythonQtCreateObject<LnSensor_Wrapper> );
 PythonQt::self()->registerCPPClass("AbstractSensor", "Sensor", "jmri", PythonQtCreateObject<AbstractSensor_Wrapper> );
 PythonQt::self()->registerCPPClass("Sensor", "AbstractNamedBean", "jmri", PythonQtCreateObject<Sensor_Wrapper> );

 PythonQt::self()->registerCPPClass("FlowLayout", "QLayout", "jmri", PythonQtCreateObject<FlowLayout_Wrapper> );
 PythonQt::self()->registerCPPClass("PanelMenu", "QMenu", "jmri", PythonQtCreateObject<PanelMenu_Wrapper> );
 PythonQt::self()->registerCPPClass("Editor", "JmriJFrame", "jmri", PythonQtCreateObject<Editor_Wrapper> );
 PythonQt::self()->registerCPPClass("JButton", "QPushButton", "jmri", PythonQtCreateObject<JButton_Wrapper> );
 PythonQt::self()->registerCPPClass("ActionEvent", "", "jmri", PythonQtCreateObject<ActionEvent_Wrapper> );

 PythonQt::self()->registerCPPClass("AudioManager", "AbstractManager", "jmri", PythonQtCreateObject<AudioManager_Wrapper> );
 PythonQt::self()->registerCPPClass("AbstractAudioManager", "AudioManager", "jmri", PythonQtCreateObject<AbstractAudioManager_Wrapper> );
 PythonQt::self()->registerCPPClass("DefaultAudioManager", "AbstractAudioManager", "jmri", PythonQtCreateObject<DefaultAudioManager_Wrapper> );
 PythonQt::self()->registerCPPClass("Audio", "AbstractNamedBean", "jmri", PythonQtCreateObject<Audio_Wrapper> );
 PythonQt::self()->registerCPPClass("AudioBuffer", "Audio", "jmri", PythonQtCreateObject<AudioBuffer_Wrapper> );
 PythonQt::self()->registerCPPClass("AudioSource", "Audio", "jmri", PythonQtCreateObject<AudioSource_Wrapper> );
 PythonQt::self()->registerCPPClass("AudioListener", "Audio", "jmri", PythonQtCreateObject<AudioListener_Wrapper> );
 PythonQt::self()->registerCPPClass("QtSoundAudioBuffer", "AbstractAudioBuffer", "jmri", PythonQtCreateObject<QtSoundAudioBuffer_Wrapper> );
 PythonQt::self()->registerCPPClass("AbstractAudioBuffer", "AbstractAudio", "jmri", PythonQtCreateObject<QtSoundAudioBuffer_Wrapper> );
 PythonQt::self()->registerCPPClass("AbstractAudio", "AudioBuffer", "jmri", PythonQtCreateObject<AbstractAudio_Wrapper> );

 PythonQt::self()->registerCPPClass("DccThrottle", "Throttle", "jmri", PythonQtCreateObject<DccThrottle_Wrapper> );
 PythonQt::self()->registerCPPClass("Throttle", "", "jmri", PythonQtCreateObject<Throttle_Wrapper> );

// PythonQt::self()->registerCPPClass("AbstractAutomaton", "Runnable", "jmri", PythonQtCreateObject<AbstractAutomaton_Wrapper> );
 PythonQt::self()->registerCPPClass("Runnable", "QThread", "jmri", PythonQtCreateObject<Runnable_Wrapper> );
// PythonQt::self()->addDecorators(new AbstractAutomaton_Decorators());

// PythonQt::self()->registerCPPClass("Siglet", "AbstractAutomaton", "jmri", PythonQtCreateObject<Siglet_Wrapper> );
#endif

 PythonQt_init_Jmri(0);
#if 0
// PythonQtObjectPtr module = NULL;
// PythonQt::priv()->registerClass(&AbstractAutomaton::staticMetaObject, "MyPackage", PythonQtCreateObject<PythonQtWrapper_AbstractAutomaton>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractAutomaton>, module, 0);
// PythonQt::priv()->registerClass(&Siglet::staticMetaObject, "MyPackage", PythonQtCreateObject<PythonQtWrapper_Siglet>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Siglet>, module, 0);

 PythonQt::self()->registerCPPClass("AbstractShutDownTask", "ShutDownTask", "jmri", PythonQtCreateObject<AbstractShutDownTask_Wrapper> );
#endif
}
