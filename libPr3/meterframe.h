#ifndef METERFRAME_H
#define METERFRAME_H
#include "jmrijframe.h"
#include "namedicon.h"
#include <QUuid>
#include "jlabel.h"
#include "manager.h"
#include "abstractaction.h"
#include <QMetaEnum>

class SelectMeterAction;
class Meter;
class MeterFrame : public JmriJFrame
{
  Q_OBJECT
 public:
  class Unit
  {
   public:
   /*public*/ enum UNITS {
       Percent, //1.0),    // Not a unit, but here anyway
       MicroVolt, //1000*1000),
       MilliVolt, //1000),
       Volt, //1.0),
       KiloVolt, //1/1000.0),
       MicroAmpere, //1000*1000),
       MilliAmpere, //1000),
       Ampere, //1.0),
       KiloAmpere //1/1000.0);
    };
    //Q_ENUM(UNITS)
    /*public*/ static QMap<UNITS, Unit>* values;
    /*public*/ static QMap<UNITS, double>* factors;
    /*public*/ static QMap<UNITS, QString>* names;
    Unit() {}
private:
      /*private*/ /*final*/ double multiply;
      QString name;
      UNITS u;
//      /*private*/ Unit(UNITS u, QString name, double m)
//      {
//       multiply = m;
//       this->name = name;
//       this->u = u;
//      }
      /*private*/ Unit(UNITS u)
      {
       switch(u)
       {
        case Percent:
         multiply = 1.0;    // Not a unit, but here anyway
         name = "Percent";
         break;
        case MicroVolt:
         multiply = 1000*1000;
         name = "MicroVolt";
         break;
        case MilliVolt:
         multiply = 1000;
         name = "MilliVolt";
         break;
        case Volt:
         multiply = 1.0;
         name = "Volt";
         break;
        case KiloVolt:
         multiply = 1/1000.0;
         name = "KiloVolt";
         break;
        case MicroAmpere:
         multiply = 1000*1000;
         name = "MicroAmpere";
         break;
        case MilliAmpere:
         multiply = 1000;
         name = "MilliAmpere";
         break;
        case Ampere:
         multiply = 1.0;
         name = "Ampere";
         break;
        case KiloAmpere:
         multiply = 1/1000.0;
         name = "KiloAmpere";
         break;
       }
//       QMetaEnum metaEnum = QMetaEnum::fromType<UNITS>();
//       name = metaEnum.valueToKey(u);
       this->u = u;
      }
      /*private*/ Unit(QString s)
      {
       if(s == "Percent")
       {
        u = Percent;
        multiply = 1.0;
       }
       else if(s == "MicroVolt")
       {
        u = MicroVolt;
        multiply = 1000*1000;
       }
       else if(s == "MilliVolt")
       {
        u = MilliVolt;
        multiply = 1000.0;
       }
       else if(s == "Volt")
       {
        u = Volt;
        multiply = 1.0;
       }
       else if(s == "KiloVolt")
       {
        u = KiloVolt;
        multiply = 1/1000.0;
       }
       else if(s == "MicroAmpere")
       {
        u = MicroAmpere;
        multiply = 1000*1000;
       }
       else if(s == "MilliAmpere")
       {
        u = MilliAmpere;
        multiply = 1000.0;
       }
       else if(s == "Ampere")
       {
        u = Ampere;
        multiply = 1.0;
       }
       else if(s == "KiloAmpere")
       {
        u = KiloAmpere;
        multiply = 1/1000.0;
       }
       name = s;
      }
    friend class MeterFrame;
    friend class MeterFrameManagerXml;
  };
  MeterFrame(QUuid uuid = QUuid::createUuid(), QWidget* parent = nullptr);
  /*public*/ QUuid getUUID();
  /*public*/ Meter* getMeter();
  /*public*/ void setMeter(Meter* m);
  /*public*/ void initComponents();
  /*synchronized*/ /*public*/ void scaleImage();
  /*public*/ void dispose();
  /*public*/ int getNumIntegerDigits();
  /*public*/ void setNumIntegerDigits(int digits);
  /*public*/ int getNumDecimalDigits();
  /*public*/ void setNumDecimalDigits(int digits);
  /*public*/ Unit getUnit();
  /*public*/ void setUnit(MeterFrame::Unit unit);
  /*public*/ QString getClassName() {return "jmri.jmrit.swing.meter.MeterFrame";}

 private:
  static Logger* log;
  /*private*/ static /*final*/ int MAX_INTEGER_DIGITS;// = 7;
  /*private*/ static /*final*/ int MAX_DECIMAL_DIGITS;// = 3;
  /*private*/ /*final*/ QUuid uuid;

  /*private*/ /*final*/ QList<Meter*> voltageMeters = QList<Meter*>();
  /*private*/ /*final*/ QList<Meter*> currentMeters = QList<Meter*>();

  // GUI member declarations
  /*private*/ QMenuBar* menuBar = nullptr;
  QVector<JLabel*> integerDigitIcons;
  QVector<JLabel*> decimalDigitIcons;
  JLabel* decimal = nullptr;
  QMap<Unit::UNITS, JLabel*> unitLabels = QMap<Unit::UNITS, JLabel*>();

  QMap<Meter*, QAction*> meter_MenuItemMap = QMap<Meter*, QAction*>();
  QMap<Unit::UNITS, QAction*> units_MenuItemMap = QMap<Unit::UNITS, QAction*>();
  QMap<int, QAction*> integerDigits_MenuItemMap = QMap<int, QAction*>();
  QMap<int, QAction*> decimalDigits_MenuItemMap = QMap<int, QAction*>();
  QAction* lastSelectedMeterMenuItem = nullptr;
  QAction* lastSelectedIntegerDigitsMenuItem = nullptr;
  QAction* lastSelectedDecimalDigitsMenuItem = nullptr;
  int numIntegerDigits = 3;
  int numDecimalDigits = 0;
  int lastNumDecimalDigits = -1;
  int widthOfAllIconsToDisplay = 0;
  int oldWidthOfAllIconsToDisplay = -1;
  bool frameIsInitialized = false;
  Unit selectedUnit = Unit::Volt;

  int digitIconWidth;
  int decimalIconWidth;
  int unitIconWidth;
  int iconHeight;

  /*private*/ PropertyChangeListener* propertyChangeListener = nullptr;

  /*private*/ Meter* meter = nullptr;

  QVector<NamedIcon*> integerDigits = QVector<NamedIcon*>(10);
  QVector<NamedIcon*> decimalDigits = QVector<NamedIcon*>(10);
  NamedIcon* decimalIcon;
  NamedIcon* microVoltIcon;
  NamedIcon* milliVoltIcon;
  NamedIcon* voltIcon;
  NamedIcon* kiloVoltIcon;
  NamedIcon* microAmpIcon;
  NamedIcon* milliAmpIcon;
  NamedIcon* ampIcon;
  NamedIcon* kiloAmpIcon;
  NamedIcon* percentIcon;
  NamedIcon* errorIcon;

  JPanel* pane1;
  JPanel* meterPane;
  QMenu* voltageMetersMenu = nullptr;
  QMenu* currentMetersMenu = nullptr;
  /*private*/ void initSelectedUnit();
  /*private*/ void updateMenuUnits();
  /*private*/ void showError();
  /*synchronized*/ void update();
  /*private*/ void addAllMeters();
  /*private*/ void updateVoltageMeters(QMenu* voltageMetersMenu);
  /*private*/ void updateCurrentMeters(QMenu* currentMetersMenu);
  /*private*/ void updateCheckboxList();

  friend class BeanListListener;
  friend class SelectMeterAction;
};
/**
 * Provides hooks so that menus of available meters may be updated "on-the-fly"
 * as new meters are created and/or old meters are disposed of.
 */
/*private*/ /*static*/ class BeanListListener : public ManagerDataListener/*<Meter>*/ {
 Q_OBJECT
    /*private*/ BeanListListener(MeterFrame* mf) {
        this->mf = mf;
    }
    MeterFrame* mf = nullptr;
public:
    //@Override
    /*public*/ void contentsChanged(/*Manager.ManagerDataEvent<Meter> e*/) {
        MeterFrame::log->warn("contents of the bean list changed.");
        mf->updateCheckboxList();
    }

    //@Override
    /*public*/ void intervalRemoved(/*Manager.ManagerDataEvent<Meter> e*/) {
        mf->updateCheckboxList();
    }

    //@Override
    /*public*/ void intervalAdded(/*Manager.ManagerDataEvent<Meter> e*/) {
        mf->updateCheckboxList();
    }
    friend class MeterFrame;
};

/**
 * Mechanism for acting upon selection of a meter from one of the menu items.
 */
/*public*/ class SelectMeterAction : public AbstractAction {
 Q_OBJECT
    /*private*/ /*final*/ Meter* m;
  MeterFrame* f;
 public:
    /*public*/ SelectMeterAction(QString actionName, Meter* meter, MeterFrame* f)
    {
        //super(actionName);
        this->m = meter;
        this->f = f;

     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
    }
 public slots:
    //@Override
    /*public*/ void actionPerformed(/*ActionEvent e*/) {
        f->setMeter(m);

        AbstractAction* selectedItem = this;//(JMenuItem) e.valueSource();
        selectedItem->setChecked(true);
        f->lastSelectedMeterMenuItem = selectedItem;
    }
};

class MFPropertyChangeListener : public PropertyChangeListener
{
  Q_OBJECT
  MeterFrame* f;
 public:
  MFPropertyChangeListener(MeterFrame* f) {this->f = f;}

};
#endif // METERFRAME_H
