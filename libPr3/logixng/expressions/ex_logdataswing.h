#ifndef EXPRESSIONS_LOGDATASWING_H
#define EXPRESSIONS_LOGDATASWING_H

#include "../abstractdigitalexpressionswing.h"
#include "jcheckbox.h"
#include "jcombobox.h"
#include "jtable.h"

namespace Expressions {
 class LogDataTableModel;
 class LogDataSwing : public AbstractDigitalExpressionSwing
 {
   Q_OBJECT
  public:
   LogDataSwing(QObject* parent = nullptr);
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
Q_DECLARE_METATYPE(Expressions::LogDataSwing)
#endif // EXPRESSIONS_LOGDATASWING_H
