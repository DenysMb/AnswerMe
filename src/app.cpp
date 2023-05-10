// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2023 Denys Madureira <denysmb@zoho.com>

#include "app.h"
#include <KSharedConfig>
#include <KWindowConfig>
#include <QQuickWindow>
#include <iostream>
#include <cstdlib>
#include <ctime>

struct Magic8Ball {
    QString text;
    QString color;
};

Magic8Ball answers[] = {
    {"Signs point to yes.", "green"},
    {"Outlook good.", "green"},
    {"Reply hazy, try again.", "gold"},
    {"Better not tell you now.", "gold"},
    {"Concentrate and ask again.", "gold"},
    {"Very doubtful.", "red"},
    {"Cannot predict now.", "gold"},
    {"My sources say no.", "red"},
    {"As I see it, yes.", "green"},
    {"Don't count on it.", "red"},
    {"Most likely.", "green"},
    {"Ask again later.", "gold"},
    {"Outlook not so good.", "red"},
    {"My reply is no.", "red"},
    {"Yes, definitely.", "green"},
    {"It is certain.", "green"},
    {"Without a doubt.", "green"},
    {"You may rely on it.", "green"},
    {"Yes, absolutely.", "green"},
    {"It is decidedly so.", "green"}
};

int size = sizeof(answers) / sizeof(answers[0]);

int lastSelectedIndex = -1;

void selectRandomAnswer(Magic8Ball& selectedAnswer) {
    srand(time(0)); // Seed the random number generator
    int index = lastSelectedIndex;
    while (index == lastSelectedIndex) {
        index = rand() % size; // Generate a random index
    }
    lastSelectedIndex = index; // Remember the last selected index
    selectedAnswer = answers[index]; // Select the answer at the random index
}

void App::restoreWindowGeometry(QQuickWindow *window, const QString &group) const
{
    KConfig dataResource(QStringLiteral("data"), KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    KConfigGroup windowGroup(&dataResource, QStringLiteral("Window-") + group);
    KWindowConfig::restoreWindowSize(window, windowGroup);
    KWindowConfig::restoreWindowPosition(window, windowGroup);
}

void App::saveWindowGeometry(QQuickWindow *window, const QString &group) const
{
    KConfig dataResource(QStringLiteral("data"), KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    KConfigGroup windowGroup(&dataResource, QStringLiteral("Window-") + group);
    KWindowConfig::saveWindowPosition(window, windowGroup);
    KWindowConfig::saveWindowSize(window, windowGroup);
    dataResource.sync();
}

void App::generateAnswer(QObject *textObject) const
{
    Magic8Ball selectedAnswer;
    selectRandomAnswer(selectedAnswer);

    QString answer = selectedAnswer.text;
    QString color = selectedAnswer.color;

    qDebug() << "Selected answer: " << selectedAnswer.text;
    qDebug() << "Color: " << selectedAnswer.color;

    textObject->setProperty("text", answer);
    textObject->setProperty("color", color);
}
