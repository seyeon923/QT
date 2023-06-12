#ifndef SKETCHPAPERSETTER_H
#define SKETCHPAPERSETTER_H

#include <QWidget>

#include "ui_sketch_paper_setter.h"

class SketchPaperSetter : public QWidget, Ui_SketchPaper
{
    Q_OBJECT
public:
    explicit SketchPaperSetter(QWidget *parent = nullptr);

    constexpr static int MAX_THICKNESS = 99;
    constexpr static int MIN_THICKNESS = 1;

signals:
    void colorChanged(QColor);
    void thickChanged(int);

public slots:
    void setColor(QColor color);
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);
    void setThick(int thickness);
};

#endif // SKETCHPAPERSETTER_H
