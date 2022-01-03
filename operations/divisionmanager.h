#ifndef OPERATIONS_DIVISIONMANAGER_H
#define OPERATIONS_DIVISIONMANAGER_H

#include <propertychangesupport.h>
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"
#include "jcombobox.h"
#include <QtXml>

namespace Operations {
 class Division;
 class DivisionManager : public PropertyChangeSupport,public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
   Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)
  public:
   Q_INVOKABLE explicit DivisionManager(QObject *parent = nullptr);
   ~DivisionManager() {}
   DivisionManager(const DivisionManager&) : PropertyChangeSupport(this) {}
   /*public*/  static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "divisionsListLength"; // NOI18N
   /*public*/  void dispose();
   /*public*/  int getNumberOfdivisions();
   /*public*/  Division* getDivisionByName(QString name);
   /*public*/  Division* getDivisionById(QString id);
   /*public*/  Division* newDivision(QString name);
   /*public*/  void _register(Division* division);
   /*public*/  void deregister(Division* division);
   /*public*/  QList<Division*> getDivisionsByNameList();
   /*public*/  QList<Division*> getDivisionsByIdList();
   /*public*/  QList<Division*> getList();
   /*public*/  JComboBox/*<Division>*/* getComboBox();
   /*public*/  void updateComboBox(JComboBox/*<Division>*/* box);
   /*public*/  void load(QDomElement root);
   /*public*/  void store(QDomElement root, QDomDocument doc);
   Q_INVOKABLE /*public*/  void initialize()override;

  private:
   /*private*/ int _id = 0;
   static Logger* log;

  protected:
   /*protected*/ QMap<QString, Division*> _divisionHashTable = QMap<QString, Division*>();
   /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };

} // namespace Operations
Q_DECLARE_METATYPE(Operations::DivisionManager)
#endif // OPERATIONS_DIVISIONMANAGER_H
