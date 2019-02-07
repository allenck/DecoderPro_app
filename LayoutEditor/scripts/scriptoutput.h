#ifndef SCRIPTOUTPUT_H
#define SCRIPTOUTPUT_H

#include <QObject>

class Logger;
class JTextArea;
class ScriptOutput : public QObject
{
 Q_OBJECT
public:
 explicit ScriptOutput(QObject *parent = nullptr);
 /*public*/ JTextArea* getOutputArea();
 static /*public*/ ScriptOutput* getDefault();
 static /*public*/ void writeScript(/*final*/ QString script);

signals:

public slots:

private:
 /*private*/ JTextArea* output = nullptr;
 static Logger* log;
};

#endif // SCRIPTOUTPUT_H
