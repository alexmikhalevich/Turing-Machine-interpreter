#ifndef QLINENUMBERAREA_H
#define QLINENUMBERAREA_H

#include <QWidget>
#include "qcodeedit.h"

class QLineNumberArea : public QWidget
{
public:
    explicit QLineNumberArea(QCodeEdit *edit);
    QSize sizeHint() const;
protected:
    void paintEvent(QPaintEvent* e);
private:
    QCodeEdit* lna_codeEdit;
};

#endif // QLINENUMBERAREA_H
