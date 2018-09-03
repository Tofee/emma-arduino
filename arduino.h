#ifndef ARDUINO_H
#define ARDUINO_H

class MainWindow;

#include <QObject>

class Arduino : public QObject
{
    Q_OBJECT
public:
    explicit Arduino(MainWindow *parent = nullptr);

    void setup();

signals:

public slots:
    void loop();

private:
    void analogWrite(int &pin, int value);
    void delay(int ms);
};

#endif // ARDUINO_H
