#ifndef PSetDir_H
#define PSetDir_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include "common.h"
#include "popups.h"
#include "button.h"
class PSetDir : public Popups
{
    Q_OBJECT
public:
    explicit PSetDir(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PSetDir_H
