#include "qcodeedit.h"
#include <QPainter>
#include <QTextBlock>

QCodeEdit::QCodeEdit(QWidget* parent) : QPlainTextEdit(parent)
{
    ce_lineNumberArea = new QWidget(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int QCodeEdit::line_number_area_width()
{
    int digits = 1;
    int max = std::max(1, blockCount());
    while(max >= 10)
    {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void QCodeEdit::updateLineNumberAreaWidth(const int newBlockCount) //TODO: is newBlockCount variable necessary here?
{
    setViewportMargins(line_number_area_width(), 0, 0, 0);
}

void QCodeEdit::updateLineNumberArea(const QRect &rect, const int dy)
{
    if(dy)
        ce_lineNumberArea->scroll(0, dy);
    else
        ce_lineNumberArea->update(0, rect.y(), ce_lineNumberArea->width(), rect.height());

    if(rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void QCodeEdit::resizeEvent(QResizeEvent* e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    ce_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), line_number_area_width(), cr.height()));
}

void QCodeEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelection;

    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::gray).lighter();

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelection.append(selection);
    }
    setExtraSelections(extraSelection);
}

void QCodeEdit::line_number_area_paint_event(QPaintEvent* e)
{
    QPainter painter(ce_lineNumberArea);
    painter.fillRect(e->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int)blockBoundingRect(block).height();

    while(block.isValid() && top <= e->rect().bottom())
    {
        if(block.isVisible() && bottom >= e->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, ce_lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int)blockBoundingRect(block).height();
        ++blockNumber;
    }
}
