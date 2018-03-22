
class Matrix
{
  public:
    int **arr;
    int rows;
    int columns;

  public:
    Matrix(){};
    Matrix(int rows, int columns)
    {
        this->rows = rows;
        this->columns = columns;
        arr = new int *[rows];
        for (int i = 0; i < rows; i++)
        {
            arr[i] = new int[columns];
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                arr[i][j] = 0;
            }
        }
    }
};

class Vector
{
     

  public:
    friend Matrix;
    int size;
    int *arr;
    Vector(int size)
    {
        this->size = size;
        arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = 0;
        }
    }
};
