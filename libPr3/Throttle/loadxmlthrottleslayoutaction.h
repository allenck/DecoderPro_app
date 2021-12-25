#ifndef LOADXMLTHROTTLESLAYOUTACTION_H
#define LOADXMLTHROTTLESLAYOUTACTION_H
#include "abstractaction.h"
#include "exceptions.h"

class File;
class Logger;
class JFileChooser;
class LoadXmlThrottlesLayoutAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ LoadXmlThrottlesLayoutAction(QString s, QObject* parent);
 /*public*/ LoadXmlThrottlesLayoutAction(QObject* parent);
 /*public*/ bool loadThrottlesLayout(File* f) /*throw (IOException)*/;

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

 private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger('LoadXmlThrottlesLayoutAction');
 JFileChooser* fileChooser;

};

#endif // LOADXMLTHROTTLESLAYOUTACTION_H
