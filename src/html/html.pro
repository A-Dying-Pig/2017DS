#-------------------------------------------------
#
# Project created by QtCreator 2017-12-19T19:51:01
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = html
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    html_analysis.cpp \
    m_balanced_binary_tree.cpp \
    m_charstring.cpp \
    m_charstringlink.cpp \
    m_file_list.cpp \
    m_stack.cpp \
    query_web_hash_table.cpp \
    qt_download_web.cpp \
    progress_bar.cpp \
    m_thread.cpp \
    m_program.cpp

HEADERS  += widget.h \
    html_analysis.h \
    m_balanced_binary_tree.h \
    m_charstring.h \
    m_charstringlink.h \
    m_file_list.h \
    m_stack.h \
    query_web_hash_table.h \
    qt_download_web.h \
    progress_bar.h \
    m_thread.h \
    m_program.h

FORMS    += widget.ui

RESOURCES += \
    digger.qrc
