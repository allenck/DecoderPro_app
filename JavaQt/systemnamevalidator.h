#ifndef SYSTEMNAMEVALIDATOR_H
#define SYSTEMNAMEVALIDATOR_H

#include <QObject>

class Manager;
class SystemNameValidator : public QObject
{
 Q_OBJECT
public:
 explicit SystemNameValidator(QObject *parent = nullptr);
 /*public*/ SystemNameValidator(/*@Nonnull*/ /*JComponent*/QWidget* component, /*@Nonnull*/ Manager* manager, bool required = false);
 /*public*/ bool isRequired();
 /*public*/ void setRequired(bool required);
 /*public*/ void setManager(/*@Nonnull*/ Manager* manager);

signals:

public slots:

private:
 /*private*/ Manager* manager;
 /*private*/ bool required = false;

};

#endif // SYSTEMNAMEVALIDATOR_H
