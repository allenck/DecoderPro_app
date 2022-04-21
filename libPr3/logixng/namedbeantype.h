#ifndef NAMEDBEANTYPE_H
#define NAMEDBEANTYPE_H
#include "light.h"
#include "proxylightmanager.h"
#include "instancemanager.h"
#include "proxyturnoutmanager.h"
#include "defaultmemorymanager.h"
#include "proxysensormanager.h"
#include "abstractsignalheadmanager.h"
#include "defaultsignalmastmanager.h"
/**
 * Defines types of NamedBeans, for example Turnout and Light.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
/*public*/ /*enum*/class NamedBeanType : QObject {
//    Light(Bundle.getMessage("BeanNameLight"), Light.class, "KnownState", () -> {
//        return InstanceManager.getDefault(LightManager.class);
//    }),
//    Memory(Bundle.getMessage("BeanNameMemory"), Memory.class, "value", () -> {
//        return InstanceManager.getDefault(MemoryManager.class);
//    }),
//    Sensor(Bundle.getMessage("BeanNameSensor"), Sensor.class, "KnownState", () -> {
//        return InstanceManager.getDefault(SensorManager.class);
//    }),
//    SignalHead(Bundle.getMessage("BeanNameSignalHead"), SignalHead.class, null, () -> {
//        return InstanceManager.getDefault(SignalHeadManager.class);
//    }),
//    SignalMast(Bundle.getMessage("BeanNameSignalMast"), SignalMast.class, null, () -> {
//        return InstanceManager.getDefault(SignalMastManager.class);
//    }),
//    Turnout(Bundle.getMessage("BeanNameTurnout"), Turnout.class, "KnownState", () -> {
//        return InstanceManager.getDefault(TurnoutManager.class);
//    });
  Q_OBJECT
 public:
  enum TYPE {Light, Memory, Sensor, SignalHead, SignalMast, Turnout};

//    private final String _name;
//    private final Class<? extends NamedBean> _clazz;
//    private final String _propertyName;
//    private final GetManager _getManager;
//    private Manager<? extends NamedBean> _manager;

//    NamedBeanType(String name, Class<? extends NamedBean> clazz, String propertyName, GetManager getManager) {
//        _name = name;
//        _clazz = clazz;
//        _propertyName = propertyName;
//        _getManager = getManager;
//        _manager = _getManager.getManager();
//    }

    //@Override
    /*public*/static QString toString(TYPE t) {
        switch(t)
        {
        case Light: return tr("Light");
        case Memory: return tr("Memory");
        case Sensor: return tr("Sensor");
        case SignalHead: return tr("SignalHead");
        case SignalMast: return tr("SignalMast");
         case Turnout: return tr("Sensor");
        }
    }

//    public Class<? extends NamedBean> getClazz() {
//        return _clazz;
//    }
  /*public*/static QString getClazz(TYPE t) {
      switch(t)
      {
      case Light: return "KnownState";
      case Memory: return "value";
      case Sensor: return "KnownState";
      case SignalHead: return "";
      case SignalMast: return "";
       case Turnout: return "KnownState";
      }
      throw new IllegalArgumentException(tr("NamedBeanType %1 is invalid").arg(t));
  }

    /*public*/ static QString getPropertyName(TYPE t) {
     switch(t)
     {
     case Light: return "Light";
     case Memory: return "Memory";
     case Sensor: return "Sensor";
     case SignalHead: return "SignalHead";
     case SignalMast: return "SignalMast";
      case Turnout: return "Sensor";
     }
     throw new IllegalArgumentException(tr("NamedBeanType %1 is invalid").arg(t));
    }

    /*public*/ static Manager/*<? extends NamedBean>*/* getManager(TYPE t) {
     switch(t)
     {
     case Light: return (Manager*)(AbstractProxyManager*)InstanceManager::getDefault("LightManager");
     case Memory: return (DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager");
     case Sensor: return (AbstractProxyManager*)InstanceManager::getDefault("SensorManager");
     case SignalHead: return (AbstractManager*)InstanceManager::getDefault("SignalHeadManager");
     case SignalMast: return (DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager");
      case Turnout: return (AbstractProxyManager*)InstanceManager::getDefault("TurnoutManager");
     }
     throw new IllegalArgumentException(tr("NamedBeanType %1 is invalid").arg(t));
    }

  /*public*/ static TYPE valueOf(QString s)
  {
   if(s == "Light") return Light;
   if(s == "Memory") return Memory;
   if(s == "Sensor") return Sensor;
   if(s == "SignalHead") return SignalHead;
   if(s == "SignalMast") return SignalMast;
    if(s == "Turnout")return Turnout;
    throw new IllegalArgumentException(tr("NamedBeanType %1 is invalid").arg(s));
  }
#if 0
    // This method is used by test classes to reset this enum.
    // Each test resets the InstanceManager so we need to reset the
    // managers in this enum.
    public static void reset() {
        for (NamedBeanType type : NamedBeanType.values()) {
            type._manager = type._getManager.getManager();
        }
    }

    private interface GetManager {

        Manager<? extends NamedBean> getManager();
    }
#endif
    };
#endif // NAMEDBEANTYPE_H
