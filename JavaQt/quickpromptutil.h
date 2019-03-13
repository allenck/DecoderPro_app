#ifndef QUICKPROMPTUTIL_H
#define QUICKPROMPTUTIL_H

#include <QObject>

class Component;
class QuickPromptUtil : public QObject
{
 Q_OBJECT
protected:
 explicit QuickPromptUtil(QObject *parent = nullptr);
public:
 static /*public*/ QString promptForString(Component* parentComponent, QString message, QString title, QString oldValue);
 static /*public*/ int promptForInt(Component* parentComponent, QString message, QString title, int oldValue);

signals:

public slots:
};

#endif // QUICKPROMPTUTIL_H
