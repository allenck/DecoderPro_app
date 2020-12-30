#ifndef ACTION_H
#define ACTION_H

#include <QAction>
#include "javaqt_global.h"
#include "actionevent.h"

class QIcon;
class QVariant;
class PropertyChangeListener;
class QAction;
class QMenu;
class JAVAQTSHARED_EXPORT Action : public QAction
{
 Q_OBJECT
public:
 //explicit Action();
 Action(QObject *parent = 0) : QAction(parent){};
 Action(QString text, QIcon icon, QObject* parent) : QAction(icon, text, parent) {}
 Action(QString text, QObject* parent) : QAction( text, parent) {}
 Action(const Action& other ) : QAction(other.icon(),other.text(), other.parent()) {}

 /*public*/  static /*final*/ QString DEFAULT; // "Default";
 /*public*/  static /*final*/ QString NAME; // "Name";
 /*public*/  static /*final*/ QString SHORT_DESCRIPTION; // "ShortDescription";
 /*public*/  static /*final*/ QString LONG_DESCRIPTION; // "LongDescription";
 /*public*/  static /*final*/ QString SMALL_ICON; // "SmallIcon";
 /*public*/  static /*final*/ QString ACTION_COMMAND_KEY; // "ActionCommandKey";
 /*public*/  static /*final*/ QString ACCELERATOR_KEY;//="AcceleratorKey";
 /*public*/  static /*final*/ QString MNEMONIC_KEY;//="MnemonicKey";
 /*public*/  static /*final*/ QString SELECTED_KEY; // "SwingSelectedKey";
 /*public*/  static /*final*/ QString DISPLAYED_MNEMONIC_INDEX_KEY;// =
//                              "SwingDisplayedMnemonicIndexKey";
 /*public*/  static /*final*/ QString LARGE_ICON_KEY; // "SwingLargeIconKey";
 /*public*/  virtual void putValue(QString key, QVariant value);
 /*public*/  virtual void setEnabled(bool b);
 /*public*/  virtual bool isEnabled();
 /*public*/  virtual void addPropertyChangeListener(PropertyChangeListener* listener);
 /*public*/  virtual void removePropertyChangeListener(PropertyChangeListener* listener);
 /*public*/ virtual QVariant getValue(QString /*key*/) {return QVariant();}

signals:

public slots:
 virtual void  actionPerformed(JActionEvent*) {}

private:

};

#endif // ACTION_H
