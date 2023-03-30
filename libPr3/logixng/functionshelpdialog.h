#ifndef FUNCTIONSHELPDIALOG_H
#define FUNCTIONSHELPDIALOG_H

#include <QObject>
#include <QMap>
#include "jdialog.h"
#include "jcombobox.h"
#include "jlabel.h"
#include "jeditorpane.h"
#include "comparable.h"
#include "windowadapter.h"
#include "instancemanagerautodefault.h"

class JActionEvent;
class Function;
class Module_x;
class FunctionsHelpDialog : public QObject, public InstanceManagerAutoDefault
{
  Q_OBJECT
    Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  Q_INVOKABLE explicit FunctionsHelpDialog(QObject *parent = nullptr);
    ~FunctionsHelpDialog() {}
    FunctionsHelpDialog(const FunctionsHelpDialog&) : QObject() {}

  /*public*/  void showDialog();

 signals:

 private:
  /*private*/ static /*final*/ int panelWidth;// = 500;
  /*private*/ static /*final*/ int panelHeight;// = 500;

  /*private*/ static /*final*/ QMap<QString, Module_x*> _modules;// = QMap<QString, Module*>();
  /*private*/ JDialog* _selectItemTypeDialog = nullptr;
  /*private*/ /*final*/ JComboBox/*<Module>*/* _moduleComboBox = new JComboBox();
  /*private*/ /*final*/ JComboBox/*<SortableFunction>*/* _functionComboBox = new JComboBox();
  /*private*/ /*final*/ JLabel* _moduleLabel = new JLabel(tr("Module") + ":");  // NOI18N
  /*private*/ /*final*/ JLabel* _functionLabel = new JLabel(tr("Function") + ":");   // NOI18N
  /*private*/ /*final*/ JEditorPane* _documentationEditorPane = new JEditorPane();
    /*private*/ void initFunctionsComboBox();

protected:
    /*final*/ /*protected*/ void cancelAddPressed(JActionEvent* e);

    friend class FHD_WindowAdapter;
};
class FHD_WindowAdapter : public WindowAdapter
{
    FunctionsHelpDialog* fhd;
public:
    FHD_WindowAdapter(FunctionsHelpDialog* fhd) { this->fhd = fhd;}
    /*public*/  void windowClosing(QCloseEvent* e) override{
        fhd->cancelAddPressed(nullptr);
    }
};
Q_DECLARE_METATYPE(FunctionsHelpDialog)

class Module_x : public QObject, public Comparable<Module_x>
{
    Q_OBJECT
    /*private*/ /*final*/ QString _name;
    /*private*/ /*final*/ QString _constantDescriptions;
    /*private*/ /*final*/ QList<Function*> _functions = QList<Function*>();

    /*private*/ Module_x(QString name, QString constantDescriptions) {
        _name = name;
        _constantDescriptions = constantDescriptions;
    }
public:
    //@Override
    /*public*/ bool equals(Module_x* o) {
        return (qobject_cast< Module_x*>(o)) && _name == (((Module_x*)o)->_name);
    }

    //@Override
//        /*public*/ int hashCode() {
//            int hash = 7;
//            hash = 47 * hash + Objects.hashCode(this._name);
//            return hash;
//        }

    //@Override
    /*public*/ int compareTo(Module_x o) {
        return _name.compare(o._name);
    }

    //@Override
    /*public*/ QString toString() {
        return _name;
    }
    friend class FunctionsHelpDialog;
};
/*private*/ /*static*/ class SortableFunction : public QObject, public Comparable<SortableFunction> {
  Q_OBJECT
    /*private*/ /*final*/ QString _name;
    /*private*/ /*final*/ QString _functionDescr;

    /*private*/ SortableFunction(QString name, QString functionDescr) {
        _name = name;
        _functionDescr = functionDescr;
    }

    //@Override
    /*public*/  bool equals(QObject* o) {
        return (qobject_cast< SortableFunction*>(o)) && _name == (((SortableFunction*)o)->_name) ;
    }

    //@Override
//        /*public*/  int hashCode() {
//            int hash = 7;
//            hash = 47 * hash + Objects.hashCode(this._name);
//            return hash;
//        }

    //@Override
    /*public*/  int compareTo(SortableFunction* o) {
        return _name.compare(o->_name);
    }

    //@Override
    /*public*/  QString toString() {
        return _name;
    }
    friend class FunctionsHelpDialog;
};
#endif // FUNCTIONSHELPDIALOG_H
