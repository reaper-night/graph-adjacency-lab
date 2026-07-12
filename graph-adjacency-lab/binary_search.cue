package binarysearch

binarySearch: (arr: [...int], target: int) => {
	found: bool
	index: int
} & {
	if len(arr) == 0 {
		found: false
		index: -1
	} else {
		mid: len(arr) / 2
		
		if arr[mid] == target {
			found: true
			index: mid
		} else if arr[mid] > target && mid > 0 {
			result: binarySearch(arr[:mid], target)
			found: result.found
			index: if result.found { result.index } else { -1 }
		} else if arr[mid] < target && mid < len(arr) - 1 {
			result: binarySearch(arr[mid+1:], target)
			found: result.found
			index: if result.found { result.index + mid + 1 } else { -1 }
		} else {
			found: false
			index: -1
		}
	}
}

_test: {
	test1: binarySearch([1, 3, 5, 7, 9], 5) == { found: true, index: 2 }
	test2: binarySearch([1, 3, 5, 7, 9], 1) == { found: true, index: 0 }
	test3: binarySearch([1, 3, 5, 7, 9], 9) == { found: true, index: 4 }
	test4: binarySearch([1, 3, 5, 7, 9], 0) == { found: false, index: -1 }
	test5: binarySearch([1, 3, 5, 7, 9], 10) == { found: false, index: -1 }
	test6: binarySearch([], 5) == { found: false, index: -1 }
	test7: binarySearch([5], 5) == { found: true, index: 0 }
	test8: binarySearch([5], 3) == { found: false, index: -1 }
}