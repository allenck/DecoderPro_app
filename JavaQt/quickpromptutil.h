#ifndef QUICKPROMPTUTIL_H
#define QUICKPROMPTUTIL_H

#include <QObject>

class QIntValidator;
class Component;
class QuickPromptUtil : public QObject
{
 Q_OBJECT
protected:
 explicit QuickPromptUtil(QObject *parent = nullptr);
public:
 static /*public*/ QString promptForString(Component* parentComponent, QString message, QString title, QString oldValue);
 static /*public*/ int promptForInt(Component* parentComponent, QString message, QString title, int oldValue);
 /*public*/ static int promptForInteger(Component* parentComponent, /*@Nonnull*/ QString message, /*@Nonnull*/ QString title, int oldValue, /*@CheckForNull*/ QIntValidator* validator);
 /*public*/ static QIntValidator* checkIntRange(int min, int max, QString valueLabel);

private:
};
#endif // QUICKPROMPTUTIL_H
