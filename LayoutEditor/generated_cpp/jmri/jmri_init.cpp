#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "jmri0.h"
#include "jmri1.h"



void PythonQt_init_Jmri(PyObject* module) {
PythonQt::priv()->registerClass(&AbstractAutomaton::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractAutomaton>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractAutomaton>, module, 0);
PythonQt::priv()->registerClass(&AbstractManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractManager>, module, 0);
PythonQt::priv()->registerClass(&AbstractNamedBean::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractNamedBean>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractNamedBean>, module, 0);
PythonQt::priv()->registerClass(&AbstractProxyManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractProxyManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractProxyManager>, module, 0);
PythonQt::priv()->registerClass(&AbstractSensor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractSensor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractSensor>, module, 0);
PythonQt::priv()->registerClass(&AbstractSensorManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractSensorManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractSensorManager>, module, 0);
PythonQt::priv()->registerClass(&AbstractSerialPortController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractSerialPortController>, NULL, module, 0);
PythonQt::priv()->registerClass(&AbstractTurnout::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractTurnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractTurnout>, module, 0);
PythonQt::priv()->registerClass(&Audio::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Audio>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Audio>, module, 0);
PythonQt::priv()->registerClass(&AudioBuffer::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioBuffer>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioBuffer>, module, 0);
PythonQt::priv()->registerClass(&AudioListener::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioListener>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioListener>, module, 0);
PythonQt::priv()->registerClass(&AudioManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioManager>, module, 0);
PythonQt::priv()->registerClass(&AudioSource::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioSource>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioSource>, module, 0);
PythonQt::priv()->registerClass(&CommandStation::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_CommandStation>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_CommandStation>, module, 0);
PythonQt::priv()->registerClass(&DccLocoAddress::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_DccLocoAddress>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_DccLocoAddress>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&DccThrottle::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_DccThrottle>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_DccThrottle>, module, 0);
PythonQt::priv()->registerCPPClass("Editor", "JmriJFrame", "Jmri", PythonQtCreateObject<PythonQtWrapper_Editor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Editor>, module, 0);
PythonQt::priv()->registerClass(&InstanceManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_InstanceManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_InstanceManager>, module, 0);
PythonQt::priv()->registerCPPClass("JmriJFrame", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_JmriJFrame>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_JmriJFrame>, module, 0);
PythonQt::priv()->registerClass(&LayoutBlockManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LayoutBlockManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LayoutBlockManager>, module, 0);
PythonQt::priv()->registerClass(&Light::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Light>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Light>, module, 0);
PythonQt::priv()->registerClass(&LnPacketizer::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnPacketizer>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnPacketizer>, module, 0);
PythonQt::priv()->registerClass(&LnPortController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnPortController>, NULL, module, 0);
PythonQt::priv()->registerClass(&LnSensor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnSensor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnSensor>, module, 0);
PythonQt::priv()->registerClass(&LnTrafficController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnTrafficController>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnTrafficController>, module, 0);
PythonQt::priv()->registerClass(&LnTurnout::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnTurnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnTurnout>, module, 0);
PythonQt::priv()->registerClass(&LocoAddress::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoAddress>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoAddress>, module, 0);
PythonQt::priv()->registerClass(&LocoNetInterface::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoNetInterface>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoNetInterface>, module, 0);
PythonQt::priv()->registerClass(&LocoNetMessage::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoNetMessage>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoNetMessage>, module, 0);
PythonQt::priv()->registerClass(&Manager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Manager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Manager>, module, 0);
PythonQt::priv()->registerClass(&MemoryManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_MemoryManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_MemoryManager>, module, 0);
PythonQt::priv()->registerClass(&NamedBean::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_NamedBean>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_NamedBean>, module, 0);
PythonQt::priv()->registerCPPClass("Positionable", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Positionable>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Positionable>, module, 0);
PythonQt::priv()->registerClass(&PowerManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_PowerManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_PowerManager>, module, 0);
PythonQt::priv()->registerClass(&ProgrammerManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ProgrammerManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProgrammerManager>, module, 0);
PythonQt::priv()->registerClass(&ProxyLightManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ProxyLightManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProxyLightManager>, module, 0);
PythonQt::priv()->registerClass(&ProxySensorManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ProxySensorManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProxySensorManager>, module, 0);
PythonQt::priv()->registerClass(&ProxyTurnoutManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ProxyTurnoutManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProxyTurnoutManager>, module, 0);
PythonQt::priv()->registerClass(&ReporterManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ReporterManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ReporterManager>, module, 0);
PythonQt::priv()->registerClass(&RfidSensorManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_RfidSensorManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_RfidSensorManager>, module, 0);
PythonQt::priv()->registerClass(&RouteManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_RouteManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_RouteManager>, module, 0);
PythonQt::priv()->registerClass(&Sensor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Sensor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Sensor>, module, 0);
PythonQt::priv()->registerClass(&SensorManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_SensorManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SensorManager>, module, 0);
PythonQt::priv()->registerClass(&ShutDownManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ShutDownManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ShutDownManager>, module, 0);
PythonQt::priv()->registerClass(&Siglet::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Siglet>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Siglet>, module, 0);
PythonQt::priv()->registerClass(&SignalHead::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_SignalHead>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SignalHead>, module, 0);
PythonQt::priv()->registerClass(&Throttle::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Throttle>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Throttle>, module, 0);
PythonQt::priv()->registerClass(&Turnout::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Turnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Turnout>, module, 0);


PythonQtRegisterListTemplateConverterForKnownClass(QList, QString);
PythonQtRegisterListTemplateConverterForKnownClass(QVector, QString);
}
