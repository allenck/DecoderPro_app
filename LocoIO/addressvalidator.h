#ifndef ADDRESSVALIDATOR_H
#define ADDRESSVALIDATOR_H
#include <QRegExpValidator>

class AddressValidator : public QRegExpValidator
{
public:
 AddressValidator(QObject* parent=0);
 AddressValidator(QRegExp& rx, QObject *parent=0);
 void setRelaxed(bool b);
 virtual QValidator::State	validate ( QString & input, int & pos ) const;
 /*virtual*/ void fixup(QString &input) const;
private:
 bool bRelax;
};
#endif // ADDRESSVALIDATOR_H
