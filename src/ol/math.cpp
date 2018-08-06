#include "math.h"

namespace ol {
namespace math {

/**
* Returns the square of the closest distance between the point (x, y) and the
* line segment (x1, y1) to (x2, y2).
* @param {number} x X.
* @param {number} y Y.
* @param {number} x1 X1.
* @param {number} y1 Y1.
* @param {number} x2 X2.
* @param {number} y2 Y2.
* @return {number} Squared distance.
*/
OLQT_EXPORT number_t squaredSegmentDistance(number_t x, number_t y, number_t x1, number_t y1, number_t x2, number_t y2)
{
    number_t dx = x2 - x1;
    number_t dy = y2 - y1;
    if (dx != 0 || dy != 0) {
        number_t t = ((x - x1) * dx + (y - y1) * dy) / (dx * dx + dy * dy);
        if (t > 1) {
            x1 = x2;
            y1 = y2;
        } else if (t > 0) {
            x1 += dx * t;
            y1 += dy * t;
        }
    }
    return squaredDistance(x, y, x1, y1);
}

/**
* Solves system of linear equations using Gaussian elimination method.
*
* @param {Array.<Array.<number>>} mat Augmented matrix (n x n + 1 column)
*                                     in row-major order.
* @return {Array.<number>} The resulting vector.
*/
OLQT_EXPORT std::vector<number_t> ol::math::solveLinearSystem(matrix_t mat)
{
    size_t n = mat.size();

    for (int i = 0; i < n; i++) {
        // Find max in the i-th column (ignoring i - 1 first rows)
        int maxRow = i;
        number_t maxEl = fabs(mat[i][i]);
        for (int r = i + 1; r < n; r++) {
            number_t absValue = fabs(mat[r][i]);
            if (absValue > maxEl) {
                maxEl = absValue;
                maxRow = r;
            }
        }

        if (maxEl == 0) {
            return std::vector<number_t>(); // matrix is singular
        }

        // Swap max row with i-th (current) row
        auto tmp = mat[maxRow];
        mat[maxRow] = mat[i];
        mat[i] = tmp;

        // Subtract the i-th row to make all the remaining rows 0 in the i-th column
        for (int j = i + 1; j < n; j++) {
            number_t coef = -mat[j][i] / mat[i][i];
            for (int k = i; k < n + 1; k++) {
                if (i == k) {
                    mat[j][k] = 0;
                } else {
                    mat[j][k] += coef * mat[i][k];
                }
            }
        }
    }

    // Solve Ax=b for upper triangular matrix A (mat)
    std::vector<number_t> x (n);
    for (int l = int(n - 1); l >= 0; l--) {
        x[l] = mat[l][n] / mat[l][l];
        for (int m = l - 1; m >= 0; m--) {
            mat[m][n] -= mat[m][l] * x[l];
        }
    }
    return x;
}

}
}