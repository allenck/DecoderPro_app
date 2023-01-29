#ifndef DIGITALBOOLEANONCHANGE_H
#define DIGITALBOOLEANONCHANGE_H

#include "abstractdigitalbooleanaction.h"
#include "femaledigitalactionsocket.h"
#include "femalesocketlistener.h"

class DigitalBooleanOnChange : public AbstractDigitalBooleanAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  /**
   * The trigger of Action.
   */
  /*public*/  /*enum*/class Trigger {
   public:
    enum TargetAction { CHANGE_TO_TRUE, CHANGE_TO_FALSE, CHANGE};
//        CHANGE_TO_TRUE(Bundle.getMessage("DigitalBooleanOnChange_Trigger_ChangeToTrue")),
//        CHANGE_TO_FALSE(Bundle.getMessage("DigitalBooleanOnChange_Trigger_ChangeToFalse")),
//        CHANGE(Bundle.getMessage("DigitalBooleanOnChange_Trigger_Change"));

//        private final String _text;

//        private Trigger(String text) {
//            this._text = text;
//        }
    /*public*/static QList<TargetAction> values() { return QList<TargetAction> {CHANGE_TO_TRUE, CHANGE_TO_FALSE, CHANGE};};

      //@Override
      /*public*/static  QString toString(TargetAction t) {
          switch(t){
          case CHANGE_TO_TRUE:
           return tr("On change to true");
          case CHANGE_TO_FALSE:
           return tr("On change to false");
          case CHANGE:
           return  tr("On change");
          default:
           return "?";
          }
      }
    static TargetAction toTargetAction(QString s)
    {
     if(s == tr("On change to true")) return CHANGE_TO_TRUE;
     if(s== tr("On change to false")) return CHANGE_TO_FALSE;
     if(s== tr("On change")) return CHANGE;
        throw new IllegalArgumentException(tr("%1 is not a valid Trigger target action").arg(s));
    }
  };

  explicit DigitalBooleanOnChange(QString sys, QString user, Trigger::TargetAction trigger, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException */override;
  /*public*/  Category getCategory()override;
  /*public*/  void execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/override;
  /*public*/  Trigger::TargetAction getTrigger();
  /*public*/  void setTrigger(Trigger::TargetAction trigger);
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale) override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleDigitalActionSocket* getSocket();
  /*public*/  QString getSocketSystemName() ;
  /*public*/  void setActionSocketSystemName(QString systemName);
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 private:
  /*private*/ QString _socketSystemName;
  /*private*/ /*final*/ FemaleDigitalActionSocket* _socket;
  Trigger::TargetAction _trigger = Trigger::CHANGE;
 static Logger* log;
};

#endif // DIGITALBOOLEANONCHANGE_H
