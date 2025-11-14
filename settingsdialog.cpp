#include "settingsdialog.h"
#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>

SettingsDialog::SettingsDialog(int currentDisks, int currentDurationMs, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Einstellungen");

    auto* layout = new QFormLayout(this);

    m_diskSpin = new QSpinBox(this);
    m_diskSpin->setRange(1, 12);
    m_diskSpin->setValue(currentDisks);

    m_durationSpin = new QSpinBox(this);
    m_durationSpin->setRange(100, 5000);
    m_durationSpin->setSingleStep(100);
    m_durationSpin->setValue(currentDurationMs);

    layout->addRow("Anzahl Scheiben:", m_diskSpin);
    layout->addRow("Zugdauer [ms]:", m_durationSpin);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int SettingsDialog::diskCount() const
{
    return m_diskSpin->value();
}

int SettingsDialog::moveDurationMs() const
{
    return m_durationSpin->value();
}
