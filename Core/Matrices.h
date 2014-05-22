#pragma once

#include <iostream>
#include <vector>

namespace cagd
{
    // forward declaration of template class Matrix
    template <typename T>
            class Matrix;

    // forward declaration of template class RowMatrix
    template <typename T>
            class RowMatrix;

    // forward declaration of template class ColumnMatrix
    template <typename T>
            class ColumnMatrix;

    // forward declaration of template class TriangularMatrix
    template <typename T>
            class TriangularMatrix;

    // forward declarations of overloaded and templated input/output from/to stream operators
    template <typename T>
            std::ostream& operator << (std::ostream& lhs, const Matrix<T>& rhs);

    template <typename T>
            std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs);

    //----------------------
    // template class Matrix
    //----------------------
    template <typename T>
            class Matrix
    {
        friend std::ostream& cagd::operator << <T>(std::ostream&, const Matrix<T>& rhs);
        friend std::istream& cagd::operator >> <T>(std::istream&, Matrix<T>& rhs);

    protected:
        unsigned int                    _row_count;
        unsigned int                    _column_count;
        std::vector< std::vector<T> >   _data;
    public:
        // special constructor (can also be used as a default constructor)
        Matrix(unsigned int row_count = 1, unsigned int column_count = 1);

        // copy constructor
        Matrix(const Matrix& m);

        // assignment operator
        Matrix& operator =(const Matrix& m);

        // get element by reference
        T& operator ()(unsigned int row, unsigned int column);

        // get copy of an element
        T operator ()(unsigned int row, unsigned int column) const;

        // get dimensions
        unsigned int GetRowCount() const;
        unsigned int GetColumnCount() const;

        // set dimensions
        virtual bool ResizeRows(unsigned int row_count);
        virtual bool ResizeColumns(unsigned int column_count);

        // update
        bool SetRow(unsigned int index, const RowMatrix<T>& row);
        bool SetColumn(unsigned int index, const ColumnMatrix<T>& column);

        // destructor
        virtual ~Matrix();
    };

    //-------------------------
    // template class RowMatrix
    //-------------------------
    template <typename T>
            class RowMatrix: public Matrix<T>
    {
    public:
        // special constructor (can also be used as a default constructor)
        RowMatrix(unsigned int column_count = 1);

        // get element by reference
        T& operator ()(unsigned int column);
        T& operator [](unsigned int column);

        // get copy of an element
        T operator ()(unsigned int column) const;
        T operator [](unsigned int column) const;

        // a row matrix consists of a single row
        bool ResizeRows(unsigned int row_count);
    };

    //----------------------------
    // template class ColumnMatrix
    //----------------------------
    template <typename T>
            class ColumnMatrix: public Matrix<T>
    {
    public:
        // special constructor (can also be used as a default constructor)
        ColumnMatrix(unsigned int row_count = 1);

        // get element by reference
        T& operator ()(unsigned int row);
        T& operator [](unsigned int row);

        // get copy of an element
        T operator ()(unsigned int row) const;
        T operator [](unsigned int row) const;

        // a column matrix consists of a single column
        bool ResizeColumns(unsigned int column_count);
    };

    //--------------------------------
    // template class TriangularMatrix
    //--------------------------------
    template <typename T>
    class TriangularMatrix
    {
        friend std::ostream& cagd::operator << <T>(std::ostream&, const TriangularMatrix<T>& rhs);
        friend std::istream& cagd::operator >> <T>(std::istream&, TriangularMatrix<T>& rhs);

    protected:
        unsigned int                    _row_count;
        std::vector< std::vector<T> >   _data;

    public:
        // special constructor (can also be used as a default constructor)
        TriangularMatrix(unsigned int row_count = 1);

        // get element by reference
        T& operator ()(unsigned int row, unsigned int column);

        // get copy of an element
        T operator ()(unsigned int row, unsigned int column) const;

        // get dimension
        unsigned int GetRowCount() const;

        // set dimension
        bool ResizeRows(unsigned int row_count);
    };

    //--------------------------------------------------
    // implementation of template class Matrix
    //--------------------------------------------------

    // special constructor (can also be used as a default constructor)
    template <typename T>
    Matrix<T>::Matrix(unsigned int row_count, unsigned int column_count): _row_count(row_count), _column_count(column_count)
    {
        _data.resize(_row_count);
        for (typename std::vector< std::vector<T> >::iterator row = _data.begin(); row != _data.end(); ++row)
            row->resize(_column_count);
    }

    // copy constructor
    template <typename T>
    Matrix<T>::Matrix(const Matrix &m): _row_count(m._row_count), _column_count(m._column_count), _data(m._data)
    {
    }

    // assignment operator
    template <typename T>
    Matrix<T>& Matrix<T>::operator =(const Matrix<T>& rhs)
    {
        if (this != &rhs)
        {
            _row_count = rhs._row_count;
            _column_count = rhs._column_count;
            _data = rhs._data;
        }
        return *this;
    }

    // get element by reference
    template <typename T>
    T& Matrix<T>::operator ()(unsigned int row, unsigned int column)
    {
        return _data[row][column];
    }

    // get copy of an element
    template <typename T>
    T Matrix<T>::operator ()(unsigned int row, unsigned int column) const
    {
        return _data[row][column];
    }

    // get dimensions
    template <typename T>
    unsigned int Matrix<T>::GetRowCount() const
    {
        return _row_count;
    }

    template <typename T>
    unsigned int Matrix<T>::GetColumnCount() const
    {
        return _column_count;
    }

    // set dimensions
    template <typename T>
    bool Matrix<T>::ResizeRows(unsigned int row_count)
    {
        if (_row_count != row_count)
        {
            _data.resize(row_count);

            if (row_count > _row_count)
                for (typename std::vector< std::vector<T> >::iterator row = _data.begin(); row != _data.end(); ++row)
                    row->resize(_column_count);

            _row_count = row_count;
        }

        return true;
    }

    template <typename T>
    bool Matrix<T>::ResizeColumns(unsigned int column_count)
    {
        if (_column_count != column_count)
        {
            _column_count = column_count;

            for (typename std::vector< std::vector<T> >::iterator row = _data.begin(); row != _data.end(); ++row)
                row->resize(_column_count);
        }

        return true;
    }

    template <class T>
    bool Matrix<T>::SetRow(unsigned int row, const RowMatrix<T>& entire_row)
    {
        if (row >= _row_count || _column_count != entire_row.GetColumnCount())
            return false;

        for (unsigned int c = 0; c < _column_count; ++c)
            _data[row][c] = entire_row(c);

        return true;
    }

    template <class T>
    bool Matrix<T>::SetColumn(unsigned int column, const ColumnMatrix<T>& entire_column)
    {
        if (column >= _column_count || _row_count != entire_column.GetRowCount())
            return false;

        for (unsigned int r = 0; r < _row_count; ++r)
            _data[r][column] = entire_column(r);

        return true;
    }

    // destructor
    template <typename T>
    Matrix<T>::~Matrix()
    {
        _row_count = _column_count = 0;
        _data.clear();
    }

    //-----------------------------------------------------
    // implementation of template class RowMatrix
    //-----------------------------------------------------

    // special constructor (can also be used as a default constructor)
    template <typename T>
    RowMatrix<T>::RowMatrix(unsigned int column_count): Matrix<T>(1, column_count)
    {
    }

    // get element by reference
    template <typename T>
    T& RowMatrix<T>::operator ()(unsigned int column)
    {
        return Matrix<T>::operator ()(0, column);
    }

    template <typename T>
    T& RowMatrix<T>::operator [](unsigned int column)
    {
        return Matrix<T>::operator ()(0, column);
    }

    // get copy of an element
    template <typename T>
    T RowMatrix<T>::operator ()(unsigned int column) const
    {
        return Matrix<T>::operator ()(0, column);
    }

    template <typename T>
    T RowMatrix<T>::operator [](unsigned int column) const
    {
        return Matrix<T>::operator ()(0, column);
    }

    // a row matrix consists of a single row
    template <typename T>
    bool RowMatrix<T>::ResizeRows(unsigned int row_count)
    {
        return (row_count == 1);
    }

    //--------------------------------------------------------
    // implementation of template class ColumnMatrix
    //--------------------------------------------------------

    // special constructor (can also be used as a default constructor)
    template <typename T>
    ColumnMatrix<T>::ColumnMatrix(unsigned int row_count): Matrix<T>(row_count, 1)
    {

    }

    // get element by reference
    template <typename T>
    T& ColumnMatrix<T>::operator ()(unsigned int row)
    {
        return Matrix<T>::operator ()(row, 0);
    }

    template <typename T>
    T& ColumnMatrix<T>::operator [](unsigned int row)
    {
        return Matrix<T>::operator ()(row, 0);
    }

    // get copy of an element
    template <typename T>
    T ColumnMatrix<T>::operator ()(unsigned int row) const
    {
        return Matrix<T>::operator ()(row, 0);
    }

    template <typename T>
    T ColumnMatrix<T>::operator [](unsigned int row) const
    {
        return Matrix<T>::operator ()(row, 0);
    }

    // a row matrix consists of a single row
    template <typename T>
    bool ColumnMatrix<T>::ResizeColumns(unsigned int column_count)
    {
        return (column_count == 1);
    }

    //--------------------------------------------------
    // implementation of template class TriangularMatrix
    //--------------------------------------------------

    // special constructor (can also be used as a default constructor)
    template <typename T>
    TriangularMatrix<T>::TriangularMatrix(unsigned int row_count): _row_count(row_count)
    {
        _data.resize(_row_count);
        for (unsigned int r = 0; r < row_count; ++r)
            _data[r].resize(r + 1);
    }

    // get element by reference
    template <typename T>
    T& TriangularMatrix<T>::operator ()(unsigned int row, unsigned int column)
    {
        return _data[row][column];
    }

    // get copy of an element
    template <typename T>
    T TriangularMatrix<T>::operator ()(unsigned int row, unsigned int column) const
    {
        return _data[row][column];
    }

    // get dimension
    template <typename T>
    unsigned int TriangularMatrix<T>::GetRowCount() const
    {
        return _row_count;
    }

    // set dimensions
    template <typename T>
    bool TriangularMatrix<T>::ResizeRows(unsigned int row_count)
    {
        if (_row_count != row_count)
        {
            _data.resize(row_count);

            for (unsigned int r = _row_count; r < row_count; ++r)
            {
                _data[r].resize(r + 1);
            }

            _row_count = row_count;
        }

        return true;
    }

    //------------------------------------------------------------------------------
    // definitions of overloaded and templated input/output from/to stream operators
    //------------------------------------------------------------------------------

    // output to stream
    template <typename T>
            std::ostream& operator <<(std::ostream& lhs, const Matrix<T>& rhs)
    {
        lhs << rhs._row_count << " " << rhs._column_count << std::endl;
        for (typename std::vector< std::vector<T> >::const_iterator row = rhs._data.begin();
        row != rhs._data.end(); ++row)
        {
            for (typename std::vector<T>::const_iterator column = row->begin();
            column != row->end(); ++column)
                lhs << *column << " ";
            lhs << std::endl;
        }
        return lhs;
    }

    // input from stream
    template <typename T>
            std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs)
    {
        lhs >> rhs._row_count >> rhs._column_count;

        rhs._data.resize(rhs._row_count);
        for (typename std::vector< std::vector<T> >::iterator row = rhs._data.begin(); row < rhs._data.end(); ++row)
        {
            row->resize(rhs._column_count);
            for (typename std::vector<T>::iterator column = row->begin(); column != row->end(); ++column)
                lhs >> *column;
        }

        return lhs;
    }

    // output to stream
    template <typename T>
    std::ostream& operator <<(std::ostream& lhs, const TriangularMatrix<T>& rhs)
    {
        lhs << rhs._row_count << std::endl;
        for (typename std::vector< std::vector<T> >::const_iterator row = rhs._data.begin(); row != rhs._data.end(); ++row)
        {
            for (typename std::vector<T>::const_iterator column = row->begin(); column != row->end(); ++column)
                lhs << *column << " ";
            lhs << std::endl;
        }
        return lhs;
    }

    // input from stream
    template <typename T>
    std::istream& operator >>(std::istream& lhs, TriangularMatrix<T>& rhs)
    {
        lhs >> rhs._row_count;

        rhs._data.resize(rhs._row_count);
        for (unsigned int r = 0; r < rhs._row_count; ++r)
        {
            rhs._data[r].resize(r + 1);

            for (unsigned int c = 0; c <= r; ++r)
            {
                lhs >> rhs._data[r][c];
            }
        }

        return lhs;
    }
}
