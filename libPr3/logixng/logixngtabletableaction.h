#ifndef LOGIXNGTABLETABLETABLEACTION_H
#define LOGIXNGTABLETABLETABLEACTION_H

#include "abstractlogixngtableaction.h"
#include "namedtable.h"
#include <QRadioButton>
#include <QButtonGroup>
#include "jtextfield.h"
#include "jbutton.h"

class LogixNGTableTableAction : public AbstractLogixNGTableAction
{
  Q_OBJECT
 public:
  Q_INVOKABLE LogixNGTableTableAction(QString s, QObject* parent = nullptr);
  Q_INVOKABLE /*public*/  LogixNGTableTableAction(QObject* parent=nullptr);
  ~LogixNGTableTableAction() {}
  LogixNGTableTableAction(const LogixNGTableTableAction&) : AbstractLogixNGTableAction(tr("LogixNGTableTable")) {}
  Q_INVOKABLE/*public*/  QString getClassDescription()override;

 private:
  static Logger* log;
  QRadioButton* _typeExternalTable = new QRadioButton(tr("External CSV table"));
  QRadioButton* _typeInternalTable = new QRadioButton(tr("Internal table stored in the panel file"));
  QButtonGroup* _buttonGroup = new QButtonGroup();
  JTextField* _csvFileName = new JTextField(50);
  /*private*/ JButton* createFileChooser();

  void autoSystemName() {AbstractLogixNGTableAction::autoSystemName(); }
 protected:
  /*protected*/ void setTitle()override;
  /*protected*/ AbstractLogixNGEditor/*<NamedTable>*/* getEditor(BeanTableFrame/*<NamedTable>*/* f, BeanTableDataModel/*<NamedTable>*/* m, QString sName);
  /*protected*/ Manager/*<NamedTable>*/* getManager()override;
  /*protected*/ void enableAll(bool enable)override;
  /*protected*/ void setEnabled(NamedBean* bean, bool enable)override;
  /*protected*/ bool isEnabled(NamedBean* bean)override;
  /*protected*/ /*NamedTable**/NamedBean* createBean(QString userName)override;
  /*protected*/ /*NamedTable**/NamedBean* createBean(QString systemName, QString userName)override;
  /*protected*/ void deleteBean(NamedBean* bean)override;
  /*protected*/ bool browseMonoSpace();
  /*protected*/ QString getBeanText(NamedBean* bean)override;
  /*protected*/ QString getAddTitleKey()override;
  /*protected*/ QString getCreateButtonHintKey()override;
  /*protected*/ QString helpTarget()override;
  /*protected*/ JPanel* makeAddFrame(QString titleId, QString startMessageId);
  /*protected*/ void getListenerRefsIncludingChildren(NamedBean* table, QList<QString> list)override;
  /*protected*/ bool hasChildren(NamedBean* table)override;

};
Q_DECLARE_METATYPE(LogixNGTableTableAction)
#endif // LOGIXNGTABLETABLETABLEACTION_H
