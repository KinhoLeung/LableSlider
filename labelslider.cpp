#include "labelslider.h"
#include <QGridLayout>
#include <QStyle>
#include <QStyleOptionSlider>
#include <QTimer>

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
    rebuildLabels();
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

    const int interval = m_slider->tickInterval();
    const int steps = span / interval;
    const int count = steps + 1;
    const int min = m_slider->minimum();
    QSlider::TickPosition tickPos = m_slider->tickPosition();

    auto makeLabel = [&](QWidget *bar, int val) {
        QLabel *lbl = new QLabel(formatValue(val), bar);
        lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        lbl->setProperty("ls_value", val);
        lbl->adjustSize();
        m_labels.append(lbl);
        return lbl;
    };

    if (m_slider->orientation() == Qt::Horizontal)
    {
        int row = 0;
        if (tickPos == QSlider::TicksAbove || tickPos == QSlider::TicksBothSides)
        {
            QWidget *topBar = new QWidget(this);
            topBar->setProperty("ls_side", "top");
            topBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            int maxH = 0;
            for (int i = 0; i < count; ++i)
            {
                auto *lbl = makeLabel(topBar, min + i * interval);
                maxH = qMax(maxH, lbl->height());
            }

            topBar->setMinimumHeight(maxH);
            grid->addWidget(topBar, row, 0);
            grid->setRowStretch(row, 0);
            ++row;
        }

        grid->addWidget(m_slider, row, 0);
        grid->setRowStretch(row, 1);
        ++row;

        if (tickPos == QSlider::TicksBelow || tickPos == QSlider::TicksBothSides)
        {
            QWidget *bottomBar = new QWidget(this);
            bottomBar->setProperty("ls_side", "bottom");
            bottomBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            int maxH = 0;
            for (int i = 0; i < count; ++i)
            {
                auto *lbl = makeLabel(bottomBar, min + (count - 1 - i) * interval);
                maxH = qMax(maxH, lbl->height());
            }

            bottomBar->setMinimumHeight(maxH);
            grid->addWidget(bottomBar, row, 0);
            grid->setRowStretch(row, 0);
        }
    }
    else
    {
        int column = 0;
        if (tickPos == QSlider::TicksLeft || tickPos == QSlider::TicksBothSides)
        {
            QWidget *leftBar = new QWidget(this);
            leftBar->setProperty("ls_side", "left");
            leftBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
            int maxW = 0;
            for (int i = 0; i < count; ++i)
            {
                auto *lbl = makeLabel(leftBar, min + i * interval);
                maxW = qMax(maxW, lbl->width());
            }

            leftBar->setMinimumWidth(maxW);
            grid->addWidget(leftBar, 0, column);
            grid->setColumnStretch(column, 0);
            ++column;
        }

        grid->addWidget(m_slider, 0, column);
        grid->setColumnStretch(column, 1);
        ++column;

        if (tickPos == QSlider::TicksRight || tickPos == QSlider::TicksBothSides)
        {
            QWidget *rightBar = new QWidget(this);
            rightBar->setProperty("ls_side", "right");
            rightBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
            int maxW = 0;
            for (int i = 0; i < count; ++i)
            {
                auto *lbl = makeLabel(rightBar, min + (count - 1 - i) * interval);
                maxW = qMax(maxW, lbl->width());
            }
            rightBar->setMinimumWidth(maxW);
            grid->addWidget(rightBar, 0, column);
            grid->setColumnStretch(column, 0);
        }
    }

    QTimer::singleShot(0, this, &LabelSlider::updateLabelPositions);
}

void LabelSlider::updateLabelPositions()
{
    if (m_labels.isEmpty())
        return;

    QStyleOptionSlider opt;
    opt.initFrom(m_slider);
    opt.orientation = m_slider->orientation();
    opt.minimum = m_slider->minimum();
    opt.maximum = m_slider->maximum();
    opt.singleStep = m_slider->singleStep();
    opt.pageStep = m_slider->pageStep();
    opt.sliderPosition = m_slider->sliderPosition();
    opt.sliderValue = m_slider->value();
    opt.tickPosition = m_slider->tickPosition();
    opt.tickInterval = m_slider->tickInterval();
    opt.upsideDown =
        (opt.orientation == Qt::Horizontal) ? m_slider->invertedAppearance() : !m_slider->invertedAppearance();

    const QRect sliderGroove =
        m_slider->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, m_slider);
    const int sliderLength = m_slider->style()->pixelMetric(QStyle::PM_SliderLength, &opt, m_slider);
    const int space = (opt.orientation == Qt::Horizontal) ? (sliderGroove.width() - sliderLength)
                                                          : (sliderGroove.height() - sliderLength);

    for (auto it = m_labels.cbegin(); it != m_labels.cend(); ++it)
    {
        QLabel *lbl = *it;
        if (!lbl)
            continue;

        const int val = lbl->property("ls_value").toInt();
        const int pos = QStyle::sliderPositionFromValue(opt.minimum, opt.maximum, val, space, opt.upsideDown);
        QWidget *bar = qobject_cast<QWidget *>(lbl->parent());
        if (!bar)
            continue;

        if (m_slider->orientation() == Qt::Horizontal)
        {
            const int baseX = m_slider->x() + sliderGroove.x() - bar->x() + sliderLength / 2;
            int x = baseX + pos - lbl->width() / 2;
            x = qBound(0, x, bar->width() - lbl->width());
            const int y = (bar->height() - lbl->height()) / 2;
            lbl->move(x, y);
        }
        else
        {
            const QString side = bar->property("ls_side").toString();
            const int baseY = m_slider->y() + sliderGroove.y() - bar->y() + sliderLength / 2;
            int y = baseY + pos - lbl->height() / 2;
            y = qBound(0, y, bar->height() - lbl->height());
            const int x = (side == "left") ? (bar->width() - lbl->width()) : 0;
            lbl->move(x, y);
        }
    }
}

void LabelSlider::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateLabelPositions();
}