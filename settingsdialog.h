#pragma once

#include <QDialog>

class QSpinBox;

/// Einstellungsdialog für Scheibenzahl und Zugdauer.
class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    /// @param currentDisks aktuelle Scheibenzahl
    /// @param currentDurationMs aktuelle Zugdauer in Millisekunden
    explicit SettingsDialog(int currentDisks, int currentDurationMs, QWidget* parent = nullptr);

    int diskCount() const;
    int moveDurationMs() const;

private:
    QSpinBox* m_diskSpin = nullptr;
    QSpinBox* m_durationSpin = nullptr;
};
