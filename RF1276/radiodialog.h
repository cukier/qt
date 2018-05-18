#ifndef RADIODIALOG_H
#define RADIODIALOG_H

#include <QWidget>

#include "rf1276.h"

namespace Ui {
class RadioDialog;
}

class RadioDialog : public QWidget
{
    Q_OBJECT

public:
    struct RadioSettings {
        int baudRate = 0;
        int parity = 0;
        int rfFactor = 0;
        int mode = 0;
        int rfBw = 0;
        int id = 0;
        int NetId = 0;
        int rfPower = 0;
        float freq = 0.0;
    };

    explicit RadioDialog(QWidget *parent = 0);
    ~RadioDialog();

    RadioSettings settings() const;

    void setSettings(const RadioSettings &settings);

private:
    Ui::RadioDialog *ui;
    RadioSettings m_settings;
};

#endif // RADIODIALOG_H
