#include "sketch_paper.h"

#include <algorithm>

#include <QPainter>
#include <QPaintEvent>
#include <QSizePolicy>

SketchPaper::SketchPaper(QWidget *parent)
    : QWidget{parent}, img_{IMG_WIDTH, IMG_HEIGHT, QImage::Format_RGB32}
{
    Clear();

    setMinimumWidth(200);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    pen_color_ = QColor(0, 0, 0);
    pen_thickness_ = 5;
}

void SketchPaper::setColor(QColor c)
{
    pen_color_ = c;
}

void SketchPaper::setThick(int thickness)
{
    pen_thickness_ = thickness;
}

void SketchPaper::mousePressEvent(QMouseEvent *event)
{
    qDebug(__func__);
    if(event->button() == Qt::LeftButton){
        is_drawing_ = true;
        from_ = event->pos();
    }
}

void SketchPaper::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug(__func__);
    if(event->button() == Qt::LeftButton){
        is_drawing_ = false;
    }
}

void SketchPaper::mouseMoveEvent(QMouseEvent *event)
{
    qDebug(__func__);
    if(is_drawing_){
        qDebug() << "color: " << pen_color_ << ", thickness: " << pen_thickness_;

        QPoint to = event->pos();

        QPainter g{&img_};

        g.setPen(QPen(pen_color_, pen_thickness_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        g.drawLine(from_, to);

        int min_x = std::min(from_.x(), to.x());
        int min_y = std::min(from_.y(), to.y());
        int max_x = std::max(from_.x(), to.x());
        int max_y = std::max(from_.y(), to.y());

        update(min_x - pen_thickness_, min_y - pen_thickness_,
               max_y - min_y + 2*pen_thickness_,
               max_x - min_x + 2*pen_thickness_);

        from_ = to;
    }
}

void SketchPaper::Clear(){
    img_.fill(qRgb(255, 255, 255));
    update(0,0, width(), height());
}

void SketchPaper::Save(const QString &path)
{
    img_.copy(QRect(0,0,width(), height())).save(path);
}

void SketchPaper::paintEvent(QPaintEvent *event)
{
    QPainter g(this);

    QRect rc = event->rect();

    g.drawImage(rc, img_, rc);
}
