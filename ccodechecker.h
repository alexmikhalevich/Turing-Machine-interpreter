#ifndef CCODECHECKER_H
#define CCODECHECKER_H
#include <QString>
#include <QRegExp>
#include <QVector>

class CCodeChecker
{
private:
    QString cc_code;
    QRegExp cc_correctLineExpr;
    QVector cc_wrongStrings;
public:
    CCodeChecker(const QString& text);
    bool is_correct() const;
    QVector get_wrong_strings() const;
};

#endif // CCODECHECKER_H
