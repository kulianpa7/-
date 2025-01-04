#ifndef SCROLLAREAWIDGET_H
#define SCROLLAREAWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>

class ScrollAreaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollAreaWidget(QWidget *parent = nullptr);
    void updateContent(int pageType); // 新增函數
    ~ScrollAreaWidget();

private:
    void loadOrdersFromDatabase(QVBoxLayout *containerLayout, int pageType);
    void clear();
    void updateOrderStatus(int orderId, int status);
    QScrollArea *scrollArea;
    QVBoxLayout *mainLayout;
};

#endif // SCROLLAREAWIDGET_H
