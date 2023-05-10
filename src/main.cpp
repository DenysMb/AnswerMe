/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2023 Denys Madureira <denysmb@zoho.com>
*/

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QtQml>

#include "about.h"
#include "app.h"
#include "version-answerme.h"
#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedString>

#include "answermeconfig.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("KDE"));
    QCoreApplication::setApplicationName(QStringLiteral("AnswerMe"));

    KAboutData aboutData(
                         // The program name used internally.
                         QStringLiteral("AnswerMe"),
                         // A displayable program name string.
                         i18nc("@title", "AnswerMe"),
                         // The program version string.
                         QStringLiteral(ANSWERME_VERSION_STRING),
                         // Short description of what the app does.
                         i18n("Application Description"),
                         // The license this code is released under.
                         KAboutLicense::GPL,
                         // Copyright Statement.
                         i18n("(c) 2023"));
    aboutData.addAuthor(i18nc("@info:credit", "Denys Madureira"),
                        i18nc("@info:credit", "Author Role"),
                        QStringLiteral("denysmb@zoho.com"),
                        QStringLiteral("https://yourwebsite.com"));
    KAboutData::setApplicationData(aboutData);

    QQmlApplicationEngine engine;

    auto config = AnswerMeConfig::self();

    qmlRegisterSingletonInstance("org.kde.AnswerMe", 1, 0, "Config", config);

    AboutType about;
    qmlRegisterSingletonInstance("org.kde.AnswerMe", 1, 0, "AboutType", &about);

    App application;
    qmlRegisterSingletonInstance("org.kde.AnswerMe", 1, 0, "App", &application);

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
