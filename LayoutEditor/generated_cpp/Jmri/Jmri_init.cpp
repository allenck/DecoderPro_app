#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "Jmri0.h"
#include "Jmri1.h"
#include "Jmri2.h"



void PythonQt_init_Jmri(PyObject* module) {
PythonQt::priv()->registerClass(&AbstractAutomaton::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractAutomaton>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractAutomaton>, module, 0);
PythonQt::priv()->registerClass(&AbstractNamedBean::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractNamedBean>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractNamedBean>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&AbstractPortController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractPortController>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractPortController>, module, 0);
PythonQt::priv()->registerClass(&AbstractSensor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractSensor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractSensor>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&AbstractSerialPortController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractSerialPortController>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractSerialPortController>, module, 0);
PythonQt::priv()->registerClass(&AbstractShutDownTask::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractShutDownTask>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractShutDownTask>, module, 0);
PythonQt::priv()->registerClass(&AbstractTurnout::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AbstractTurnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AbstractTurnout>, module, 0);
PythonQt::priv()->registerClass(&Audio::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Audio>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Audio>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&AudioBuffer::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioBuffer>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioBuffer>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&AudioListener::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioListener>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioListener>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&AudioSource::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_AudioSource>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_AudioSource>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("BasicRosterEntry", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_BasicRosterEntry>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_BasicRosterEntry>, module, 0);
PythonQt::priv()->registerCPPClass("BeanInterface", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_BeanInterface>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_BeanInterface>, module, 0);
PythonQt::priv()->registerClass(&BeanTableDataModel::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_BeanTableDataModel>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_BeanTableDataModel>, module, 0);
PythonQt::priv()->registerClass(&BeanTableFrame::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_BeanTableFrame>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_BeanTableFrame>, module, 0);
PythonQt::priv()->registerClass(&BeanTableModel::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_BeanTableModel>, NULL, module, 0);
PythonQt::priv()->registerClass(&Block::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Block>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Block>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&ControlPanelEditor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ControlPanelEditor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ControlPanelEditor>, module, 0);
PythonQt::priv()->registerClass(&DccLocoAddress::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_DccLocoAddress>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_DccLocoAddress>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("DccThrottle", "Throttle", "Jmri", PythonQtCreateObject<PythonQtWrapper_DccThrottle>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_DccThrottle>, module, 0);
PythonQt::priv()->registerClass(&DefaultProgrammerManager::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_DefaultProgrammerManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_DefaultProgrammerManager>, module, 0);
PythonQt::priv()->registerClass(&EditScene::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_EditScene>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_EditScene>, module, 0);
PythonQt::priv()->registerClass(&EventObject::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_EventObject>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_EventObject>, module, 0);
PythonQt::priv()->registerClass(&FileUtil::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_FileUtil>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_FileUtil>, module, 0);
PythonQt::priv()->registerClass(&FlowLayout::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_FlowLayout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_FlowLayout>, module, PythonQt::Type_NonZero);
PythonQt::priv()->registerClass(&JFrame::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_JFrame>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_JFrame>, module, 0);
PythonQt::priv()->registerClass(&JFrameItem::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_JFrameItem>, NULL, module, 0);
PythonQt::priv()->registerClass(&JLabel::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_JLabel>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_JLabel>, module, 0);
PythonQt::priv()->registerClass(&JList::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_JList>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_JList>, module, 0);
PythonQt::priv()->registerClass(&JTable::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_JTable>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_JTable>, module, 0);
PythonQt::priv()->registerClass(&JTextArea::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_JTextArea>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_JTextArea>, module, 0);
PythonQt::priv()->registerClass(&JmriJFrame::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_JmriJFrame>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_JmriJFrame>, module, 0);
PythonQt::priv()->registerClass(&LayoutEditor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LayoutEditor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LayoutEditor>, module, 0);
PythonQt::priv()->registerClass(&LayoutTurnout::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LayoutTurnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LayoutTurnout>, module, 0);
PythonQt::priv()->registerCPPClass("ListSelectionModel", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_ListSelectionModel>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ListSelectionModel>, module, 0);
PythonQt::priv()->registerClass(&LnCommandStationType::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnCommandStationType>, NULL, module, 0);
PythonQt::priv()->registerClass(&LnPacketizer::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnPacketizer>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnPacketizer>, module, 0);
PythonQt::priv()->registerClass(&LnPortController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnPortController>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnPortController>, module, 0);
PythonQt::priv()->registerClass(&LnSensor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnSensor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnSensor>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&LnTrafficController::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnTrafficController>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnTrafficController>, module, 0);
PythonQt::priv()->registerClass(&LnTurnout::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LnTurnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LnTurnout>, module, 0);
PythonQt::priv()->registerClass(&LocoAddress::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoAddress>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoAddress>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&LocoNetInterface::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoNetInterface>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoNetInterface>, module, 0);
PythonQt::priv()->registerClass(&LocoNetMessage::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoNetMessage>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoNetMessage>, module, 0);
PythonQt::priv()->registerClass(&LocoNetSystemConnectionMemo::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_LocoNetSystemConnectionMemo>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_LocoNetSystemConnectionMemo>, module, 0);
PythonQt::priv()->registerClass(&Logger::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Logger>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Logger>, module, 0);
PythonQt::priv()->registerClass(&MultiIconEditor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_MultiIconEditor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_MultiIconEditor>, module, 0);
PythonQt::priv()->registerCPPClass("MyGraphicsItemGroup", "QGraphicsItemGroup", "Jmri", PythonQtCreateObject<PythonQtWrapper_MyGraphicsItemGroup>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_MyGraphicsItemGroup>, module, 0);
PythonQt::priv()->registerCPPClass("NamedBean", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_NamedBean>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_NamedBean>, module, 0);
PythonQt::priv()->registerClass(&NetworkPortAdapter::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_NetworkPortAdapter>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_NetworkPortAdapter>, module, 0);
PythonQt::priv()->registerClass(&PanelEditor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_PanelEditor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_PanelEditor>, module, 0);
PythonQt::priv()->registerClass(&PanelMenu::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_PanelMenu>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_PanelMenu>, module, PythonQt::Type_NonZero);
PythonQt::priv()->registerClass(&PortAdapter::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_PortAdapter>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_PortAdapter>, module, 0);
PythonQt::priv()->registerCPPClass("Positionable", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Positionable>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Positionable>, module, 0);
PythonQt::priv()->registerClass(&PositionableLabel::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_PositionableLabel>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_PositionableLabel>, module, 0);
PythonQt::priv()->registerCPPClass("ProgListener", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_ProgListener>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProgListener>, module, 0);
PythonQt::priv()->registerClass(&ProgrammingMode::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ProgrammingMode>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ProgrammingMode>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&PropertyChangeEvent::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_PropertyChangeEvent>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_PropertyChangeEvent>, module, 0);
PythonQt::priv()->registerCPPClass("PropertyChangeListener", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_PropertyChangeListener>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_PropertyChangeListener>, module, 0);
PythonQt::priv()->registerClass(&PropertyChangeSupport::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_PropertyChangeSupport>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_PropertyChangeSupport>, module, 0);
PythonQt::priv()->registerClass(&Roster::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Roster>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Roster>, module, 0);
PythonQt::priv()->registerClass(&RosterEntry::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_RosterEntry>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_RosterEntry>, module, 0);
PythonQt::priv()->registerCPPClass("RosterObject", "BeanInterface", "Jmri", PythonQtCreateObject<PythonQtWrapper_RosterObject>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_RosterObject>, module, 0);
PythonQt::priv()->registerClass(&Sensor::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Sensor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Sensor>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&SerialPortAdapter::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_SerialPortAdapter>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SerialPortAdapter>, module, 0);
PythonQt::priv()->registerClass(&ShutDownTask::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_ShutDownTask>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_ShutDownTask>, module, 0);
PythonQt::priv()->registerClass(&Siglet::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Siglet>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Siglet>, module, 0);
PythonQt::priv()->registerClass(&SignalHead::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_SignalHead>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SignalHead>, module, 0);
PythonQt::priv()->registerCPPClass("Sound", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Sound>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Sound>, module, 0);
PythonQt::priv()->registerClass(&SystemConnectionMemo::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_SystemConnectionMemo>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SystemConnectionMemo>, module, 0);
PythonQt::priv()->registerCPPClass("TableCellEditor", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_TableCellEditor>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_TableCellEditor>, module, 0);
PythonQt::priv()->registerClass(&TableColumn::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_TableColumn>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_TableColumn>, module, 0);
PythonQt::priv()->registerCPPClass("TableColumnModel", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_TableColumnModel>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_TableColumnModel>, module, 0);
PythonQt::priv()->registerCPPClass("Throttle", "", "Jmri", PythonQtCreateObject<PythonQtWrapper_Throttle>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Throttle>, module, 0);
PythonQt::priv()->registerClass(&Turnout::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_Turnout>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_Turnout>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerClass(&TurnoutOperation::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_TurnoutOperation>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_TurnoutOperation>, module, 0);
PythonQt::priv()->registerClass(&VetoableChangeSupport::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_VetoableChangeSupport>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_VetoableChangeSupport>, module, 0);
PythonQt::priv()->registerClass(&WindowInterface::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_WindowInterface>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_WindowInterface>, module, 0);
PythonQt::priv()->registerClass(&WindowListener::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_WindowListener>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_WindowListener>, module, 0);
PythonQt::priv()->registerClass(&XmlFile::staticMetaObject, "Jmri", PythonQtCreateObject<PythonQtWrapper_XmlFile>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_XmlFile>, module, 0);


PythonQtRegisterListTemplateConverterForKnownClass(QList, QModelIndex);
PythonQtRegisterListTemplateConverterForKnownClass(QList, QString);
PythonQtRegisterListTemplateConverterForKnownClass(QList, QTextEdit::ExtraSelection);
PythonQtRegisterListTemplateConverterForKnownClass(QVector, QString);
}
