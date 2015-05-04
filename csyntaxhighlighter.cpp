#include "csyntaxhighlighter.h"

CSyntaxHighlighter::CSyntaxHighlighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
{
    HighlightningRule rule;

    sh_directionFormat.setFontWeight(QFont::Bold);
    sh_directionFormat.setForeground(Qt::darkGray);
    rule.pattern = QRegExp("[RLN]{1,10}");
    rule.format = sh_directionFormat;
    sh_highlightningRules.append(rule);

    sh_stateFormat.setForeground(Qt::cyan);
    rule.pattern = QRegExp("q*{1,5}");
    rule.format = sh_stateFormat;
    sh_highlightningRules.append(rule);

    sh_singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = sh_singleLineCommentFormat;
    sh_highlightningRules.append(rule);

    sh_multilineCommentFormat.setForeground(Qt::darkGreen);
    sh_commentStartExpr = QRegExp("/\\*");
    sh_commentEndExpr = QRegExp("\\*/");
}

void CSyntaxHighlighter::highlightBlock(const QString& text)
{
    foreach (HighlightningRule& rule, sh_highlightningRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while(index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    /*
     *block states:
     *0 - out of a comment
     *1 - in a comment
     */

    setCurrentBlockState(0);
    int startIndex = 0;
    if(previousBlockState() != 1)
        startIndex = sh_commentStartExpr.indexIn(text);
    while(startIndex >= 0)
    {
        int endIndex = sh_commentEndExpr.indexIn(text);
        int commentLength = 0;
        if(endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
            commentLength = endIndex - startIndex;      //NOTE: + commentEndExpression.matchedLength() ???
        setFormat(startIndex, commentLength, sh_multilineCommentFormat);
        startIndex = sh_commentEndExpr.indexIn(text, startIndex + commentLength);
    }
}
