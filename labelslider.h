#ifndef LABELSLIDER_H
#define LABELSLIDER_H

#include <QLabel>
#include <QList>
#include <QMap>
#include <QSlider>
#include <QString>
#include <QWidget>
#include <functional>

class LabelSlider : public QWidget
{
    Q_OBJECT

  public:
    enum FormatType
    {
        SimpleFormat,
        PrefixSuffixFormat,
        PrintfFormat,
        CustomFunction,
        CustomMapping
    };

  public:
    explicit LabelSlider(QWidget *parent = nullptr);
    explicit LabelSlider(Qt::Orientation orientation = Qt::Horizontal, QWidget *parent = nullptr);

    ~LabelSlider();

    void setTickPosition(QSlider::TickPosition position);
    QSlider::TickPosition tickPosition() const;

    void setTickInterval(int ti);
    int tickInterval() const;

    void setOrientation(Qt::Orientation);
    Qt::Orientation orientation() const;

    void setMinimum(int);
    int minimum() const;

    void setMaximum(int);
    int maximum() const;

    void setSingleStep(int);
    int singleStep() const;

    void setPageStep(int);
    int pageStep() const;

    void setTracking(bool enable);
    bool hasTracking() const;

    void setSliderDown(bool);
    bool isSliderDown() const;

    void setSliderPosition(int);
    int sliderPosition() const;

    void setInvertedAppearance(bool);
    bool invertedAppearance() const;

    void setInvertedControls(bool);
    bool invertedControls() const;

    void setValue(int);
    int value() const;

    void setTickValuesVisible(bool visible);
    bool tickValuesVisible() const;

    void setRange(int min, int max);

    void triggerAction(QSlider::SliderAction action);

    void setFormatType(FormatType type);
    FormatType formatType() const;

    void setFormatSuffix(const QString &suffix);
    QString formatSuffix() const;

    void setFormatPrefixSuffix(const QString &prefix, const QString &suffix);
    QString formatPrefix() const;

    void setPrintfFormat(const QString &format);
    QString printfFormat() const;

    void setDecimalPlaces(int places);
    int decimalPlaces() const;

    void setValueScale(double scale);
    double valueScale() const;

    void setCustomFormatter(std::function<QString(int)> formatter);
    void setCustomLabels(const QMap<int, QString> &labels);
    QMap<int, QString> customLabels() const;
    void setCustomLabel(int value, const QString &label);
    void clearCustomLabels();

  signals:
    void valueChanged(int value);
    void sliderMoved(int position);
    void sliderPressed();
    void sliderReleased();
    void rangeChanged(int min, int max);
    void actionTriggered(QAbstractSlider::SliderAction action);

  private slots:
    void updateLabelPositions();
    
  private:
    void rebuildLabels();
    QString formatValue(int value) const;

    QSlider *m_slider;
    QList<QLabel *> m_labels;
    bool m_showTickValues = false;

    FormatType m_formatType = SimpleFormat;
    QString m_formatPrefix;
    QString m_formatSuffix;
    QString m_printfFormat = "%d";
    int m_decimalPlaces = 0;
    double m_valueScale = 1.0;
    std::function<QString(int)> m_customFormatter;
    QMap<int, QString> m_customLabels;

  protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // LABELSLIDER_H
