## LabelSlider (Qt labeled slider with customizable tick values)

[English](README.md) | [中文](README_CN.md)

A Qt-based labeled slider widget that displays customizable formatted values at tick positions, providing enhanced user experience for value selection with visual feedback.

### Features

- 📊 Automatic label generation at slider tick positions
- 🎨 Multiple formatting types: Simple, Prefix/Suffix, Printf-style, Custom Function, and Custom Mapping
- 🔢 Flexible value scaling and decimal place control
- 📐 Support for both horizontal and vertical orientations
- 🎯 Configurable tick positions: Above, Below, Left, Right, or Both Sides
- ⚡ Real-time label updates when slider properties change
- 🔄 Compatible with Qt 5 and Qt 6

### Use Cases

- 🎚️ **Audio Controls**: Volume sliders with dB values, frequency controls with Hz labels
- 🌡️ **Temperature Controls**: Thermostats with °C/°F indicators
- 💰 **Financial Applications**: Price sliders with currency symbols
- 🎮 **Gaming Interfaces**: Settings panels with percentage or level indicators
- 📊 **Data Visualization**: Interactive charts with labeled value ranges
- ⚙️ **Engineering Tools**: Calibration interfaces with unit labels

### Requirements

- Qt 5.6+ or Qt 6.x (Widgets)
- C++11 or newer
- Platforms: Windows, macOS, Linux

### Integration

1. Copy `labelslider.h` and `labelslider.cpp` to your Qt project
2. Include the header file in your code:
   ```cpp
   #include "labelslider.h"
   ```
3. Add the files to your project's build system (CMake, qmake, etc.)

#### qmake (.pro)

```pro
QT += widgets

SOURCES += \
    labelslider.cpp

HEADERS += \
    labelslider.h
```

#### CMake (Qt 6)

```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_sources(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/labelslider.cpp
)

target_include_directories(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(your_target PRIVATE Qt6::Widgets)
```

#### CMake (Qt 5)

```cmake
find_package(Qt5 REQUIRED COMPONENTS Widgets)

target_sources(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/labelslider.cpp
)

target_include_directories(your_target PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(your_target PRIVATE Qt5::Widgets)
```

### Usage Examples

#### Basic Setup

```cpp
#include "labelslider.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class DemoWidget : public QWidget {
    Q_OBJECT
public:
    DemoWidget() {
        auto *layout = new QVBoxLayout(this);
        auto *valueLabel = new QLabel("Value: 0", this);
        auto *slider = new LabelSlider(Qt::Horizontal, this);

        // Basic configuration
        slider->setRange(-10, 10);
        slider->setTickInterval(5);
        slider->setTickPosition(QSlider::TicksBelow);
        slider->setTickValuesVisible(true);

        connect(slider, &LabelSlider::valueChanged, this, [valueLabel](int value) {
            valueLabel->setText(QString("Value: %1").arg(value));
        });

        layout->addWidget(valueLabel);
        layout->addWidget(slider);
        setLayout(layout);
    }
};
```

#### Detailed Formatting Examples

```cpp
LabelSlider *slider = new LabelSlider();
slider->setRange(-100, 100);
slider->setTickInterval(25);
slider->setTickPosition(QSlider::TicksBelow);
slider->setTickValuesVisible(true);

// 1. Simple suffix format
slider->setFormatType(LabelSlider::SimpleFormat);
slider->setFormatSuffix("°C");  // Displays: -100°C, -75°C, -50°C, -25°C, 0°C, 25°C, 50°C, 75°C, 100°C

// 2. Prefix and suffix format
slider->setFormatType(LabelSlider::PrefixSuffixFormat);
slider->setFormatPrefixSuffix("$", ".00");  // Displays: $-100.00, $-75.00, $-50.00, ..., $100.00

// 3. Printf-style formatting
slider->setFormatType(LabelSlider::PrintfFormat);
slider->setPrintfFormat("%+d dB");  // Displays: -100 dB, -75 dB, -50 dB, ..., +100 dB
// or with floating point:
slider->setPrintfFormat("%.1f°");   // Displays: -100.0°, -75.0°, -50.0°, ..., 100.0°

// 4. Value scaling with decimal places
slider->setValueScale(0.01);  // Scale integer values to decimal (divide by 100)
slider->setDecimalPlaces(2);  // Show two decimal places
slider->setFormatSuffix("%");
// Result: -1.00%, -0.75%, -0.50%, ..., 1.00%

// 5. Custom formatting function
slider->setFormatType(LabelSlider::CustomFunction);
slider->setCustomFormatter([](int value) -> QString {
    if (value == 0) return "Center";
    if (value > 0) return QString("Right +%1").arg(value);
    return QString("Left %1").arg(value);
});
// Result: "Left -100", "Left -75", ..., "Center", ..., "Right +75", "Right +100"

// 6. Completely custom label mapping
slider->setFormatType(LabelSlider::CustomMapping);
slider->setCustomLabel(-100, "Minimum");
slider->setCustomLabel(-50, "Low");
slider->setCustomLabel(0, "Normal");
slider->setCustomLabel(50, "High");
slider->setCustomLabel(100, "Maximum");
// Result: "Minimum", "Low", "Normal", "High", "Maximum"

// 7. Audio volume example with logarithmic feel
LabelSlider *volumeSlider = new LabelSlider();
volumeSlider->setRange(0, 100);
volumeSlider->setTickInterval(20);
volumeSlider->setFormatType(LabelSlider::CustomFunction);
volumeSlider->setCustomFormatter([](int value) -> QString {
    if (value == 0) return "Mute";
    // Convert linear slider to logarithmic dB scale
    double db = 20.0 * log10(value / 100.0);
    return QString("%1 dB").arg(db, 0, 'f', 1);
});

// 8. Temperature with different scales
LabelSlider *tempSlider = new LabelSlider();
tempSlider->setRange(-40, 50);  // Celsius range
tempSlider->setTickInterval(15);
tempSlider->setFormatType(LabelSlider::CustomFunction);
tempSlider->setCustomFormatter([](int celsius) -> QString {
    int fahrenheit = celsius * 9 / 5 + 32;
    return QString("%1°C (%2°F)").arg(celsius).arg(fahrenheit);
});
```

### API Overview

#### Constructors
- `LabelSlider(QWidget *parent = nullptr)`
- `LabelSlider(Qt::Orientation orientation, QWidget *parent = nullptr)`

#### Slider Properties
- `void setRange(int min, int max)`
- `void setMinimum(int min)` / `int minimum() const`
- `void setMaximum(int max)` / `int maximum() const`
- `void setValue(int value)` / `int value() const`
- `void setOrientation(Qt::Orientation)` / `Qt::Orientation orientation() const`

#### Tick Configuration
- `void setTickPosition(QSlider::TickPosition position)` / `QSlider::TickPosition tickPosition() const`
- `void setTickInterval(int interval)` / `int tickInterval() const`
- `void setTickValuesVisible(bool visible)` / `bool tickValuesVisible() const`

#### Formatting Options
- `void setFormatType(FormatType type)` / `FormatType formatType() const`
- `void setFormatSuffix(const QString &suffix)` / `QString formatSuffix() const`
- `void setFormatPrefixSuffix(const QString &prefix, const QString &suffix)`
- `QString formatPrefix() const`
- `void setPrintfFormat(const QString &format)` / `QString printfFormat() const`
- `void setDecimalPlaces(int places)` / `int decimalPlaces() const`
- `void setValueScale(double scale)` / `double valueScale() const`

#### Custom Formatting
- `void setCustomFormatter(std::function<QString(int)> formatter)`
- `void setCustomLabels(const QMap<int, QString> &labels)` / `QMap<int, QString> customLabels() const`
- `void setCustomLabel(int value, const QString &label)`
- `void clearCustomLabels()`

#### Signals
- `void valueChanged(int value)`
- `void sliderMoved(int position)`
- `void sliderPressed()`
- `void sliderReleased()`
- `void rangeChanged(int min, int max)`
- `void actionTriggered(QAbstractSlider::SliderAction action)`

### Format Types

1. **SimpleFormat**: Value + suffix (e.g., "25°C")
2. **PrefixSuffixFormat**: Prefix + value + suffix (e.g., "$25.00")
3. **PrintfFormat**: Printf-style formatting (e.g., "%+d dB" → "+25 dB")
4. **CustomFunction**: User-defined formatting function
5. **CustomMapping**: Direct value-to-string mapping

### Notes

- This widget uses `Q_OBJECT` and custom signals, so MOC must run (build as part of a Qt project).
- Labels are automatically positioned based on tick position and slider orientation.
- When `tickValuesVisible()` is false, no labels are shown regardless of other settings.
- The widget automatically rebuilds labels when relevant properties change.
- For vertical sliders, labels on the left are right-aligned, and labels on the right are left-aligned.

### Tips

- Use `setValueScale()` to convert integer slider values to meaningful decimal ranges
- Combine `setDecimalPlaces()` with `setValueScale()` for precise decimal formatting
- Custom formatters provide the most flexibility for complex formatting needs
- For performance with many labels, consider using fewer tick intervals

### Roadmap / Ideas

- Support for non-uniform tick spacing
- Optional label rotation for compact display
- Rich text formatting support in labels
- Animated label updates
- Theme-aware styling options

### Contributing

Issues and pull requests are welcome. Please include:
- Clear description of the issue or enhancement
- Reproduction steps (if applicable)
- Platform and Qt version information
- Code examples when relevant 