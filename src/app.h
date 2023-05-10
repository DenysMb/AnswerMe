// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2023 Denys Madureira <denysmb@zoho.com>

#pragma once

#include <QObject>

class QQuickWindow;

class App : public QObject
{
    Q_OBJECT

public:
    // Restore current window geometry
    Q_INVOKABLE void restoreWindowGeometry(QQuickWindow *window, const QString &group = QStringLiteral("main")) const;
    // Save current window geometry
    Q_INVOKABLE void saveWindowGeometry(QQuickWindow *window, const QString &group = QStringLiteral("main")) const;
    // Generate answer
    Q_INVOKABLE void generateAnswer(QObject *textObject) const;
};
