#ifndef SLIPICONADDDER_H
#define SLIPICONADDDER_H
#include "iconadder.h"
#include "namedbeanhandle.h"
#include "actionlistener.h"
#include "multisensoriconadder.h"
#include "dataflavor.h"
#include "transferhandler.h"
#include "transferable.h"
#include <QDebug>
#include "instancemanager.h"
#include "droptarget.h"

class Transferable;
class DataFlavor;
class DropPanel;
class QRadioButton;
class Turnout;
class SlipIconAdder : public IconAdder
{
    Q_OBJECT
public:
    explicit SlipIconAdder(QWidget *parent = 0);
    ~SlipIconAdder();
/*public*/ static /*final*/ QString NamedBeanFlavorMime;
    /*public*/ SlipIconAdder(QString type, QWidget *parent = 0);
    /*public*/ void setTurnoutType(int dblSlip);
    /*public*/ int getTurnoutType();
    /*public*/ void reset();
    /*public*/ void makeIconPanel(bool useDefaults);
    /*public*/ void complete(ActionListener* addIconAction, bool changeIconAction, bool addToTable, bool update);
    /*public*/ void valueChanged(ListSelectionEvent* e);
    /*public*/ NamedIcon* getIcon(int index);
    /*public*/ NamedIcon*  getIcon(QString key);
    /*public*/ NamedBeanHandle<Turnout*>* getTurnout(QString index);
    /*public*/ void setTurnout(QString key, NamedBeanHandle<Turnout*>* turnout);
    void updateSingleSlipRoute(bool single);
    /*public*/ void setSingleSlipRoute(bool single);
    /*public*/ bool getSingleSlipRoute();
    class ExportHandler : public TransferHandler
    {
        IconAdder* parent;
    public:
        ExportHandler(SlipIconAdder* parent)
        {
         this->parent = parent;
        }

        /*public*/ int getSourceActions(QWidget* /*c*/)
        {
            return COPY;
        }
        /*public*/ Transferable* createTransferable( QWidget* /*c*/) {
            return new MultiSensorIconAdder::TransferableNamedBean(parent);
        }
        /*public*/ void exportDone(QWidget* /*c*/, Transferable* /*t*/, int /*action*/) {
        }
    };
    /**
    *  Enables the active Slip icons to receive dragged icons
    */
    class DropPanel : public QFrame /*implements DropTargetListener*/
    {
     DataFlavor* dataFlavor;
     SlipIconAdder* iconAdder;
     QString key;
    public:
      DropPanel (SlipIconAdder* iconAdder)
      {
       this->key = key;
       this->iconAdder = iconAdder;
       setAcceptDrops(true);
       try {
        dataFlavor = new DataFlavor(MultiSensorIconAdder::NamedBeanFlavorMime);
       }
       catch (ClassNotFoundException cnfe)
       {
        //cnfe.printStackTrace();
       }
       //new DropTarget(this, DnDConstants.ACTION_COPY_OR_MOVE, this);
            //if (log.isDebugEnabled()) log.debug("DropPanel ctor");
      }
      void setKey(QString key) {this->key = key;}
    //  /*public*/ void dragExit(DropTargetEvent dte)
    //  {
    //  }
    //    /*public*/ void dragEnter(DropTargetDragEvent dtde) {
    //    }
      /*public*/ void dragEnterEvent(QDragEnterEvent *e)
      {
          // Set the drop action to be the proposed action.
          e->acceptProposedAction();
      }

    //    /*public*/ void dragOver(DropTargetDragEvent dtde) {
    //        //if (log.isDebugEnabled()) log.debug("DropPanel.dragOver");
    //    }
      void dragMoveEvent(QDragMoveEvent *de)
      {
       // The event needs to be accepted here
       if(!de->mimeData()->text().isEmpty())
        de->accept();
      }
    //    /*public*/ void dropActionChanged(DropTargetDragEvent dtde) {
    //    }
    //    /*public*/ void drop(DropTargetDropEvent e) {
    //        try {
    //            Transferable tr = e.getTransferable();
    //            if(e.isDataFlavorSupported(dataFlavor)) {
    //                Turnout turnout = (Turnout)tr.getTransferData(dataFlavor);
    //                if (turnout !=NULL) {
    //                    e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
    //                    DropTarget target = (DropTarget)e.getSource();
    //                    JPanel panel = (JPanel)target.getComponent();
    //                    JComponent comp = (JLabel)panel.getComponent(0);
    //                    if (putTurnout(comp.getName(), turnout)) {
    //                        makeIconPanel(true);
    //                    }
    //                    e.dropComplete(true);
    //                    if (log.isDebugEnabled()) log.debug("DropPanel.drop COMPLETED for "+
    //                                                         comp.getName());
    //                    return;
    //                } else {
    //                    if (log.isDebugEnabled()) log.debug("DropPanel.drop REJECTED!");
    //                    e.rejectDrop();
    //                }
    //            }
    //        } catch(IOException ioe) {
    //            if (log.isDebugEnabled()) log.debug("DropPanel.drop REJECTED!");
    //            e.rejectDrop();
    //        } catch(UnsupportedFlavorException ufe) {
    //            if (log.isDebugEnabled()) log.debug("DropPanel.drop REJECTED!");
    //            e.rejectDrop();
    //        }
    //    }
      /*public*/ void dropEvent(QDropEvent *e)
      {
       QString text = e->mimeData()->text().toLatin1();
       qDebug() << text;
       Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(text);
       if (iconAdder->putTurnout(key, turnout))
       {
        iconAdder-> makeIconPanel(true);
       }
      }
    };

signals:

public slots:
    void slipUpdate(int slip);
    void changeNumScissorTurnouts();

private:
    /*private*/ void common();
    QMap <QString, NamedBeanHandle<Turnout*>*>* _turnoutMap;// = new QMap <QString, NamedBeanHandle<Turnout*>*>();
    int _lastIndex;// = 0;
    int doubleSlip;// = 0x00;
    QRadioButton* doubleSlipButton;// = new JRadioButton(Bundle.getMessage("DoubleSlip"));
    QRadioButton* singleSlipButton;// = new JRadioButton(Bundle.getMessage("SingleSlip"));
    QRadioButton* threeWayButton;// = new JRadioButton(Bundle.getMessage("ThreeWay"));
    QRadioButton* scissorButton;// = new JRadioButton(Bundle.getMessage("Scissor"));

    QRadioButton* singleDirection;// = new JRadioButton(Bundle.getMessage("SingleSlipRoute"));
    QRadioButton* lowerWestToLowerEastButton;// = new JRadioButton(Bundle.getMessage("LowerWestToLowerEast"));
    QRadioButton* upperWestToUpperEastButton;// = new JRadioButton(Bundle.getMessage("UpperWestToUpperEast"));
    void _delete(int index);
    Logger* log;
    /*private*/ bool putTurnout(QString key, Turnout* turnout);
};

#endif // SLIPICONADDDER_H
