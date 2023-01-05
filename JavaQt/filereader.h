#ifndef FILEREADER_H
#define FILEREADER_H
#include "inputstreamreader.h"
#include "exceptions.h"

class File;
class FileReader : public InputStreamReader
{
public:
 /*public*/ FileReader(QString fileName, QObject* parent = nullptr) /*throw (FileNotFoundException)*/;
 /*public*/ FileReader(File* file, QObject* parent = nullptr) /*throw (FileNotFoundException)*/;

};

#endif // FILEREADER_H
