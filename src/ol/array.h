#ifndef OL_ARRAY_H
#define OL_ARRAY_H
/**
 * @module ol/array
 */

#include <vector>

#include "dll_export.h"
#include "jsport.h"

namespace ol {
namespace array {

/**
* Performs a binary search on the provided sorted list and returns the index of the item if found. If it can't be found it'll return -1.
* https://github.com/darkskyapp/binary-search
*
* @param {Array.<*>} haystack Items to search through.
* @param {*} needle The item to look for.
* @param {Function=} opt_comparator Comparator function.
* @return {number} The index of the item if found, -1 if not.
*/
template<typename T, typename F>
int binarySearch(std::vector<T> const &haystack, T const &needle, F comparator)
{
  int mid, cmp;
  int low = 0;
  int high = int(haystack.size());
  bool found = false;

  while (low < high) {
      /* Note that "(low + high) >>> 1" may overflow, and results in a typecast
       * to double (which gives the wrong results). */
      mid = low + ((high - low) >> 1);
      cmp = comparator(haystack[mid], needle);

      if (cmp < 0) { /* Too low. */
          low = mid + 1;
      } else { /* Key found or too high */
          high = mid;
          found = !cmp;
      }
  }

  /* Key not found. */
  return found ? low : ~low;
}


/**
 * Compare function for array sort that is safe for numbers.
 * @param {*} a The first object to be compared.
 * @param {*} b The second object to be compared.
 * @return {number} A negative number, zero, or a positive number as the first
 *     argument is less than, equal to, or greater than the second.
 */
template<typename T>
int numberSafeCompareFunction(T const &a, T const &b) 
{
    return a > b ? 1 : a < b ? -1 : 0;
}


template<typename T>
int binarySearch(std::vector<T> const &haystack, T const &needle)
{
    return binarySearch<T, int(T const &, T const &)>(haystack, needle, numberSafeCompareFunction);
}

template<typename T, typename T1>
int binarySearch(std::vector<T> const &haystack, T1 const &needle)
{
    return binarySearch<T>(haystack, T(needle));
}

/**
 * Whether the array contains the given object.
 * @param {Array.<*>} arr The array to test for the presence of the element.
 * @param {*} obj The object for which to test.
 * @return {boolean} The object is in the array.
 */
//export function includes(arr, obj) {
//  return arr.indexOf(obj) >= 0;
//}


/**
 * @param {Array.<number>} arr Array.
 * @param {number} target Target.
 * @param {number} direction 0 means return the nearest, > 0
 *    means return the largest nearest, < 0 means return the
 *    smallest nearest.
 * @return {number} Index.
 */
template <typename T>
size_t linearFindNearest(std::vector<T> const &arr, T const &target, T const &direction)
{
    auto n = arr.size();
    if (arr[0] <= target) {
        return 0;
    } else if (target <= arr[n - 1]) {
        return n - 1;
    } else {
        if (direction > 0) {
            for (int i = 1; i < n; ++i) {
                if (arr[i] < target) {
                    return i - 1;
                }
            }
        } else if (direction < 0) {
            for (int i = 1; i < n; ++i) {
                if (arr[i] <= target) {
                    return i;
                }
            }
        } else {
            for (int i = 1; i < n; ++i) {
                if (arr[i] == target) {
                    return i;
                } else if (arr[i] < target) {
                    if (arr[i - 1] - target < target - arr[i]) {
                        return i - 1;
                    } else {
                        return i;
                    }
                }
            }
        }
        return n - 1;
    }
}


///**
// * @param {Array.<*>} arr Array.
// * @param {number} begin Begin index.
// * @param {number} end End index.
// */
//export function reverseSubArray(arr, begin, end) {
//  while (begin < end) {
//    const tmp = arr[begin];
//    arr[begin] = arr[end];
//    arr[end] = tmp;
//    ++begin;
//    --end;
//  }
//}
//
//
///**
// * @param {Array.<VALUE>} arr The array to modify.
// * @param {!Array.<VALUE>|VALUE} data The elements or arrays of elements to add to arr.
// * @template VALUE
// */
//export function extend(arr, data) {
//  const extension = Array.isArray(data) ? data : [data];
//  const length = extension.length;
//  for (let i = 0; i < length; i++) {
//    arr[arr.length] = extension[i];
//  }
//}
//
//
///**
// * @param {Array.<VALUE>} arr The array to modify.
// * @param {VALUE} obj The element to remove.
// * @template VALUE
// * @return {boolean} If the element was removed.
// */
//export function remove(arr, obj) {
//  const i = arr.indexOf(obj);
//  const found = i > -1;
//  if (found) {
//    arr.splice(i, 1);
//  }
//  return found;
//}
//
//
///**
// * @param {Array.<VALUE>} arr The array to search in.
// * @param {function(VALUE, number, ?) : boolean} func The function to compare.
// * @template VALUE
// * @return {VALUE|null} The element found or null.
// */
//export function find(arr, func) {
//  const length = arr.length >>> 0;
//  let value;
//
//  for (let i = 0; i < length; i++) {
//    value = arr[i];
//    if (func(value, i, arr)) {
//      return value;
//    }
//  }
//  return null;
//}
//
//
///**
// * @param {Array|Uint8ClampedArray} arr1 The first array to compare.
// * @param {Array|Uint8ClampedArray} arr2 The second array to compare.
// * @return {boolean} Whether the two arrays are equal.
// */
//export function equals(arr1, arr2) {
//  const len1 = arr1.length;
//  if (len1 !== arr2.length) {
//    return false;
//  }
//  for (let i = 0; i < len1; i++) {
//    if (arr1[i] !== arr2[i]) {
//      return false;
//    }
//  }
//  return true;
//}
//
//
///**
// * @param {Array.<*>} arr The array to sort (modifies original).
// * @param {Function} compareFnc Comparison function.
// */
//export function stableSort(arr, compareFnc) {
//  const length = arr.length;
//  const tmp = Array(arr.length);
//  let i;
//  for (i = 0; i < length; i++) {
//    tmp[i] = {index: i, value: arr[i]};
//  }
//  tmp.sort(function(a, b) {
//    return compareFnc(a.value, b.value) || a.index - b.index;
//  });
//  for (i = 0; i < arr.length; i++) {
//    arr[i] = tmp[i].value;
//  }
//}
//
//
///**
// * @param {Array.<*>} arr The array to search in.
// * @param {Function} func Comparison function.
// * @return {number} Return index.
// */
//export function findIndex(arr, func) {
//  let index;
//  const found = !arr.every(function(el, idx) {
//    index = idx;
//    return !func(el, idx, arr);
//  });
//  return found ? index : -1;
//}
//
//
/**
 * @param {Array.<*>} arr The array to test.
 * @param {Function=} opt_func Comparison function.
 * @param {boolean=} opt_strict Strictly sorted (default false).
 * @return {boolean} Return index.
 */

template <typename T>
bool isSorted(std::vector<T> const &arr, int zero, bool opt_strict)
{
    auto compare = numberSafeCompareFunction<T>;

    return isSorted(arr, compare, opt_strict);
}

template <typename T, typename Compare>
bool isSorted(std::vector<T> const &arr, Compare compare, bool opt_strict = false)
{
    //return arr.every(function(currentVal, index) {
    //  if (index === 0) {
    //    return true;
    //  }
    //  const res = compare(arr[index - 1], currentVal);
    //  return !(res > 0 || opt_strict && res === 0);
    //});

    if (arr.size() < 2)
        return true;
    for (int i = 1; i != arr.size(); ++i) {
        auto res = compare(arr[i - 1], arr[i]);
        if ((res > 0 || opt_strict && res == 0))
            return false;
    }
    return true;
}

template <typename T>
bool isSorted(std::vector<T> const &arr)
{
    auto compare = numberSafeCompareFunction<T>;
    bool opt_strict = false;

    return isSorted(arr, 0, false);
}

}
}
#endif