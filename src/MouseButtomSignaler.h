#include <QtWidgets>
/**
 * @brief The MouseButtonSignaler class
 * Coisa muito útil para fazer labels, por exemplo executarem clicks.
 */
class MouseButtonSignaler : public QObject {
  Q_OBJECT
  bool eventFilter(QObject * obj, QEvent * ev) Q_DECL_OVERRIDE {
    if ((ev->type() == QEvent::MouseButtonPress
        || ev->type() == QEvent::MouseButtonRelease
        || ev->type() == QEvent::MouseButtonDblClick)
        && obj->isWidgetType())
      emit mouseButtonEvent(static_cast<QWidget*>(obj),
                            static_cast<QMouseEvent*>(ev));
    return false;
  }
public:
  Q_SIGNAL void mouseButtonEvent(QWidget *, QMouseEvent *);
  MouseButtonSignaler(QObject * parent = 0) : QObject(parent) {}
  void installOn(QWidget * widget) {
    widget->installEventFilter(this);
  }
};
