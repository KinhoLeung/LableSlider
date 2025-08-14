#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "labelslider.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LabelSlider *labelSlider1 = new LabelSlider(Qt::Horizontal, this);
    labelSlider1->setRange(0, 100);
    labelSlider1->setTickInterval(20);
    labelSlider1->setTickPosition(QSlider::TicksAbove);
    labelSlider1->setTickValuesVisible(true);
    labelSlider1->setFormatType(LabelSlider::SimpleFormat);
    labelSlider1->setFormatSuffix("°C");
    ui->verticalLayout->addWidget(labelSlider1);

    LabelSlider *labelSlider2 = new LabelSlider(Qt::Horizontal, this);
    labelSlider2->setRange(0, 100);
    labelSlider2->setTickInterval(20);
    labelSlider2->setTickPosition(QSlider::TicksAbove);
    labelSlider2->setTickValuesVisible(true);
    labelSlider2->setFormatType(LabelSlider::PrefixSuffixFormat);
    labelSlider2->setFormatPrefixSuffix("$", ".00");
    ui->verticalLayout->addWidget(labelSlider2);

    LabelSlider *labelSlider3 = new LabelSlider(Qt::Horizontal, this);
    labelSlider3->setRange(0, 100);
    labelSlider3->setTickInterval(20);
    labelSlider3->setTickPosition(QSlider::TicksBothSides);
    labelSlider3->setTickValuesVisible(true);
    labelSlider3->setFormatType(LabelSlider::PrintfFormat);
    labelSlider3->setPrintfFormat("%+d dB");
    ui->verticalLayout->addWidget(labelSlider3);

    LabelSlider *labelSlider4 = new LabelSlider(Qt::Horizontal, this);
    labelSlider4->setRange(0, 100);
    labelSlider4->setTickInterval(20);
    labelSlider4->setTickPosition(QSlider::TicksBelow);
    labelSlider4->setTickValuesVisible(true);
    labelSlider4->setFormatType(LabelSlider::SimpleFormat);
    labelSlider4->setValueScale(0.01);
    labelSlider4->setDecimalPlaces(2);
    labelSlider4->setFormatSuffix("%");
    ui->verticalLayout->addWidget(labelSlider4);

    LabelSlider *labelSlider5 = new LabelSlider(Qt::Horizontal, this);
    labelSlider5->setRange(0, 100);
    labelSlider5->setTickInterval(20);
    labelSlider5->setTickPosition(QSlider::TicksBelow);
    labelSlider5->setTickValuesVisible(true);
    labelSlider5->setFormatType(LabelSlider::CustomFunction);
    labelSlider5->setCustomFormatter([](int value) -> QString {
        if (value == 50)
            return "中心";
        if (value > 50)
            return QString("右侧 +%1").arg(value);
        return QString("左侧 %1").arg(value);
    });
    ui->verticalLayout->addWidget(labelSlider5);

    LabelSlider *labelSlider6 = new LabelSlider(Qt::Vertical, this);
    labelSlider6->setRange(0, 100);
    labelSlider6->setTickInterval(20);
    labelSlider6->setTickPosition(QSlider::TicksLeft);
    labelSlider6->setTickValuesVisible(true);
    labelSlider6->setFormatType(LabelSlider::CustomMapping);
    labelSlider6->setCustomLabel(0, "最小值");
    labelSlider6->setCustomLabel(20, "低");
    labelSlider6->setCustomLabel(40, "正常");
    labelSlider6->setCustomLabel(60, "正常");
    labelSlider6->setCustomLabel(80, "高");
    labelSlider6->setCustomLabel(100, "最大值");
    ui->horizontalLayout->addWidget(labelSlider6);

    LabelSlider *labelSlider7 = new LabelSlider(Qt::Vertical, this);
    labelSlider7->setRange(0, 100);
    labelSlider7->setTickInterval(20);
    labelSlider7->setTickPosition(QSlider::TicksBothSides);
    labelSlider7->setTickValuesVisible(true);
    labelSlider7->setFormatType(LabelSlider::CustomFunction);
    labelSlider7->setCustomFormatter([](int value) -> QString {
        if (value == 0)
            return "静音";
        double db = 20.0 * log10(value / 100.0);
        return QString("%1 dB").arg(db, 0, 'f', 1);
    });
    ui->horizontalLayout->addWidget(labelSlider7);

    LabelSlider *labelSlider8 = new LabelSlider(Qt::Vertical, this);
    labelSlider8->setRange(0, 100);
    labelSlider8->setTickInterval(20);
    labelSlider8->setTickPosition(QSlider::TicksRight);
    labelSlider8->setTickValuesVisible(true);
    labelSlider8->setFormatType(LabelSlider::CustomFunction);
    labelSlider8->setCustomFormatter([](int celsius) -> QString {
        int fahrenheit = celsius * 9 / 5 + 32;
        return QString("%1°C (%2°F)").arg(celsius).arg(fahrenheit);
    });
    ui->horizontalLayout->addWidget(labelSlider8);
}

MainWindow::~MainWindow()
{
    delete ui;
}
