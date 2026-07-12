def binary_search(arr, target):
    if len(arr) == 0:
        return {"found": False, "index": -1}
    
    mid = len(arr) // 2
    
    if arr[mid] == target:
        return {"found": True, "index": mid}
    elif arr[mid] > target and mid > 0:
        result = binary_search(arr[:mid], target)
        if result["found"]:
            return {"found": True, "index": result["index"]}
        else:
            return {"found": False, "index": -1}
    elif arr[mid] < target and mid < len(arr) - 1:
        result = binary_search(arr[mid+1:], target)
        if result["found"]:
            return {"found": True, "index": result["index"] + mid + 1}
        else:
            return {"found": False, "index": -1}
    else:
        return {"found": False, "index": -1}

test_cases = [
    ("found_first", [1, 3, 5, 7, 9], 1, {"found": True, "index": 0}),
    ("found_last", [1, 3, 5, 7, 9], 9, {"found": True, "index": 4}),
    ("found_middle", [1, 3, 5, 7, 9], 5, {"found": True, "index": 2}),
    ("not_found_smaller", [1, 3, 5, 7, 9], 0, {"found": False, "index": -1}),
    ("not_found_larger", [1, 3, 5, 7, 9], 10, {"found": False, "index": -1}),
    ("not_found_in_middle", [1, 3, 5, 7, 9], 4, {"found": False, "index": -1}),
    ("empty_array", [], 5, {"found": False, "index": -1}),
    ("single_element_found", [5], 5, {"found": True, "index": 0}),
    ("single_element_not_found", [5], 3, {"found": False, "index": -1}),
]

print("Running binary search tests...")
print("=" * 60)

passed = 0
failed = 0

for name, arr, target, expected in test_cases:
    result = binary_search(arr, target)
    status = "PASS" if result == expected else "FAIL"
    
    if status == "PASS":
        passed += 1
    else:
        failed += 1
    
    print(f"{status}: {name}")
    print(f"  Input: arr={arr}, target={target}")
    print(f"  Expected: {expected}")
    print(f"  Got: {result}")
    print()

print("=" * 60)
print(f"Results: {passed} passed, {failed} failed")