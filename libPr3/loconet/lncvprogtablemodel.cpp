#include "lncvprogtablemodel.h"
#include "loconetsystemconnectionmemo.h"
#include "roster.h"
#include "tablecolumnmodel.h"
#include "lncvdevicesmanager.h"
#include "tablecolumn.h"
#include "lncvdevice.h"
#include "decoderindexfile.h"
#include "instancemanager.h"
#include "exceptions.h"
#include "lncvdevices.h"
#include "joptionpane.h"
#include "decoderindexfile.h"
#include "paneopsprogframe.h"
#include "loggerfactory.h"
#include "jtable.h"
#include "lncvprogpane.h"

/**
 * Table model for the programmed LNCV Modules table.
 * See Sv2f Programing tool
 *
 * @author Egbert Broerse Copyright (C) 2020
 */
///*public*/ class LncvProgTableModel extends AbstractTableModel implements PropertyChangeListener, ProgrammingTool {


    LncvProgTableModel::LncvProgTableModel(LncvProgPane* pane, /*@Non""*/ LocoNetSystemConnectionMemo* memo, QObject* parent)
     : AbstractTableModel(parent)
    {
        this->pane = (QWidget*)pane;
        this->memo = memo;
        //pane->initComponents(memo);
        lncvdm = memo->getLncvDevicesManager();
        _roster = Roster::getDefault();
        lncvdm->addPropertyChangeListener((PropertyChangeListener*)this);
    }

    /*public*/ void LncvProgTableModel::initTable(JTable* lncvModulesTable) {
       TableColumnModel* assignmentColumnModel = lncvModulesTable->getColumnModel();
       TableColumn* idColumn = assignmentColumnModel->getColumn(0);
       idColumn->setMaxWidth(8);
    }

   //@Override
   /*public*/ QString LncvProgTableModel::getColumnName(int c) const {
       switch (c) {
           case ARTICLE_COLUMN:
               return tr("Article");
           case MODADDR_COLUMN:
               return tr("Address");
           case CV_COLUMN:
               return tr("CvLastRead");
           case VALUE_COLUMN:
               return tr("Value");
           case DEVICENAMECOLUMN:
               return tr("DeviceModel");
           case ROSTERENTRYCOLUMN:
               return tr("DeviceId");
           case OPENPRGMRBUTTONCOLUMN:
               return tr("Program");
           case COUNT_COLUMN:
           default:
               return "#";
       }
   }

   //@Override
   /*public*/ QString LncvProgTableModel::getColumnClass(int c) const {
       switch (c) {
           case COUNT_COLUMN:
           case ARTICLE_COLUMN:
           case MODADDR_COLUMN:
           case CV_COLUMN:
           case VALUE_COLUMN:
               return "Integer";
           case OPENPRGMRBUTTONCOLUMN:
               return "JButton";
           case DEVICENAMECOLUMN:
           case ROSTERENTRYCOLUMN:
           default:
               return "String";
       }
   }

   //@Override
   /*public*/ bool LncvProgTableModel::isCellEditable(int r, int c) const {
       return (c == OPENPRGMRBUTTONCOLUMN);
   }

   //@Override
   /*public*/ int LncvProgTableModel::getColumnCount() const {
      return NUMCOLUMNS;
   }

   //@Override
   /*public*/ int LncvProgTableModel::getRowCount() const {
        if (lncvdm == nullptr) {
            return 0;
        } else {
            return lncvdm->getDeviceCount();
        }
   }

   //@Override
   /*public*/ QVariant LncvProgTableModel::getValueAt(int r, int c) const{
       LncvDevice* dev = memo->getLncvDevicesManager()->getDeviceList()->getDevice(r);
       try {
          switch (c) {
              case ARTICLE_COLUMN:
                  //assert dev != "";
                  return dev->getProductID();
              case MODADDR_COLUMN:
                  //assert dev != "";
                  return dev->getDestAddr();
              case CV_COLUMN:
                  //assert dev != "";
                  return dev->getCvNum();
              case VALUE_COLUMN:
                  //assert dev != "";
                  return dev->getCvValue();
              case DEVICENAMECOLUMN:
                  //assert dev != "";
                  if (dev->getDeviceName().length() == 0) { // not yet filled in, look for a candidate
                      QList<DecoderFile*> l =
                          ((DecoderIndexFile*)InstanceManager::getDefault(
                              "DecoderIndexFile"))->
                              matchingDecoderList(
                                      "",
                                      "",
                                      "",
                                      "",
                                      QString::number(dev->getProductID()), // a bit risky to check just 1 value
                                      "",
                                      "",
                                      "",
                                      ""
                              );
                      //log.debug("found {} possible decoder matches for LNCV device", l.size());
                      QString lastModelName = "";
                      if (l.size() > 0) {
                          for (DecoderFile* d : l) {
                              if (d->getModel() == ("")) {
                                  log->warn(tr("Empty model(name) in decoderfile %1").arg(d->getFileName()));
                              }
                              lastModelName = d->getModel();
                          }
                          dev->setDevName(lastModelName);
                          dev->setDecoderFile(l.at(l.size() - 1));
                      }
                      return lastModelName;
                  }
                  return dev->getDeviceName();
              case ROSTERENTRYCOLUMN:
                  //assert dev != "";
                  return dev->getRosterName();
              case OPENPRGMRBUTTONCOLUMN:
                  //assert dev != "";
                  if (dev->getDeviceName().length() != 0) {
                      if ((dev->getRosterName() != "") && (dev->getRosterName().length() == 0)) {
                          return tr("Create Roster Entry");
                      }
                      return tr("Program");
                  }
                  return tr("No Match in Roster");
              default: // column 1
                 return r + 1;
          }
      } catch (NullPointerException npe) {
        log->warn(tr("Caught NPE reading Module %1").arg(r));
        return "";
      }
   }

    //@Override
    /*public*/ void LncvProgTableModel::setValueAt(QVariant value, int r, int c) {
        if (getRowCount() < r + 1) {
            // prevent update of a row that does not (yet) exist
            return;
        }
        LncvDevice* dev = memo->getLncvDevicesManager()->getDeviceList()->getDevice(r);
        if (c == OPENPRGMRBUTTONCOLUMN) {
            if (( getValueAt(r, c).toString())==(tr("Create Roster Entry")) == 0) {
                createRosterEntry(dev);
                if (dev->getRosterEntry() != nullptr) {
                    setValueAt(dev->getRosterName(), r, c);
                } else {
                    log->warn(tr("Failed to connect RosterEntry to device %1").arg(dev->getRosterName()));
                }
            } else if (( getValueAt(r, c).toString()).compare(tr("Program")) == 0) {
                openProgrammer(r);
            }
        } else {
            // no change, so do not fire a property change event
            return;
        }
        if (getRowCount() >= 1) {
            this->fireTableRowsUpdated(r, r);
        }
    }

    /*private*/ void LncvProgTableModel::openProgrammer(int r) {
        LncvDevice* dev = memo->getLncvDevicesManager()->getDeviceList()->getDevice(r);

        LncvDevicesManager::ProgrammingResult result = lncvdm->prepareForSymbolicProgrammer(dev, this);
        switch (result) {
            case LncvDevicesManager::SUCCESS_PROGRAMMER_OPENED:
                return;
            case LncvDevicesManager::FAIL_NO_SUCH_DEVICE:
                JOptionPane::showMessageDialog(pane,
                        tr("Re-try the 'Device Discovery' process and try again.\nCannot open the programmer."),
                        tr("Open RosterEntry"), JOptionPane::ERROR_MESSAGE);
                return;
            case LncvDevicesManager::FAIL_NO_APPROPRIATE_PROGRAMMER:
                JOptionPane::showMessageDialog(pane,
                        tr("No suitable programmer available for this LocoNet connection.\nCannot open the programmer."),
                        tr("Open RosterEntry"), JOptionPane::ERROR_MESSAGE);
                return;
            case LncvDevicesManager::FAIL_NO_MATCHING_ROSTER_ENTRY:
                JOptionPane::showMessageDialog(pane,
                        tr("There does not appear to be a roster entry for this device.\nannot open the programmer."),
                        tr("Open RosterEntry"), JOptionPane::ERROR_MESSAGE);
                return;
            case LncvDevicesManager::FAIL_DESTINATION_ADDRESS_IS_ZERO:
                JOptionPane::showMessageDialog(pane,
                        tr("Device is at address 0.\nRe-configure device address to a non-zero value before programming!\nCanceling operation."),
                        tr("Open RosterEntry"), JOptionPane::ERROR_MESSAGE);
                return;
            case LncvDevicesManager::FAIL_MULTIPLE_DEVICES_SAME_DESTINATION_ADDRESS:
                JOptionPane::showMessageDialog(pane,
                        tr("Should not program as there are multiple devices with device address %1 present on LocoNet.\nCanceling operation.").arg(dev->getDestAddr()),
                        tr("Open RosterEntry"), JOptionPane::ERROR_MESSAGE);
                return;
            case LncvDevicesManager::FAIL_NO_ADDRESSED_PROGRAMMER:
                JOptionPane::showMessageDialog(pane,
                        tr("No addressed programmer available for this LocoNet connection./nCannot open the programmer."),
                        tr("Open RosterEntry"), JOptionPane::ERROR_MESSAGE);
                return;
            case LncvDevicesManager::FAIL_NO_LNCV_PROGRAMMER:
                JOptionPane::showMessageDialog(pane,
                        tr("LNCV programming mode is not available on this connection.\nCannot open the programmer."),
                        tr("Open RosterEntry"), JOptionPane::ERROR_MESSAGE);
                return;
            default:
                JOptionPane::showMessageDialog(pane,
                        tr("An unknown error occurred.\nCannot open the programmer."),
                        tr("Open RosterEntry"), JOptionPane::ERROR_MESSAGE);
        }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void LncvProgTableModel::openPaneOpsProgFrame(RosterEntry* re, QString name,
                                     QString programmerFile, Programmer* p) {
        // would be better if this was a new task on the GUI thread...
        log->debug(tr("attempting to open programmer, re=%1, name=%2, programmerFile=%3, programmer=%4").arg(
                re->getDisplayName()).arg(name).arg(programmerFile).arg(p->self()->objectName()));

        DecoderFile* decoderFile = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->fileFromTitle(re->getDecoderModel());

        PaneOpsProgFrame* progFrame =
                new PaneOpsProgFrame(decoderFile, re, name, programmerFile, p);

        progFrame->pack();
        progFrame->setVisible(true);
    }

    /*private*/ void LncvProgTableModel::createRosterEntry(LncvDevice* dev) {
        if (dev->getDestAddr() == 0) {
            JOptionPane::showMessageDialog(pane,
                    tr("Cannot create a roster entry when the destination address is 0.\nCanceling operation."),
                    tr("Create Roster Entry"), JOptionPane::ERROR_MESSAGE);
        } else {
            QString s = "";
            while (s == "") {
                s = JOptionPane::showInputDialog(pane,
                        tr("Enter a name for the roster entry:"), "");
                if (s == "") {
                    // cancel button hit
                    return;
                }
            }

            RosterEntry* re = new RosterEntry(dev->getDecoderFile()->getFileName());
            re->setDccAddress(QString::number(dev->getDestAddr()));
            re->setDecoderModel(dev->getDecoderFile()->getModel());
            re->setProductID(QString::number(dev->getProductID()));
            re->setId(s);
            _roster->addEntry(re);
            dev->setRosterEntry(re);
        }
    }

    /*
     * Process the "property change" events from LncvDevicesManager.
     *
     * @param evt event
     */
    //@Override
    /*public*/ void LncvProgTableModel::propertyChange(PropertyChangeEvent* evt) {
        // these messages can arrive without a complete
        // GUI, in which case we just ignore them
        //String eventName = evt.getPropertyName();
        /* always use fireTableDataChanged() because it does not always
            resize columns to "preferred" widths!
            This may slow things down, but that is a small price to pay!
        */
        fireTableDataChanged();
    }

    /*public*/ void LncvProgTableModel::dispose() {
        if ((memo != nullptr) && (memo->getLncvDevicesManager() != nullptr)) {
            memo->getLncvDevicesManager()->removePropertyChangeListener((PropertyChangeListener*)this);
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* LncvProgTableModel::log = LoggerFactory::getLogger("LncvProgTableModel");
