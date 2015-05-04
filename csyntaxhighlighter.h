#ifndef CSYNTAXHIGHLIGHTER_H
#define CSYNTAXHIGHLIGHTER_H
#include <QSyntaxHighlighter>

class CSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    CSyntaxHighlighter(QTextDocument* parent = 0);
protected:
    void highlightBlock(const QString &text);
private:
    struct HighlightningRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightningRule> sh_highlightningRules;
    QTextCharFormat sh_stateFormat;
    QTextCharFormat sh_directionFormat;
    QTextCharFormat sh_singleLineCommentFormat;
    QTextCharFormat sh_multilineCommentFormat;
    QRegExp sh_commentStartExpr;
    QRegExp sh_commentEndExpr;
};

#endif // CSYNTAXHIGHLIGHTER_H
