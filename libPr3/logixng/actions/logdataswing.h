#ifndef LOGDATASWING_H
#define LOGDATASWING_H

#include "../abstractdigitalactionswing.h"
#include "jcheckbox.h"
#include "jcombobox.h"
#include "jtable.h"

namespace Actions {
 class LogDataTableModel;
 class LogDataSwing : public AbstractDigitalActionSwing
 {
   Q_OBJECT
  public:
   Q_INVOKABLE LogDataSwing(QObject* parent = nullptr) {}
   ~LogDataSwing(){}
   LogDataSwing(const LogDataSwing&){}
   /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
   /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
   /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
   /*public*/  QString toString()override;
   /*public*/  void dispose()override;

   QObject* sself() override {return this;}

  private:
   /*private*/ JCheckBox* _logToLogCheckBox;
   /*private*/ JCheckBox* _logToScriptOutputCheckBox;
   /*private*/ JComboBox/*<LogData.FormatType> */* _formatType;
   /*private*/ JTextField* _format;
   /*private*/ JTable* _logDataTable;
   /*private*/ LogDataTableModel* _logDataTableModel;

  protected:
   /*protected*/ void createPanel(/*@CheckForNull */Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

 };
}
Q_DECLARE_METATYPE(Actions::LogDataSwing)
#endif // LOGDATASWING_H
