#ifndef QCODEEDIT_H
#define QCODEEDIT_H

#include <QWidget>
#include <QPlainTextEdit>

class QCodeEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit QCodeEdit(QWidget* parent = 0);
    void line_number_area_paint_event(QPaintEvent* event);
    int line_number_area_width();
protected:
    void resizeEvent(QResizeEvent* e);
private:
    QWidget* ce_lineNumberArea;
private slots:
    void updateLineNumberAreaWidth(const int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, const int dy);
};

#endif // QCODEEDIT_H
