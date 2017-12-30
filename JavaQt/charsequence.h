#ifndef CHARSEQUENCE_H
#define CHARSEQUENCE_H

#include <QObject>

class CharSequence : public QObject
{
 Q_OBJECT
public:
 explicit CharSequence(QObject *parent = 0);
 virtual int length();
 virtual char charAt(int index);
 virtual CharSequence* subSequence(int start, int end);
 virtual /*public*/ QString toString();
signals:

public slots:
};

#endif // CHARSEQUENCE_H
