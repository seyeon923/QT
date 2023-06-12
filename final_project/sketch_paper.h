#ifndef SKETCHPAPER_H
#define SKETCHPAPER_H

#include <QWidget>

class SketchPaper : public QWidget
{
    Q_OBJECT
public:
    explicit SketchPaper(QWidget *parent = nullptr);

    constexpr static int IMG_WIDTH = 5120;
    constexpr static int IMG_HEIGHT = 5120;

public slots:
    void setColor(QColor c);
    void setThick(int thickness);

    void Clear();

    void Save(const QString& path);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;


signals:

private:
    QImage img_;
    QColor pen_color_;
    int pen_thickness_;

    QPoint from_;
    bool is_drawing_;
};

#endif // SKETCHPAPER_H
