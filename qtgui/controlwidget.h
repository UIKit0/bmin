/*
 * controlwidget.h - Top layout part (setting fce, ...)
 * created date: 2009/08/06
 *
 * Copyright (C) 2007-2009 Jakub Zelenka.
 *
 * Bmin is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * Bmin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with Bmin; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.
 */

#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>

class QComboBox;
class QLineEdit;
class QPushButton;
class QString;
class QLabel;

class ControlWidget : public QWidget
{
Q_OBJECT

public:
    // constructor (no implicit construnctor)
    ControlWidget(QWidget *parent = 0);

protected:
    // paint event for drawing lines
    virtual void paintEvent(QPaintEvent* e);

private:
    // line input
    QLineEdit *m_fceLine;
    // minimize button
    QPushButton *m_minBtn;
    // label with minimized function
    QLabel *m_minFceLabel;

    // previous function
    QString m_prevFce;
    // prefix for minimized function
    QString m_minFcePrefix;
    // separator color
    QColor m_sepColor;

public slots:
    // sets fceLine to new value
    void setFce(const QString &fceStr);
    // sets minFceLabel to new value
    void setMinFce(const QString &minFceStr);

private slots:
    // called when QLineEdit with fce is changed
    void sendFce();

signals:
    // emited by changing boolean function
    void fceChanged(const QString &);
};

#endif // CONTROLWIDGET_H