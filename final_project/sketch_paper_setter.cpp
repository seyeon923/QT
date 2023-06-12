#include "sketch_paper_setter.h"

SketchPaperSetter::SketchPaperSetter(QWidget *parent)
    : QWidget{parent}
{
    setupUi(this);

    setMaximumWidth(250);

    connect(spinBox_thickness, &QSpinBox::valueChanged,
            this, &SketchPaperSetter::setThick);

    connect(spinBox_red, &QSpinBox::valueChanged,
            this, &SketchPaperSetter::setRed);
    connect(spinBox_green, &QSpinBox::valueChanged,
            this, &SketchPaperSetter::setGreen);
    connect(spinBox_blue, &QSpinBox::valueChanged,
            this, &SketchPaperSetter::setBlue);

}

void SketchPaperSetter::setColor(QColor color)
{
    int r = color.red();
    int g = color.green();
    int b = color.blue();

    spinBox_red->setValue(r);
    spinBox_green->setValue(g);
    spinBox_blue->setValue(b);

    label_color->setStyleSheet(QString::asprintf("background-color: rgb(%d, %d, %d)", r, g, b));

    emit colorChanged(QColor(r,g,b));
}

void SketchPaperSetter::setRed(int r)
{
    setColor(QColor(r, spinBox_green->value(), spinBox_blue->value()));
}
void SketchPaperSetter::setGreen(int g)
{
    setColor(QColor(spinBox_red->value(), g, spinBox_blue->value()));
}
void SketchPaperSetter::setBlue(int b)
{
    setColor(QColor(spinBox_red->value(), spinBox_green->value(), b));
}

void SketchPaperSetter::setThick(int thickness)
{
    if( thickness > MAX_THICKNESS){
        thickness = MAX_THICKNESS;
    }
    if(thickness < MIN_THICKNESS){
        thickness = MIN_THICKNESS;
    }

    spinBox_thickness->setValue(thickness);

    emit thickChanged(thickness);
}
