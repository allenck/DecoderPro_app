#ifndef MULTISENSORICONADDER_H
#define MULTISENSORICONADDER_H
#include "iconadder.h"
#include "namedbeanhandle.h"
#include "multisensoricon.h"
#include "transferhandler.h"
#include "transferable.h"
#include <QVariant>
#include "dataflavor.h"
#include "dndconstants.h"
#include "actionlistener.h"
#include "droptargetlistener.h"
#include "droptarget.h"
#include "component.h"
#include "instancemanager.h"
#include "proxysensormanager.h"

class MultiSensorIcon;
class CatalogTreeNode;
class QRadioButton;
class Sensor;
class MultiSensorIconAdder : public IconAdder
{
    Q_OBJECT
public:
    explicit MultiSensorIconAdder(QString s = "", QWidget *parent = 0);
    /*public*/ void reset();
    void setMultiIcon(QList <MultiSensorIcon::Entry*>* icons);
    /*public*/ void complete(ActionListener* addIconAction, bool changeIcon, bool addToTable, bool update);
    void _delete(QString key);
    /*public*/ NamedIcon* getIcon(int index);
    /*public*/ NamedBeanHandle<Sensor*>* getSensor(int index);
    /*public*/ bool getUpDown();
    /*public*/ static /*final*/ QString NamedBeanFlavorMime;// = DataFlavor.javaJVMLocalObjectMimeType +
//               ";class=jmri.NamedBean";

    class ExportHandler : public TransferHandler
    {
        MultiSensorIconAdder* parent;
    public:
        ExportHandler(MultiSensorIconAdder* parent)
        {
         this->parent = parent;
        }

        /*public*/ int getSourceActions(QWidget* /*c*/) {
            return TransferHandler::COPY;
        }
        /*public*/ Transferable* createTransferable(QWidget* /*c*/) {
            return new TransferableNamedBean(parent);
        }
        /*public*/ void exportDone(QWidget* /*c*/, Transferable* /*t*/, int /*action*/)
        {
        }
    };

    class TransferableNamedBean : public  Transferable
    {
        DataFlavor* dataFlavor;
        Logger* log;
        IconAdder* parent;
    public:
        TransferableNamedBean(IconAdder* parent)
        {
            this->parent = parent;
            log = new Logger("TransferableNamedBean");
            try {
                dataFlavor = new DataFlavor(NamedBeanFlavorMime);
            } catch (ClassNotFoundException cnfe) {
//                cnfe.printStackTrace();
            }
        }
        /*public*/ QVector<DataFlavor*>* getTransferDataFlavors() {
            //if (log.isDebugEnabled()) log.debug("TransferableNamedBean.getTransferDataFlavors ");
            QVector<DataFlavor*>* vector = new QVector<DataFlavor*>();
            vector->append( dataFlavor );
            return vector;
        }
        /*public*/ bool isDataFlavorSupported(DataFlavor* flavor) {
            //if (log.isDebugEnabled()) log.debug("TransferableNamedBean.isDataFlavorSupported ");
            return dataFlavor==(flavor);
        }
        /*public*/ NamedBean* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) {
            if (log->isDebugEnabled()) log->debug("TransferableNamedBean.getTransferData ");
            if (isDataFlavorSupported(flavor)) {
                return parent->getTableSelection();
            }
            return NULL;
        }
    };

    /**
    *  Enables the active MultiSensor icons to receive dragged icons
    */
    class DropPanel : public  QWidget
    {
     //Q_OBJECT

     DataFlavor* dataFlavor;
     Logger* log;
     MultiSensorIconAdder* multiSensorIconAddr;
     QWidget* comp;

    public:
     DropPanel (MultiSensorIconAdder* multiSensorIconAddr, QWidget* parent = 0) : QWidget(parent)
     {
      log = new Logger("DropPanel");
      log->setDebugEnabled(multiSensorIconAddr->log->isDebugEnabled());
      this->multiSensorIconAddr = multiSensorIconAddr;
      try
      {
       dataFlavor = new DataFlavor(MultiSensorIconAdder::NamedBeanFlavorMime);
      }
      catch (ClassNotFoundException cnfe)
      {
                //cnfe.printStackT(race();
      }
//      Component* comp = new Component();
//      DropTargetListener* dtl = new DropTargetListener();
//      new DropTarget(comp, DnDConstants::ACTION_COPY_OR_MOVE, dtl);
      if(log-> isDebugEnabled()) log-> debug("DropPanel ctor");
      setAcceptDrops(true);
     }
    //    /*public*/ void dragExit(DropTargetEvent dte) {
    //    }
    //    /*public*/ void dragEnter(DropTargetDragEvent dtde) {
     /*public*/ void dragEnterEvent(QDragEnterEvent *event)
     {
      if (log->isDebugEnabled()) log->debug("DropJLabel.dragEnter ");
      event->acceptProposedAction();
     }
    //    /*public*/ void dragOver(DropTargetDragEvent dtde) {
     /*public*/ void dragMoveEvent(QDragMoveEvent * de)
     {
      if (log-> isDebugEnabled()) log-> debug("DropPanel.dragOver");
      if(!de->mimeData()->text().isEmpty())
       de->accept();
     }
    //    /*public*/ void dropActionChanged(DropTargetDragEvent dtde) {
    //    }
    //    /*public*/ void drop(DropTargetDropEvent e) {
     /*public*/ void dropEvent(QDropEvent * e)
     {
      const QMimeData* mimeData = e->mimeData();
      QString text = mimeData->text();
//      if(text.startsWith("DataFlavor"))
//      {
//       QString mimeText = text.mid(11+9, text.length()-12 -9);
//       dataFlavor = new DataFlavor(mimeText);
//      try
//      {

//       Transferable* tr = e->getTransferable();
//       if(e->isDataFlavorSupported(dataFlavor))
//       {
//        Sensor* sensor = (Sensor*)tr.getTransferData(dataFlavor);
       Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(text);
        if (sensor !=NULL)
        {
         //e->acceptDrop(DnDConstants::ACTION_COPY_OR_MOVE);
         e->accept();
//         DropTarget* target = (DropTarget)e->getSource();
//         QWidget* panel = (QWidget*)target->getComponent();
//         QWidget* comp = (JLabel*)panel->getComponent(0);
//          if (multiSensorIconAddr->putSensor(((JLabel*)comp)->getName(), sensor))
//          {
//           multiSensorIconAddr->makeIconPanel(!multiSensorIconAddr->_update);
//          }
         QObjectList ol = children();
         foreach (QObject* o, ol)
         {
          if(o->objectName() == "key")
          {
           QString key = ((QLabel*)o)->text();
           multiSensorIconAddr->_sensorMap->remove(key);
           multiSensorIconAddr->_sensorMap->insert(key, new NamedBeanHandle<Sensor*>(text,sensor));
          }
          if(o->objectName() == "SensorName")
          {
           comp = (QWidget*)o;
           ((QLabel*)comp)->setText(text);
          }
         }
          //e->dropComplete(true);
         if (log-> isDebugEnabled()) log-> debug("DropPanel.drop COMPLETED for "+
                                              ((QLabel*)comp)->text());
         return;
        }
//        }
        else
        {
         if (log-> isDebugEnabled()) log-> debug("DropPanel.drop REJECTED!");
         //e->rejectDrop();
        }
//       }
//      } catch(IOException ioe) {
//          if (log-> isDebugEnabled()) log-> debug("DropPanel.drop REJECTED!");
//          e->rejectDrop();
//      } catch(UnsupportedFlavorException ufe) {
//          if (log-> isDebugEnabled()) log-> debug("DropPanel.drop REJECTED!");
//          e->rejectDrop();
//      }
     }
    };

    class DeleteActionListener : public ActionListener
    {
     //Q_OBJECT
       MultiSensorIconAdder* parent;
     QString key;
     public:
     /*public*/ void actionPerformed(JActionEvent* a = 0)
     {
      Q_UNUSED(a);
      parent->_delete(key);
     }
     DeleteActionListener* init(QString k,  MultiSensorIconAdder* parent)
     {
      this->parent = parent;
      key = k;
      return this;
     }
    };
signals:

public slots:
    /*public*/ void valueChanged(/*ListSelectionEvent e*/);

private:
    QRadioButton* _updown;
    QRadioButton* _rightleft;

   QMap <QString, NamedBeanHandle<Sensor*>*>* _sensorMap;// = new QMap <QString, NamedBeanHandle<Sensor*>*>();
   /*private*/ bool putSensor(QString key, Sensor* sensor);
   Logger* log;
private slots:
   /*private*/ void addIcon();

protected:
   /*protected*/ void makeIcons(CatalogTreeNode* n);
   /*protected*/ void doIconPanel();

};

#endif // MULTISENSORICONADDER_H
