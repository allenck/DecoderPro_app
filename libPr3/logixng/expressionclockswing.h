#ifndef EXPRESSIONCLOCKSWING_H
#define EXPRESSIONCLOCKSWING_H

#include "abstractdigitalexpressionswing.h"

class JComboBox;
class ExpressionClockSwing : public AbstractDigitalExpressionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionClockSwing(QObject *parent = nullptr);
    ~ExpressionClockSwing() {}
    ExpressionClockSwing(const ExpressionClockSwing&) : AbstractDigitalExpressionSwing() {}
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;;
    /*private*/ int validateTime(QList<QString>* errorMessages, JTextField *timeField);
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString()override;
    /*public*/ void dispose() override;

    QObject* sself() override {return this;}

private:
    /*private*/ JComboBox/*<Type>*/* _stateComboBox;
    /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;
    /*private*/ JTextField* _beginTextField;
    /*private*/ JTextField* _endTextField;

    /*private*/ int _beginMinutes;
    /*private*/ int _endMinutes;


};
Q_DECLARE_METATYPE(ExpressionClockSwing)
#endif // EXPRESSIONCLOCKSWING_H
