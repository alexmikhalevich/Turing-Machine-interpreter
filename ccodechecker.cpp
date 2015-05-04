#include "ccodechecker.h"

CCodeChecker::CCodeChecker(const QString& text)
{
    cc_code = text;

    //TODO: replace [01]. Maybe should be any sequence of characters
    cc_correctLineExpr = QRegExp("\\(q[0-9]{1,}\\,[01]\\)\\->\\(q[0-9]{1,}\\,[01]\\,[RLN]{1,}\)");
}

bool CCodeChecker::is_correct() const
{

}

QVector CCodeChecker::get_wrong_strings() const
{
    return cc_wrongStrings;
}
