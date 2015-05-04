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
