#ifndef ACTIONBLOCK_H
#define ACTIONBLOCK_H

#include "abstractdigitalaction.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "expressionnode.h"
#include "vetoablechangelistener.h"
#include "threadingutil.h"
#include "sensor.h"
#include "layoutblock.h"
#include "block.h"

class Block;
class ActionBlock : public AbstractDigitalAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  Q_INVOKABLE ActionBlock(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  /*enum*/class DirectOperation {
//      SetOccupied(Bundle.getMessage("ActionBlock_SetOccupied")),
//      SetNotOccupied(Bundle.getMessage("ActionBlock_SetNotOccupied")),
//      SetAltColorOn(Bundle.getMessage("ActionBlock_SetAltColorOn")),
//      SetAltColorOff(Bundle.getMessage("ActionBlock_SetAltColorOff")),
//      SetNullValue(Bundle.getMessage("ActionBlock_SetNullValue")),
//      SetValue(Bundle.getMessage("ActionBlock_SetValue"));
   public:
    enum TYPE {SetOccupied, SetNotOccupied, SetAltColorOn, SetAltColorOff, SetNullValue, SetValue};
    static QList<TYPE> values()
    {
     return QList<TYPE>{SetOccupied, SetNotOccupied, SetAltColorOn, SetAltColorOff, SetNullValue, SetValue};
    }
//      /*private*/ final String _text;

//      /*private*/ DirectOperation(String text) {
//          this._text = text;
//      }

      //@Override
      /*public*/ static QString toString(TYPE t) {
       switch (t) {
       case SetOccupied: return tr("Block Sensor Active");
       case SetNotOccupied: return tr("Block Sensor Inactive");
       case SetAltColorOn: return tr("Alternate Color On");
       case SetAltColorOff: return tr("Alternate Color Off");
       case SetNullValue: return tr("Empty (null)");
       case SetValue: return tr("Value");
       }
       throw IllegalArgumentException();
     }
    /*public*/ static TYPE valueOf(QString s)
    {
     if(s == tr("Block Sensor Active")) return SetOccupied;
     if(s == tr("Block Sensor Inactive"))return SetNotOccupied;
     if(s== tr("Alternate Color On")) return SetAltColorOn;
     if(s== tr("Alternate Color Off")) return SetAltColorOff;
     if(s== tr("Empty (null)")) return SetNullValue;
     if(s==tr("Value")) return SetValue;

     throw IllegalArgumentException();
    }
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
  /*public*/  void setBlock(/*@Nonnull*/ QString blockName) ;
  /*public*/  void setBlock(/*@Nonnull*/ Block* block) ;
  /*public*/  void setBlock(/*@Nonnull*/ NamedBeanHandle<Block*>* handle);
  /*public*/  void removeBlock();
  /*public*/  NamedBeanHandle<Block*>* getBlock();
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */;
  /*public*/  NamedBeanAddressing::TYPE getAddressing() ;
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable() ;
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */;
  /*public*/  QString getFormula();
  /*public*/  void setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getOperationAddressing();
  /*public*/  void setOperationDirect(DirectOperation::TYPE state);
  /*public*/  DirectOperation::TYPE getOperationDirect();
  /*public*/  void setOperationReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getOperationReference();
  /*public*/  void setOperationLocalVariable(/*@Nonnull*/ QString localVariable) ;
  /*public*/  QString getOperationLocalVariable() ;
  /*public*/  void setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getOperationFormula() ;
  /*public*/  void setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
  /*public*/  NamedBeanAddressing::TYPE getDataAddressing();
  /*public*/  void setDataReference(/*@Nonnull*/ QString reference) ;
  /*public*/  QString getDataReference() ;
  /*public*/  void setDataLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getDataLocalVariable();
  /*public*/  void setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException */;
  /*public*/  QString getDataFormula();
  /*public*/  void setBlockValue(/*@Nonnull*/ QString value);
  /*public*/  QString getBlockValue();
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;
  /*public*/  Category getCategory() override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
   AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
  }
  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) override {
   AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
  }
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
  ///*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Block*>* _blockHandle = nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;

  /*private*/ NamedBeanAddressing::TYPE _operationAddressing = NamedBeanAddressing::Direct;
  /*private*/ DirectOperation::TYPE _operationDirect = DirectOperation::SetOccupied;
  /*private*/ QString _operationReference = "";
  /*private*/ QString _operationLocalVariable = "";
  /*private*/ QString _operationFormula = "";
  /*private*/ ExpressionNode* _operationExpressionNode;

  /*private*/ NamedBeanAddressing::TYPE _dataAddressing = NamedBeanAddressing::Direct;
  /*private*/ QString _dataReference = "";
  /*private*/ QString _dataLocalVariable = "";
  /*private*/ QString _dataFormula = "";
  /*private*/ ExpressionNode* _dataExpressionNode;

  /*private*/ QString _blockValue = "";
  /*private*/ void parseFormula() /*throws ParserException */;
  /*private*/ void parseOperationFormula() /*throws ParserException*/;
  /*private*/ void parseDataFormula() /*throws ParserException*/ ;
  /*private*/ QString getNewOperation() /*throws JmriException*/;
  /*private*/ QString getNewData() /*throws JmriException*/;

  friend class ActionBlock_run;
};

class ActionBlock_run : /*public QObject,*/ public ThreadAction
{
  Q_OBJECT
  //Q_INTERFACES(ThreadAction)
  Sensor* sensor;
  LayoutBlock* lblk;
  ActionBlock* act;
  ActionBlock::DirectOperation::TYPE theOper;
  Block* block;
 public:
  ActionBlock_run(Block* block, ActionBlock::DirectOperation::TYPE theOper, ActionBlock* act) {this->block = block; this->act =act; this->theOper = theOper;}
  void run()
  {
   switch (theOper) {
      case ActionBlock::DirectOperation::SetOccupied:
          sensor = block->getSensor();
          if (sensor != nullptr) {
              try {
                  sensor->setKnownState(Sensor::ACTIVE);
              } catch (JmriException* ex) {
                  act->log->debug("Exception setting sensor active");
              }
          } else {
              throw new JmriException(tr("Block \"%1\" does not have sensor").arg(block->getDisplayName()));
          }
          break;
      case ActionBlock::DirectOperation::SetNotOccupied:
          sensor = block->getSensor();
          if (sensor != nullptr) {
              try {
                  sensor->setKnownState(Sensor::INACTIVE);
              } catch (JmriException* ex) {
                  act->log->debug("Exception setting sensor inactive");
              }
          } else {
              throw new JmriException(tr("Block \"%1\" does not have sensor").arg(block->getDisplayName()));
          }
          break;
      case ActionBlock::DirectOperation::SetAltColorOn:
          lblk = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(block);
          if (lblk != nullptr) {
              lblk->setUseExtraColor(true);
          } else {
              throw new JmriException(tr("Block \"%1\" does not have a related LayoutBlock").arg(block->getDisplayName()));
          }
          break;
      case ActionBlock::DirectOperation::SetAltColorOff:
          lblk = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(block);
          if (lblk != nullptr) {
              lblk->setUseExtraColor(false);
          } else {
              throw new JmriException(tr("Block \"%1\" does not have a related LayoutBlock").arg(block->getDisplayName()));
          }
          break;
      case ActionBlock::DirectOperation::SetNullValue:
          block->setValue(QVariant());
          break;
      case ActionBlock::DirectOperation::SetValue:
          block->setValue(act->getNewData());
          break;
      default:
          throw new IllegalArgumentException("invalid oper state: " + ActionBlock::DirectOperation::toString(theOper));
   }
  }
};

#endif // ACTIONBLOCK_H
