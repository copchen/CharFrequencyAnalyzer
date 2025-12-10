#ifndef DOCXANALYZER_H
#define DOCXANALYZER_H

#include <QString>
#include <QMap>
#include <QChar>

class DocxAnalyzer
{
public:

    static QMap<QChar, quint64> analyzeDocx(const QString &path);


    static QString extractFullText(const QString &path);
};

#endif // DOCXANALYZER_H
