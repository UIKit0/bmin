/*
 *
 * created date: 11/30/2009
 *
 * Copyright (C) 2009 Jakub Zelenka.
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

#include "qmwidget.h"
#include "modulewidget.h"
#include "guimanager.h"
// kernel
#include "kernel.h"
#include "quinemccluskey.h"
#include "term.h"

#include <QString>
#include <QStringList>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTextTable>

#include <list>
#include <algorithm>
#include <functional>
using namespace std;

#include <iostream>

QmWidget::QmWidget(const QString &name, int pos)
        : ModuleWidget(name, pos)
{
    m_data = 0;
    m_gm = GUIManager::instance();

    connect(m_gm, SIGNAL(formulaMinimized()), this, SLOT(updateData()));
    connect(m_gm, SIGNAL(formulaChanged(Formula *)), this, SLOT(makeData(Formula *)));

    m_textArea = new QTextEdit;
    m_textArea->setFont(QFont("monospace", 10));
    m_textArea->setLineWrapMode(QTextEdit::NoWrap);
    m_textArea->setReadOnly(true);
    m_textArea->setUndoRedoEnabled(false);

    // set layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_textArea);
    setLayout(mainLayout);
}

void QmWidget::setActivity(bool a)
{
    m_active = a;
    if (a) {
        if (m_gm->isCorrectFormula())
            m_gm->minimizeFormula(true);
        else {
            showHeader();
            showNothing();
        }
    }
}

void QmWidget::makeData(Formula *)
{
    if (m_active)
        m_gm->minimizeFormula(true);
}

void QmWidget::updateData()
{
    if (m_active) {
        m_data = m_gm->getQmData();
        showHeader();
        if (m_data) {
            showPrimeTable();
            showCoveringTable();
        }
        else
            showNothing();
    }
}

void QmWidget::showHeader()
{
    m_textArea->clear();
    m_textArea->insertHtml(QString("<h1 align=\"center\">%1</h1>").arg(
            tr("Quine-McCluskey Algorithm")));
}

void QmWidget::showNothing()
{
    m_textArea->insertHtml(QString("<br><h3 align=\"left\">%1</h3>").arg(
            tr("The formula is unknown.")));
}


void QmWidget::setCell(QTextTable *table, int row, int col, const QString &html)
{
    QTextTableCell cell = table->cellAt(row, col);
    QTextCursor cellCursor = cell.firstCursorPosition();
    cellCursor.insertHtml(html);
}

void QmWidget::showPrimeTable()
{
    m_textArea->insertHtml(QString("<br><h2 align=\"center\">%1</h2>").arg(
            tr("Finding Prime Implicants ")));

    int columns = (m_data->getMaxMissings() * 2) + 3;
    int varsCount = m_data->getVarsCount();
    int firstImpl = m_data->firstMintermOnes();
    int lastImpl = m_data->lastMintermOnes();
    int rows = varsCount - (firstImpl + (varsCount - lastImpl)) + 3;

    list<Term> *l;
    QTextCursor cursor(m_textArea->textCursor());

    QTextTableFormat tableFormat;
    tableFormat.setCellPadding(2);
    tableFormat.setCellSpacing(0);
    tableFormat.setHeaderRowCount(1);
    QTextTable *table = cursor.insertTable(rows, columns, tableFormat);

    QString headStr = tr("Size %1 primes");
    QString cubeStr = tr("%1-cube");

    table->mergeCells(0, 0, 1, 3);
    setCell(table, 0, 0, headStr.arg(1));
    setCell(table, 1, 0, tr("Number of 1s"));
    setCell(table, 1, 1, tr("Minterm"));
    setCell(table, 1, 2, cubeStr.arg(0));

    // first col
    for (int row = 2, ones = firstImpl; row < rows; row++, ones++) {
        setCell(table, row, 0, QString::number(ones));
        l = m_data->getImpls(0, ones);
        if (!l->empty()) {
            l->sort(greater<Term>());
            for (list<Term>::iterator it = l->begin(); it != l->end(); it++) {
                if (it != l->begin()) {
                    setCell(table, row, 1, "<br>");
                    setCell(table, row, 2, "<br>");
                }
                setCell(table, row, 1, QString::fromStdString((*it).toString(Term::SF_MSET)));
                setCell(table, row, 2, QString::fromStdString((*it).toString()));
            }
        }
    }

    for (int column = 3; column < columns; column += 2) {
        table->mergeCells(0, column, 1, 2);
        // header
        int missings = (column - 1) / 2;
        int size = 1 << missings;
        setCell(table, 0, column, headStr.arg(size));
        setCell(table, 1, column, tr("Minterms"));
        setCell(table, 1, column + 1, cubeStr.arg(missings));

        // body
        for (int row = 2, ones = firstImpl; row < rows; row++, ones++) {
            l = m_data->getImpls(missings, ones);
            l->sort(greater<Term>());
            for (list<Term>::iterator it = l->begin(); it != l->end(); it++) {
                if (it != l->begin()) {
                    setCell(table, row, column, "<br>");
                    setCell(table, row, column + 1, "<br>");
                }
                setCell(table, row, column, QString::fromStdString((*it).toString(Term::SF_MSET)));
                setCell(table, row, column + 1, QString::fromStdString((*it).toString()));
            }
        }
    }


    // Table
    m_textArea->insertHtml(QString("<br><h2 align=\"center\">%1</h2>").arg(
            tr("Prime Implicants Table")));

    vector<Term> *headRow = m_data->getCoverHeadRow();
    vector<Term> *headCol = m_data->getCoverHeadCol();

    table = m_textArea->textCursor().insertTable(headRow->size() + 1, headCol->size() + 1, tableFormat);

    for (unsigned i = 1; i <= headRow->size(); i++)
        setCell(table, i, 0, QString::fromStdString(headRow->at(i-1).toString(Term::SF_MSET)));
    for (unsigned j = 1; j <= headCol->size(); j++)
        setCell(table, 0, j, QString::number(headCol->at(j-1).getIdx()));

    for (unsigned i = 1; i <= headRow->size(); i++) {
        for (unsigned j = 1; j <= headCol->size(); j++) {
            if (m_data->isCovered(i - 1, j - 1))
                setCell(table, i, j, "X");
        }
    }
}

void QmWidget::showCoveringTable()
{

}


