#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QString>
#include <QJsonArray>
class JsonParser
{
public:
    JsonParser();
    int getResult();
    void setMessage(QString str);

private:
    QString message;
};

#endif // JSONPARSER_H
