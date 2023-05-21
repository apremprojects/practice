#include <vector>
#include <string>
#include <ostream>
#include <glog/logging.h>

template <typename T>
class Matrix {
public:
	Matrix(const size_t rows, const size_t cols);

	size_t rowSize() const { return _rows; }
	size_t colSize() const { return _columns; }

	T operator()(const size_t r, const size_t c) const;
	T& operator()(const size_t r, const size_t c);

	Matrix<T> operator+(const Matrix<T>& m) const;
	Matrix<T> operator*(const Matrix<T>& m) const;
	Matrix<T> operator*(const T s) const;

	Matrix<T> transpose() const;

	template <typename T>
	friend std::istream& operator>>(std::istream& in, Matrix<T>& mat);

	template <typename T>
	friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat);

private:
	size_t rowColumnToIndex(size_t r, size_t c) const {
		return r * _columns + c;
	}

	size_t _rows;
	size_t _columns;
	std::vector<T> _data;
};

template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols)
	: _rows(rows), _columns(cols), _data(rows* cols) {}

template <typename T>
T Matrix<T>::operator()(const size_t r, const size_t c) const {
	return _data[rowColumnToIndex(r,c)];
}

template <typename T>
T& Matrix<T>::operator()(const size_t r, const size_t c) {
	return _data[rowColumnToIndex(r, c)];
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat) {
	for (size_t i = 0; i < mat._data.size(); i++) {
		if (i % (mat._columns) == 0 && i != 0) {
			out << "\n";
		} else if (i != 0) {
			out << " ";
		}
		out << mat._data[i];
	}
	out << "\n";
	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& mat) {
	for (size_t i = 0; i < mat._data.size(); i++) {
		in >> mat._data[i];
	}
	return in;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m) const {
	CHECK_EQ(rowSize(), m.rowSize()) << "Row size mismatch " << rowSize() << ", " << m.rowSize();
	CHECK_EQ(colSize(), m.colSize()) << "Column size mismatch " << colSize() << ", " << m.colSize();
	Matrix<T> out(rowSize(), colSize());
	for (size_t i = 0; i < _data.size(); i++) {
		out._data[i] = m._data[i] + _data[i];
	}
	return out;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const{
	CHECK_EQ(_columns, m._rows) << "Invalid multiplication of matrices with dimensions: (" 
								<<  _rows << "x" << _columns << ")" << " and " << "(" 
								<<  m._rows << "x" << m._columns << ")";
	Matrix<T> out(_rows, m._columns);
	for (size_t r = 0; r < _rows; r++) {
		for (size_t c = 0; c < m._columns; c++) {
			for (size_t i = 0; i < _columns; i++) {
				out(r, c) += _data[rowColumnToIndex(r, i)] * m(i, c);
			}
		}
	}
	return out;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T s) const {
	Matrix<T> out(_rows, _columns);
	for (size_t i = 0; i < _data.size(); i++) {
		out._data[i] = _data[i] * s;
	}
	return out;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> out(_columns, _rows);
	for (size_t r = 0; r < _rows; r++) {
		for (size_t c = 0; c < _columns; c++) {
			out(c, r) = _data[rowColumnToIndex(r, c)];
		}
	}
	return out;
}