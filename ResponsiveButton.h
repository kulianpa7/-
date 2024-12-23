#ifndef RESPONSIVEBUTTON_H
#define RESPONSIVEBUTTON_H


#include <QPushButton>
#include <QResizeEvent>
#include <QFontMetrics>

class ResponsiveButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ResponsiveButton(QWidget *parent = nullptr)
        : QPushButton(parent) {}

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QPushButton::resizeEvent(event);

        // 動態調整字體大小
        QFont font = this->font();
        int buttonHeight = this->height();
        font.setPointSize(buttonHeight / 3); // 根據按鈕高度調整字體大小
        this->setFont(font);
    }
};


#endif // RESPONSIVEBUTTON_H
