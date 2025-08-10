#include "labelslider.h"
#include <QGridLayout>
#include <cmath>

LabelSlider::LabelSlider(Qt::Orientation orientation, QWidget *parent) : QWidget(parent)
{
    m_slider = new QSlider(orientation, this);

    connect(m_slider, &QSlider::valueChanged, this, [this](int value) { emit valueChanged(value); });
    connect(m_slider, &QSlider::sliderMoved, this, [this](int position) { emit sliderMoved(position); });
    connect(m_slider, &QSlider::sliderPressed, this, [this]() { emit sliderPressed(); });
    connect(m_slider, &QSlider::sliderReleased, this, [this]() { emit sliderReleased(); });
    connect(m_slider, &QSlider::rangeChanged, this, [this](int min, int max) { emit rangeChanged(min, max); });
    connect(m_slider, &QSlider::actionTriggered, this,
            [this](int action) { emit actionTriggered(static_cast<QAbstractSlider::SliderAction>(action)); });

    rebuildLabels();
}

LabelSlider::LabelSlider(QWidget *parent) : QWidget(parent)
{
    m_slider = new QSlider(this);

    connect(m_slider, &QSlider::valueChanged, this, [this](int value) { emit valueChanged(value); });
    connect(m_slider, &QSlider::sliderMoved, this, [this](int position) { emit sliderMoved(position); });
    connect(m_slider, &QSlider::sliderPressed, this, [this]() { emit sliderPressed(); });
    connect(m_slider, &QSlider::sliderReleased, this, [this]() { emit sliderReleased(); });
    connect(m_slider, &QSlider::rangeChanged, this, [this](int min, int max) { emit rangeChanged(min, max); });
    connect(m_slider, &QSlider::actionTriggered, this,
            [this](int action) { emit actionTriggered(static_cast<QAbstractSlider::SliderAction>(action)); });

    rebuildLabels();
}

LabelSlider::~LabelSlider()
{
    delete m_slider;
    qDeleteAll(m_labels);
}

void LabelSlider::setTickPosition(QSlider::TickPosition position)
{
    m_slider->setTickPosition(position);
    rebuildLabels();
}

QSlider::TickPosition LabelSlider::tickPosition() const
{
    return m_slider->tickPosition();
}

void LabelSlider::setTickInterval(int ti)
{
    m_slider->setTickInterval(ti);
    rebuildLabels();
}

int LabelSlider::tickInterval() const
{
    return m_slider->tickInterval();
}

void LabelSlider::setOrientation(Qt::Orientation orientation)
{
    m_slider->setOrientation(orientation);
    rebuildLabels();
}

Qt::Orientation LabelSlider::orientation() const
{
    return m_slider->orientation();
}

void LabelSlider::setMinimum(int min)
{
    m_slider->setMinimum(min);
    rebuildLabels();
}

int LabelSlider::minimum() const
{
    return m_slider->minimum();
}

void LabelSlider::setMaximum(int max)
{
    m_slider->setMaximum(max);
    rebuildLabels();
}

int LabelSlider::maximum() const
{
    return m_slider->maximum();
}

void LabelSlider::setSingleStep(int step)
{
    m_slider->setSingleStep(step);
}

int LabelSlider::singleStep() const
{
    return m_slider->singleStep();
}

void LabelSlider::setPageStep(int step)
{
    m_slider->setPageStep(step);
}

int LabelSlider::pageStep() const
{
    return m_slider->pageStep();
}

void LabelSlider::setTracking(bool enable)
{
    m_slider->setTracking(enable);
}

bool LabelSlider::hasTracking() const
{
    return m_slider->hasTracking();
}

void LabelSlider::setSliderDown(bool down)
{
    m_slider->setSliderDown(down);
}

bool LabelSlider::isSliderDown() const
{
    return m_slider->isSliderDown();
}

void LabelSlider::setSliderPosition(int position)
{
    m_slider->setSliderPosition(position);
}

int LabelSlider::sliderPosition() const
{
    return m_slider->sliderPosition();
}

void LabelSlider::setInvertedAppearance(bool inverted)
{
    m_slider->setInvertedAppearance(inverted);
}

bool LabelSlider::invertedAppearance() const
{
    return m_slider->invertedAppearance();
}

void LabelSlider::setInvertedControls(bool inverted)
{
    m_slider->setInvertedControls(inverted);
}

bool LabelSlider::invertedControls() const
{
    return m_slider->invertedControls();
}

void LabelSlider::setValue(int v)
{
    m_slider->setValue(v);
}

int LabelSlider::value() const
{
    return m_slider->value();
}

void LabelSlider::setTickValuesVisible(bool visible)
{
    if (m_showTickValues != visible)
    {
        m_showTickValues = visible;
        rebuildLabels();
    }
}

bool LabelSlider::tickValuesVisible() const
{
    return m_showTickValues;
}

void LabelSlider::setRange(int min, int max)
{
    m_slider->setRange(min, max);
    rebuildLabels();
}

void LabelSlider::triggerAction(QSlider::SliderAction action)
{
    m_slider->triggerAction(action);
}

void LabelSlider::setFormatType(FormatType type)
{
    if (m_formatType != type)
    {
        m_formatType = type;
        rebuildLabels();
    }
}

LabelSlider::FormatType LabelSlider::formatType() const
{
    return m_formatType;
}

void LabelSlider::setFormatSuffix(const QString &suffix)
{
    if (m_formatSuffix != suffix)
    {
        m_formatSuffix = suffix;
        if (m_formatType == SimpleFormat)
        {
            rebuildLabels();
        }
    }
}

QString LabelSlider::formatSuffix() const
{
    return m_formatSuffix;
}

void LabelSlider::setFormatPrefixSuffix(const QString &prefix, const QString &suffix)
{
    bool changed = (m_formatPrefix != prefix || m_formatSuffix != suffix);
    m_formatPrefix = prefix;
    m_formatSuffix = suffix;
    if (changed && m_formatType == PrefixSuffixFormat)
    {
        rebuildLabels();
    }
}

QString LabelSlider::formatPrefix() const
{
    return m_formatPrefix;
}

void LabelSlider::setPrintfFormat(const QString &format)
{
    if (m_printfFormat != format)
    {
        m_printfFormat = format;
        if (m_formatType == PrintfFormat)
        {
            rebuildLabels();
        }
    }
}

QString LabelSlider::printfFormat() const
{
    return m_printfFormat;
}

void LabelSlider::setDecimalPlaces(int places)
{
    if (m_decimalPlaces != places)
    {
        m_decimalPlaces = qMax(0, places);
        rebuildLabels();
    }
}

int LabelSlider::decimalPlaces() const
{
    return m_decimalPlaces;
}

void LabelSlider::setValueScale(double scale)
{
    if (qAbs(m_valueScale - scale) > 1e-6)
    {
        m_valueScale = scale;
        rebuildLabels();
    }
}

double LabelSlider::valueScale() const
{
    return m_valueScale;
}

void LabelSlider::setCustomFormatter(std::function<QString(int)> formatter)
{
    m_customFormatter = formatter;
    if (m_formatType == CustomFunction)
    {
        rebuildLabels();
    }
}

void LabelSlider::setCustomLabels(const QMap<int, QString> &labels)
{
    m_customLabels = labels;
    if (m_formatType == CustomMapping)
    {
        rebuildLabels();
    }
}

QMap<int, QString> LabelSlider::customLabels() const
{
    return m_customLabels;
}

void LabelSlider::setCustomLabel(int value, const QString &label)
{
    m_customLabels[value] = label;
    if (m_formatType == CustomMapping)
    {
        rebuildLabels();
    }
}

void LabelSlider::clearCustomLabels()
{
    m_customLabels.clear();
    if (m_formatType == CustomMapping)
    {
        rebuildLabels();
    }
}

QString LabelSlider::formatValue(int value) const
{
    switch (m_formatType)
    {
    case SimpleFormat:
        if (m_decimalPlaces > 0)
        {
            double scaledValue = value * m_valueScale;
            return QString::number(scaledValue, 'f', m_decimalPlaces) + m_formatSuffix;
        }
        else
        {
            int scaledValue = static_cast<int>(value * m_valueScale);
            return QString::number(scaledValue) + m_formatSuffix;
        }

    case PrefixSuffixFormat:
        if (m_decimalPlaces > 0)
        {
            double scaledValue = value * m_valueScale;
            return m_formatPrefix + QString::number(scaledValue, 'f', m_decimalPlaces) + m_formatSuffix;
        }
        else
        {
            int scaledValue = static_cast<int>(value * m_valueScale);
            return m_formatPrefix + QString::number(scaledValue) + m_formatSuffix;
        }

    case PrintfFormat: {
        double scaledValue = value * m_valueScale;
        if (m_printfFormat.contains('f') || m_printfFormat.contains('e') || m_printfFormat.contains('g'))
        {
            return QString::asprintf(m_printfFormat.toLocal8Bit().data(), scaledValue);
        }
        else
        {
            return QString::asprintf(m_printfFormat.toLocal8Bit().data(), static_cast<int>(scaledValue));
        }
    }

    case CustomFunction:
        if (m_customFormatter)
        {
            return m_customFormatter(value);
        }
        return QString::number(value);

    case CustomMapping:
        if (m_customLabels.contains(value))
        {
            return m_customLabels[value];
        }
        return QString::number(static_cast<int>(value * m_valueScale));
    }

    return QString::number(value);
}

void LabelSlider::rebuildLabels()
{
    if (this->layout())
    {
        delete this->layout();
    }
    qDeleteAll(m_labels);
    m_labels.clear();

    int span = m_slider->maximum() - m_slider->minimum();
    QGridLayout *grid = new QGridLayout(this);

    if (m_slider->tickPosition() == QSlider::NoTicks || m_slider->tickInterval() <= 0 || span <= 0 || !m_showTickValues)
    {
        grid->addWidget(m_slider, 0, 0);
        return;
    }

    int steps = span / m_slider->tickInterval();
    int count = steps + 1;
    QSlider::TickPosition tickPos = m_slider->tickPosition();

    if (m_slider->orientation() == Qt::Horizontal)
    {
        switch (tickPos)
        {
        case QSlider::TicksAbove:
            grid->addWidget(m_slider, 1, 0, 1, count);
            for (int i = 0; i < count; ++i)
            {
                int val = m_slider->minimum() + i * m_slider->tickInterval();
                QLabel *lbl = new QLabel(formatValue(val), this);
                lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                grid->addWidget(lbl, 0, i);
                m_labels.append(lbl);
            }
            break;

        case QSlider::TicksBelow:
            grid->addWidget(m_slider, 0, 0, 1, count);
            for (int i = 0; i < count; ++i)
            {
                int val = m_slider->minimum() + i * m_slider->tickInterval();
                QLabel *lbl = new QLabel(formatValue(val), this);
                lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                grid->addWidget(lbl, 1, i);
                m_labels.append(lbl);
            }
            break;

        case QSlider::TicksBothSides:
            grid->addWidget(m_slider, 1, 0, 1, count);
            for (int i = 0; i < count; ++i)
            {
                int val = m_slider->minimum() + i * m_slider->tickInterval();

                QLabel *lblTop = new QLabel(formatValue(val), this);
                lblTop->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                grid->addWidget(lblTop, 0, i);
                m_labels.append(lblTop);

                QLabel *lblBottom = new QLabel(formatValue(val), this);
                lblBottom->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                grid->addWidget(lblBottom, 2, i);
                m_labels.append(lblBottom);
            }
            break;

        default:
            grid->addWidget(m_slider, 0, 0);
            break;
        }
    }
    else
    {
        switch (tickPos)
        {
        case QSlider::TicksLeft:
            grid->addWidget(m_slider, 0, 1, count, 1);
            for (int i = 0; i < count; ++i)
            {
                int val = m_slider->minimum() + i * m_slider->tickInterval();
                QLabel *lbl = new QLabel(formatValue(val), this);
                lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                grid->addWidget(lbl, count - 1 - i, 0);
                m_labels.append(lbl);
            }
            break;

        case QSlider::TicksRight:
            grid->addWidget(m_slider, 0, 0, count, 1);
            for (int i = 0; i < count; ++i)
            {
                int val = m_slider->minimum() + i * m_slider->tickInterval();
                QLabel *lbl = new QLabel(formatValue(val), this);
                lbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                grid->addWidget(lbl, count - 1 - i, 1);
                m_labels.append(lbl);
            }
            break;

        case QSlider::TicksBothSides:
            grid->addWidget(m_slider, 0, 1, count, 1);
            for (int i = 0; i < count; ++i)
            {
                int val = m_slider->minimum() + i * m_slider->tickInterval();

                QLabel *lblLeft = new QLabel(formatValue(val), this);
                lblLeft->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                grid->addWidget(lblLeft, count - 1 - i, 0);
                m_labels.append(lblLeft);

                QLabel *lblRight = new QLabel(formatValue(val), this);
                lblRight->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                grid->addWidget(lblRight, count - 1 - i, 2);
                m_labels.append(lblRight);
            }
            break;

        default:
            grid->addWidget(m_slider, 0, 0);
            break;
        }
    }
}
