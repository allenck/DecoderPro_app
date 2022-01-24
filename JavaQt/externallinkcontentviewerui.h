#ifndef EXTERNALLINKCONTENTVIEWERUI_H
#define EXTERNALLINKCONTENTVIEWERUI_H

#include <QObject>

class Logger;
class ExternalLinkContentViewerUI : public QObject
{
 Q_OBJECT
public:
 explicit ExternalLinkContentViewerUI(QObject *parent = nullptr);
 /*public*/ static void activateURL(QUrl u); //throw new IOException, URISyntaxException

signals:

public slots:
private:
 static Logger* log;
};

#endif // EXTERNALLINKCONTENTVIEWERUI_H
