#include "widget.h"

#include <QIntValidator>

Widget::Widget() : QWidget(nullptr) {
	out_edit = new QLineEdit(this);
	out_edit->setReadOnly(true);
	out_edit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	out_edit->setText("0");

	num1_edit = new QLineEdit(this);
	num1_edit->setValidator(new QIntValidator(0, 1000, this));
	num1_edit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	num1_edit->setText("0");

	num2_edit = new QLineEdit(this);
	num2_edit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	num2_edit->setValidator(new QIntValidator(0, 1000, this));
	num2_edit->setText("0");

	add_button = new QPushButton(tr("Add"), this);
	sub_button = new QPushButton(tr("Subtract"), this);
	mul_button = new QPushButton(tr("Multiply"), this);

	grid_layout = new QGridLayout(this);
	grid_layout->addWidget(out_edit, 0, 0);
	grid_layout->addWidget(num1_edit, 0, 1);
	grid_layout->addWidget(num2_edit, 0, 2);
	grid_layout->addWidget(add_button, 1, 0);
	grid_layout->addWidget(sub_button, 1, 1);
	grid_layout->addWidget(mul_button, 1, 2);

	connect(add_button, SIGNAL(clicked()), this, SLOT(add()));
	connect(sub_button, SIGNAL(clicked()), this, SLOT(subtract()));
	connect(mul_button, SIGNAL(clicked()), this, SLOT(multiply()));
}

void Widget::add() {
	const int result = std::stoi(num1_edit->text().toStdString()) + std::stoi(num2_edit->text().toStdString());
	out_edit->setText(QString("%1").arg(result));
}

void Widget::subtract() {
	const int result = std::stoi(num1_edit->text().toStdString()) - std::stoi(num2_edit->text().toStdString());
	out_edit->setText(QString("%1").arg(result));

}

void Widget::multiply() {
	const int result = std::stoi(num1_edit->text().toStdString()) * std::stoi(num2_edit->text().toStdString());
	out_edit->setText(QString("%1").arg(result));
}
