//
// Created by maximus on 21.01.23.
//
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix_operations.h"

matrix matrix_multiplication(matrix first_matrix, matrix second_matrix) {
    matrix result;
    double restriction = 500;
    if (first_matrix.j != second_matrix.i) {
        printf("ERRNO (matr mult firstmatrix j = %d, secondmatrix i = %d)", first_matrix.j, second_matrix.i);
        errno = ERANGE;
        result.i = result.j = 0;
        return result;
    }
    result = matrix_creation(first_matrix.i, second_matrix.j);
    for (int i = 0; i < first_matrix.i; i++) {
        for (int j = 0; j < second_matrix.j; j++) {
            result.table[i][j] = 0;
            for (int i2 = 0; i2 < first_matrix.j; i2++) {
                result.table[i][j] += first_matrix.table[i][i2] * second_matrix.table[i2][j];
                //if (result.table[i][j] > restriction)result.table[i][j] = restriction;
                //if (result.table[i][j] < -restriction)result.table[i][j] = restriction;
            }
        }
    }
    return result;
}

#pragma region add

matrix matrix_addition(matrix first_matrix, matrix second_matrix) {
    matrix result;
    if (first_matrix.i != second_matrix.i || first_matrix.j != second_matrix.j) {
        printf("matr add firstmatrix %d x %d secondmatrix %d x %d", first_matrix.i, first_matrix.j, second_matrix.i,
               second_matrix.j);
        errno = ERANGE;
        result.i = result.j = 0;
        return result;
    }
    result = matrix_copy(first_matrix);
    for (int i = 0; i < first_matrix.i; i++) {
        for (int j = 0; j < first_matrix.j; j++) {
            result.table[i][j] += second_matrix.table[i][j];
        }
    }
    return result;
}

#pragma endregion

matrix matrix_creation(int i, int j) {
    matrix result;
    result.i = i;
    result.j = j;
    result.table = calloc(i, sizeof(double *));
    for (int iterator = 0; iterator < i; iterator++) {
        result.table[iterator] = calloc(j, sizeof(double));
    }
    return result;
}

matrix matrix_copy(matrix matrix_to_copy) {
    matrix copy = matrix_creation(matrix_to_copy.i, matrix_to_copy.j);
    for (int i = 0; i < matrix_to_copy.i; i++) {
        for (int j = 0; j < matrix_to_copy.j; j++) {
            copy.table[i][j] = matrix_to_copy.table[i][j];
        }
    }
    return copy;
}

matrix matrix_transposition(matrix matrix_to_transpose) {
    matrix result_matrix;
    result_matrix = matrix_creation(matrix_to_transpose.j, matrix_to_transpose.i);
    for (int i = 0; i < matrix_to_transpose.i; i++) {
        for (int j = 0; j < matrix_to_transpose.j; j++) {
            result_matrix.table[j][i] = matrix_to_transpose.table[i][j];
        }
    }
    return result_matrix;
}

void matrix_print(matrix matrix_to_print) {
    for (int i = 0; i < matrix_to_print.i; i++) {
        for (int j = 0; j < matrix_to_print.j; j++) {
            printf("%.2f ", matrix_to_print.table[i][j]);
        }
        printf("\n");
    }
}

void matrix_free(matrix matrix_to_free) {
    for (int i = 0; i < matrix_to_free.i; ++i) {
        free(matrix_to_free.table[i]);
    }
    free(matrix_to_free.table);
}

void matrix_function_to_elements(matrix matrix_for_operation, double (*func)(double)) {
    for (int i = 0; i < matrix_for_operation.i; i++) {
        for (int j = 0; j < matrix_for_operation.j; j++) {
            matrix_for_operation.table[i][j] = func(matrix_for_operation.table[i][j]);
        }
    }
}

void matrix_multiply_by_constant(matrix matrix_for_operation, double number) {
    for (int i = 0; i < matrix_for_operation.i; i++) {
        for (int j = 0; j < matrix_for_operation.j; j++) {
            matrix_for_operation.table[i][j] = number * matrix_for_operation.table[i][j];
        }
    }
}

matrix make_matrix_from_array(const double *double_array, int i, int j) {
    matrix result;
    result = matrix_creation(i, j);
    for (int iterator = 0; iterator < i; iterator++) {
        for (int iterator1 = 0; iterator1 < j; iterator1++) {
            result.table[iterator][iterator1] = *(double_array + iterator * j + iterator1);
        }
    }
    return result;
}

matrix matrix_substact(matrix first_matrix, matrix second_matrix) {
    matrix result = first_matrix;
    matrix_multiply_by_constant(second_matrix, -1);
    return matrix_addition(result, second_matrix);

}

matrix matrix_multiplication_elements(matrix first_matrix, matrix second_matrix) {
    matrix result;
    result = first_matrix;
    for (int i = 0; i < first_matrix.i; ++i) {
        for (int j = 0; j < first_matrix.j; ++j) {
            result.table[i][j] *= second_matrix.table[i][j];
        }
    }
    return result;
}

matrix create_vector(int feach_num, int this) {
    matrix result = matrix_creation(feach_num, 1);
    for (int i = 0; i < feach_num; ++i) {
        result.table[i][0] = i == this ? 1 : 0;
    }
    return result;
}

void matrix_restrict(matrix matrix_for_operation, double limit) {
    for (int i = 0; i < matrix_for_operation.i; i++) {
        for (int j = 0; j < matrix_for_operation.j; j++) {
            if (matrix_for_operation.table[i][j] > limit)matrix_for_operation.table[i][j] = limit;
            if (matrix_for_operation.table[i][j] < -limit)matrix_for_operation.table[i][j] = -limit;
        }
    }
}
