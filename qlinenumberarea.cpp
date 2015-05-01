#include "qlinenumberarea.h"

QLineNumberArea::QLineNumberArea(QCodeEdit* edit) : QWidget(edit)
{
    lna_codeEdit = edit;
}

QSize QLineNumberArea::sizeHint() const
{
    return QSize(lna_codeEdit->line_number_area_width(), 0);
}

void QLineNumberArea::paintEvent(QPaintEvent* e)
{
    lna_codeEdit->line_number_area_paint_event(e);
}
