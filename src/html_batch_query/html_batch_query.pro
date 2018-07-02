#-------------------------------------------------
#
# Project created by QtCreator 2017-12-24T18:33:11
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = html_batch_query
TEMPLATE = app


SOURCES += main.cpp \
    html_analysis.cpp \
    m_balanced_binary_tree.cpp \
    m_charstring.cpp \
    m_charstringlink.cpp \
    m_file_list.cpp \
    m_program.cpp \
    m_stack.cpp \
    m_thread.cpp \
    progress_bar.cpp \
    qt_download_web.cpp \
    query_web_hash_table.cpp

HEADERS  += \
    html_analysis.h \
    m_balanced_binary_tree.h \
    m_charstring.h \
    m_charstringlink.h \
    m_file_list.h \
    m_program.h \
    m_stack.h \
    m_thread.h \
    progress_bar.h \
    qt_download_web.h \
    query_web_hash_table.h

FORMS    +=

RESOURCES += \
    digger.qrc
