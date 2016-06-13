#ifndef MEMORYCONTENTS_H
#define MEMORYCONTENTS_H

#include <QObject>
#include "logger.h"
#include <QStringList>
#include <QVector>

class Writer;
class File;
/*public*/ enum LoadOffsetFieldType
{
 UNDEFINED,
 ADDRESSFIELDSIZE16BITS,
 ADDRESSFIELDSIZE24BITS,
 ADDRESSFIELDSIZEUNKNOWN
};
enum MemoryContentsException
{
 FileNotFoundException,
 MemoryFileRecordLengthException,
 MemoryFileChecksumException,
 MemoryFileUnknownRecordType,
 MemoryFileRecordContentException,
 MemoryFileNoDataRecordsException,
 MemoryFileNoEOFRecordException,
 MemoryFileRecordFoundAfterEOFRecord,
 MemoryFileAddressingRangeException,
 IOException,
 MemoryFileAddressingFormatException
};

class MemoryContents : public QObject
{
 Q_OBJECT
public:
 explicit MemoryContents(QObject *parent = 0);
 /*public*/ void readHex(QString filename);
 /*public*/ void readHex(File* file);
 /*public*/ void writeHex(Writer* w);
 /*public*/ void writeHex(Writer* writer, bool writeKeyVals, int blockSize);
 /*public*/ int nextContent(int location);
 /*public*/ void setLocation(int location, int value);
 /*public*/ bool locationInUse(int location);
 /*public*/ int getLocation(int location);
 /*public*/ bool isEmpty();
 /*public*/ QString extractValueOfKey(QString keyName);
 /*public*/ void setAddressFormat(LoadOffsetFieldType addressingType);
 /*public*/ LoadOffsetFieldType getCurrentAddressFormat();
 /*public*/ void addKeyValueComment(QString keyName, QString value);
 /*public*/ void writeComments(Writer* writer);
 enum RECTYPE
 {
  RECTYP_DATA_RECORD = 0,
  RECTYP_EXTENDED_SEGMENT_ADDRESS_RECORD = 2,
  RECTYP_EXTENDED_LINEAR_ADDRESS_RECORD = 4,
  RECTYP_EOF_RECORD = 1
 };

signals:
 void memoryContentsException(MemoryContentsException,  QString);

public slots:
private:
 /*private*/ static /*final*/ int DEFAULT_MEM_VALUE;// = -1;
 /*private*/ static /*final*/ int PAGESIZE;// = 0x10000;
 /*private*/ static /*final*/ int PAGES;// = 256;

 /*private*/ static /*final*/ QString STRING_DATA_RECTYP;// = StringUtil.twoHexFromInt(RECTYP_DATA_RECORD);
 /*private*/ static /*final*/ int CHARS_IN_RECORD_MARK;// = 1;
 /*private*/ static /*final*/ int CHARS_IN_RECORD_LENGTH;// = 2;
 /*private*/ static /*final*/ int CHARS_IN_RECORD_TYPE;// = 2;
 /*private*/ static /*final*/ int CHARS_IN_EACH_DATA_BYTE;// = 2;
 /*private*/ static /*final*/ int CHARS_IN_CHECKSUM;// = 2;
 /*private*/ static /*final*/ int CHARS_IN_24_BIT_ADDRESS;// = 6;
 /*private*/ static /*final*/ int CHARS_IN_16_BIT_ADDRESS;// = 4;

 /*private*/ static /*final*/ QChar LEADING_CHAR_COMMENT;// = '#'; // NOI18N
 /*private*/ static /*final*/ QChar LEADING_CHAR_KEY_VALUE;// = '!'; // NOI18N
 /*private*/ static /*final*/ QChar LEADING_CHAR_RECORD_MARK;// = ':'; // NOI18N
 // Instance variables
 /**
  * Firmware data storage
  *
  * Implemented as a two-dimensional array where the first dimension
  * represents the "page" number, and the second dimension represents the
  * byte within the page of <code>PAGESIZE</code> bytes.
  */
 /*private*/ /*final*/ /*int pageArray[256][0x10000];*/ QVector<QVector<int>* >* pageArray;
 /*private*/ int currentPage;
 /*private*/ int lineNum;
 /*private*/ bool hasData;
 /*private*/ int curExtLinAddr;
 /*private*/ int curExtSegAddr;

 /**
  * Storage for Key/Value comment information extracted from key/value
  * comments within a .DMF or .hex file
  */
 /*private*/ QStringList keyValComments;// = new ArrayList<String>(1);

 /**
  * Defines the LOAD OFFSET field type used/expected for records in "I8HEX"
  * and ".DMF" file formats.
  * <p>
  * When reading a file using the <code>readHex</code> method, the value is
  * inferred from the first record and then used to validate the remaining
  * records in the file.
  * <p>
  * This value must be properly set before invoking the <code>writeHex</code>
  * method.
  */
 /*private*/ LoadOffsetFieldType loadOffsetFieldType;// = UNDEFINED;
 /*private*/ bool isPageInitialized(int page);
 /*private*/ void initPage(int page);
 Logger* log;
 /*private*/ void writeHex(Writer* writer, int blockSize);
 /*private*/ LoadOffsetFieldType inferRecordAddressType(QString recordString);
 /*private*/ int calculate8BitChecksum(QString infoString);
 /*private*/ bool addressAndCountIsOk(int addr, int count);
 /*private*/ int findKeyCommentIndex(QString keyName);
 /*private*/ bool isLoadOffsetType24Bits();
 /*private*/ bool isLoadOffsetType16Bits();
 /*private*/ bool isSupportedRecordType(int recordType);
 /*private*/ int extractRecLen(QString line);
 /*private*/ int charsInAddress();
 /*private*/ int extractLoadOffset(QString line);

};

#endif // MEMORYCONTENTS_H
