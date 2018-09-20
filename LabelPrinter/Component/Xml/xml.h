#ifndef XML_H
#define XML_H

#include <QObject>

#define XML_TABLE_COLUMN_COUNT_MAX      6

#define XML_DECLARATION_TARGET          "xml"
#define PATH_SETTING                    "labelXml/Setup.xml"
#define XML_DECLARATION_DATA            "version=\"1.0\" encoding=\"UTF-8\""
#define XML_SETUP                       "Setup"
#define XML_CODEC                       "UTF-8"
#define XML_TAG_POS                     "Pos"
#define XML_TAG_TABLE_TEXT              "TableText"
#define XML_POS_POSXVAL                 "PosXVal"
#define XML_POS_POSYVAL                 "PosYVal"
#define XML_POS_X_DEFAULT_VALUE         "20"
#define XML_POS_Y_DEFAULT_VALUE         "30"
#define XML_DEFAULT_VALUE               "none"
#define XML_TABLE_COLUMN0               "Column0"
#define XML_TABLE_COLUMN1               "Column1"
#define XML_TABLE_COLUMN2               "Column2"
#define XML_TABLE_COLUMN3               "Column3"
#define XML_TABLE_COLUMN4               "Column4"
#define XML_TABLE_COLUMN5               "Column5"


class Xml: public QObject
{
    Q_OBJECT
public:
    inline explicit Xml(QObject *parent = 0);
    static Xml *getInstance();

public:
    void createSettingXml(void);
    int getXmlPosX(void);
    int getXmlPosY(void);
    QString getXmlTableText(const int);
    void writeXmlPos(const QString, const QString);
    void writeXmlTableText(const QStringList columnText);

private:
    void readPosXml(void);
    bool readXmlTableText(void);

private:
    QString m_posX;
    QString m_posY;
    QString m_column[6];
};

#endif // XML_H
