#include "mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setupUi(this);

    connect(sketch_paper_setter, &SketchPaperSetter::colorChanged,
            sketch_paper, &SketchPaper::setColor);
    connect(sketch_paper_setter, &SketchPaperSetter::thickChanged,
            sketch_paper, &SketchPaper::setThick);

    sketch_paper_setter->setColor(QColor(0,0,0));
    sketch_paper_setter->setThick(5);

    connect(action_exit, &QAction::triggered, this, &QMainWindow::close);

    connect(action_showme, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "제출자", "회사: LG이노텍\r\n사번: 89869\r\n이름: 김세연");
    });

    sketch_paper->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(sketch_paper, &SketchPaper::customContextMenuRequested,
            this, &MainWindow::SketchPaperContextRequested);

    connect(action_save, &QAction::triggered, [this](){
        auto save_path = QFileDialog::getSaveFileName(this, "Save Image", {}, "png file(*.png)");

        if(save_path != ""){
            sketch_paper->Save(save_path);
            qDebug() << "Saved to " << save_path;
        }
    });
}

void MainWindow::SketchPaperContextRequested(QPoint pos)
{
    qDebug(__func__);
    QMenu menu{this};

    menu.addAction("빨강", sketch_paper_setter,
                    [this](){sketch_paper_setter->setColor(QColor(255, 0, 0));});
    menu.addAction("파랑", sketch_paper_setter,
                    [this](){sketch_paper_setter->setColor(QColor(0, 0, 255));});
    menu.addAction("녹색", sketch_paper_setter,
                    [this](){sketch_paper_setter->setColor(QColor(0, 255, 0));});
    menu.addSeparator();

    menu.addAction("두께 5", sketch_paper_setter,
                    [this](){sketch_paper_setter->setThick(5);});
    menu.addAction("두께 10", sketch_paper_setter,
                      [this](){sketch_paper_setter->setThick(10);});
    menu.addAction("두께 20", sketch_paper_setter,
                      [this](){sketch_paper_setter->setThick(20);});
    menu.addSeparator();

    menu.addAction("초기화", sketch_paper, [this](){sketch_paper->Clear();});

    menu.exec(mapToGlobal(pos));
}
