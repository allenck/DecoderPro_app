#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "jmri0.h"
#include "jmri1.h"



void PythonQt_init_Jmri(PyObject* module) {
PythonQt::priv()->registerClass(&AbstractAutomaton::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractAutomaton>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractAutomaton>, module, 0);
PythonQt::priv()->registerCPPClass("AbstractManager", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractManager>, module, 0);
PythonQt::priv()->registerCPPClass("AbstractProxyManager", "AbstractManager", "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractProxyManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractProxyManager>, module, 0);
PythonQt::priv()->registerCPPClass("AbstractSensor", "Sensor", "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractSensor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractSensor>, module, 0);
PythonQt::priv()->registerCPPClass("AbstractSensorManager", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractSensorManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractSensorManager>, module, 0);
PythonQt::priv()->registerClass(&AbstractSerialPortController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractSerialPortController>, NULL, module, 0);
PythonQt::priv()->registerCPPClass("AbstractTurnout", "Turnout", "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractTurnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractTurnout>, module, 0);
PythonQt::priv()->registerClass(&AddressedProgrammerManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AddressedProgrammerManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AddressedProgrammerManager>, module, 0);
PythonQt::priv()->registerCPPClass("Audio", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Audio>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Audio>, module, 0);
PythonQt::priv()->registerCPPClass("AudioBuffer", "Audio", "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioBuffer>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioBuffer>, module, 0);
PythonQt::priv()->registerCPPClass("AudioListener", "Audio", "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioListener>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioListener>, module, 0);
PythonQt::priv()->registerCPPClass("AudioManager", "AbstractManager", "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioManager>, module, 0);
PythonQt::priv()->registerCPPClass("AudioSource", "Audio", "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioSource>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioSource>, module, 0);
PythonQt::priv()->registerClass(&CommandStation::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_CommandStation>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_CommandStation>, module, 0);
PythonQt::priv()->registerClass(&DccLocoAddress::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_DccLocoAddress>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_DccLocoAddress>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&DccThrottle::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_DccThrottle>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_DccThrottle>, module, 0);
PythonQt::priv()->registerCPPClass("DefaultLogixManager", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_DefaultLogixManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_DefaultLogixManager>, module, 0);
PythonQt::priv()->registerCPPClass("DefaultMemoryManager", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_DefaultMemoryManager>, NULL, module, 0);
PythonQt::priv()->registerCPPClass("Editor", "JmriJFrame", "Jmri", PythonQtCreateObject<PythonQtWrapper_Editor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Editor>, module, 0);
PythonQt::priv()->registerCPPClass("JFrame", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_JFrame>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_JFrame>, module, 0);
PythonQt::priv()->registerCPPClass("JmriJFrame", "JFrame", "Jmri", PythonQtCreateObject<PythonQtWrapper_JmriJFrame>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_JmriJFrame>, module, 0);
PythonQt::priv()->registerCPPClass("LayoutBlockManager", "AbstractManager", "Jmri", PythonQtCreateObject<PythonQtWrapper_LayoutBlockManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LayoutBlockManager>, module, 0);
PythonQt::priv()->registerCPPClass("Light", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Light>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Light>, module, 0);
PythonQt::priv()->registerClass(&LnPacketizer::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnPacketizer>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnPacketizer>, module, 0);
PythonQt::priv()->registerClass(&LnPortController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnPortController>, NULL, module, 0);
PythonQt::priv()->registerCPPClass("LnPowerManager", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_LnPowerManager>, NULL, module, 0);
PythonQt::priv()->registerCPPClass("LnSensor", "AbstractSensor", "Jmri", PythonQtCreateObject<PythonQtWrapper_LnSensor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnSensor>, module, 0);
PythonQt::priv()->registerClass(&LnTrafficController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnTrafficController>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnTrafficController>, module, 0);
PythonQt::priv()->registerCPPClass("LnTurnout", "AbstractTurnout", "Jmri", PythonQtCreateObject<PythonQtWrapper_LnTurnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnTurnout>, module, 0);
PythonQt::priv()->registerClass(&LocoAddress::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoAddress>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoAddress>, module, 0);
PythonQt::priv()->registerClass(&LocoNetInterface::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoNetInterface>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoNetInterface>, module, 0);
PythonQt::priv()->registerClass(&LocoNetMessage::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoNetMessage>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoNetMessage>, module, 0);
PythonQt::priv()->registerCPPClass("MemoryManager", "AbstractManager", "Jmri", PythonQtCreateObject<PythonQtWrapper_MemoryManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_MemoryManager>, module, 0);
PythonQt::priv()->registerCPPClass("Positionable", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Positionable>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Positionable>, module, 0);
PythonQt::priv()->registerClass(&ProgrammerManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ProgrammerManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProgrammerManager>, module, 0);
PythonQt::priv()->registerCPPClass("ProxyLightManager", "AbstractProxyManager", "Jmri", PythonQtCreateObject<PythonQtWrapper_ProxyLightManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProxyLightManager>, module, 0);
PythonQt::priv()->registerCPPClass("ProxySensorManager", "AbstractProxyManager", "Jmri", PythonQtCreateObject<PythonQtWrapper_ProxySensorManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProxySensorManager>, module, 0);
PythonQt::priv()->registerCPPClass("ProxyTurnoutManager", "AbstractProxyManager", "Jmri", PythonQtCreateObject<PythonQtWrapper_ProxyTurnoutManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProxyTurnoutManager>, module, 0);
PythonQt::priv()->registerCPPClass("ReporterManager", "AbstractManager", "Jmri", PythonQtCreateObject<PythonQtWrapper_ReporterManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ReporterManager>, module, 0);
PythonQt::priv()->registerCPPClass("RouteManager", "AbstractManager", "Jmri", PythonQtCreateObject<PythonQtWrapper_RouteManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_RouteManager>, module, 0);
PythonQt::priv()->registerCPPClass("Sensor", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Sensor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Sensor>, module, 0);
PythonQt::priv()->registerClass(&Siglet::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Siglet>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Siglet>, module, 0);
PythonQt::priv()->registerCPPClass("SignalHead", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_SignalHead>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SignalHead>, module, 0);
PythonQt::priv()->registerCPPClass("Sound", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Sound>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Sound>, module, 0);
PythonQt::priv()->registerClass(&Throttle::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Throttle>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Throttle>, module, 0);
PythonQt::priv()->registerCPPClass("Turnout", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Turnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Turnout>, module, 0);


PythonQtRegisterListTemplateConverterForKnownClass(QVector, QString);
}
