# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023 Denys Madureira <denysmb@zoho.com>

add_executable(answerme
    main.cpp
    about.cpp
    app.cpp
    resources.qrc)

target_link_libraries(answerme
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Svg
    KF5::I18n
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::ConfigGui)

if (ANDROID)
    kirigami_package_breeze_icons(ICONS
        list-add
        help-about
        application-exit
        applications-graphics
    )
endif()

kconfig_add_kcfg_files(answerme GENERATE_MOC answermeconfig.kcfgc)
install(TARGETS answerme ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
