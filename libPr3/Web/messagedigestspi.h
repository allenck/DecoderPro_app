#ifndef MESSAGEDIGESTSPI_H
#define MESSAGEDIGESTSPI_H

#include <QObject>
#include <QByteArray>

class MessageDigestSpi : public QObject
{
 Q_OBJECT
public:
 explicit MessageDigestSpi(QObject *parent = nullptr);

signals:

public slots:

private:
 // for re-use in engineUpdate(ByteBuffer input)
 /*private*/ QByteArray tempArray;

protected:
 /*protected*/ int engineGetDigestLength();

 /**
  * Updates the digest using the specified byte.
  *
  * @param input the byte to use for the update.
  */
 /*protected*/ /*abstract*/ virtual void engineUpdate(char input);

 /**
  * Updates the digest using the specified array of bytes,
  * starting at the specified offset.
  *
  * @param input the array of bytes to use for the update.
  *
  * @param offset the offset to start from in the array of bytes.
  *
  * @param len the number of bytes to use, starting at
  * {@code offset}.
  */
 /*protected*/ virtual void engineUpdate(QByteArray input, int offset, int len);


};

#endif // MESSAGEDIGESTSPI_H
