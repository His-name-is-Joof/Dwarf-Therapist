/*
Dwarf Therapist
Copyright (c) 2009 Trey Stout (chmod)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef VIEW_COLUMN_SET_H
#define VIEW_COLUMN_SET_H

#include <QtGui>

class ViewColumn;
class GridView;

namespace Ui
{
	class ViewColumnSetDialog;
}

/*!
ViewColumnSet
*/
class ViewColumnSet : public QObject {
	Q_OBJECT
public:
	ViewColumnSet(QString name, QObject *parent = 0);

	QString name() {return m_name;}
	void set_filename(const QString &filename) {m_filename = filename;}
	void add_column(ViewColumn *col);
	void clear_columns();
	void set_bg_color(const QColor &color) {m_bg_color = color;}
	QColor bg_color() {return m_bg_color;}
	QList<ViewColumn*> columns() {return m_columns.values();}
	GridView *view() {return m_view;}

	//! loads a returns a new set object based on the description in filename
	static ViewColumnSet *from_file(QString filename, QObject *parent = 0);

	//! for use when editing this set is cancelled, just reload from disk
	void reset_from_disk();

	bool eventFilter(QObject *, QEvent *);
	public slots:
		void set_name(const QString &name);
		void write_settings();
		
		//! Shows a small editing dialog for this set
		int show_builder_dialog(QWidget *parent = 0);

		//! for use when the builder dialog is open
		void update_color(const QColor &new_color);
		void draw_columns();
		void type_chosen(const QString &type_name);
		void add_column_from_gui();
		void draw_column_context_menu(const QPoint &);
		void edit_column(); // from context menu
		void edit_column(QListWidgetItem*); // from double click

private:
	Ui::ViewColumnSetDialog *ui;
	QString m_name;
	QString m_filename;
	GridView *m_view;
	QMap<int, ViewColumn*> m_columns;
	QBrush m_bg_brush; // possibly allow textured backgrounds in the long long ago, err future.
	QColor m_bg_color;
	QDialog *m_dialog; // for showing the builder dialog

	void order_changed();
	void show_edit_column_dialog(ViewColumn *vc);
};

#endif
