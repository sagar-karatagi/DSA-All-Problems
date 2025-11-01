# Sum of Subsequence Widths — Detailed Documentation

**Problem statement (short):**
Given an integer array `nums`, compute the sum of widths (max - min) over all non-empty subsequences of `nums`. Return the result modulo `1e9 + 7`.

---

## Final C++ solution (as requested)

```cpp
class Solution {
    int MOD = 1e9 + 7;
public:
    int sumSubseqWidths(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        const int n = (int)nums.size();
        int ans = 0;
        vector<int> binpow(n,0);
        binpow[0] = 1;
        for(int i = 1;i<n;i++){
            binpow[i]= (binpow[i-1]*2)%MOD;
        }
        for (int i = 0; i < n; i++) {
            int add = binpow[i];
            int subtract = binpow[n - i - 1];
            ans = (ans + (1LL*nums[i]*(add - subtract) % MOD )+ MOD) % MOD;
        }
        return ans;
    }
};
```

---

## Overview of the approach (high-level intuition)

1. **Sort the array.** Sorting moves the smallest elements to the front and the largest to the back. This gives a deterministic ordering that we can reason about using indices.

2. **Count contributions per element.** After sorting, for each element `nums[i]`:

   * Count how many subsequences have `nums[i]` as the **maximum** — call this `count_max(i)`.
   * Count how many subsequences have `nums[i]` as the **minimum** — call this `count_min(i)`.
   * The net contribution of `nums[i]` to the final sum equals `nums[i] * (count_max(i) - count_min(i))`.

3. **Why counting is easy after sorting.**

   * To make `nums[i]` the maximum, we must include `nums[i]` and we may freely choose any subset of earlier elements (`0..i-1`) to include or not. There are `2^i` such subsets. So `count_max(i) = 2^i`.
   * To make `nums[i]` the minimum, we must include `nums[i]` and we may freely choose any subset of later elements (`i+1..n-1`) to include or not. There are `2^{n-i-1}` such subsets. So `count_min(i) = 2^{n-i-1}`.

4. **Combine contributions.**

   * Total = `sum_{i=0..n-1} nums[i] * (2^i - 2^{n-i-1})`.

5. **Compute modulo `1e9+7`.** Since values grow exponentially, compute powers of two modulo `MOD` and perform modular arithmetic carefully.

---

## Line-by-line explanation of the provided code

### Declarations

```cpp
class Solution {
    int MOD = 1e9 + 7;
public:
```

* `MOD` is the modulus `1000000007`. Declared once for reuse.

### Sorting

```cpp
        sort(nums.begin(), nums.end());
        const int n = (int)nums.size();
```

* Sorting gives us the non-decreasing order needed to reason about min/max positions.
* `n` stores the array length for convenience.

### Precompute powers of two modulo MOD

```cpp
        int ans = 0;
        vector<int> binpow(n,0);
        binpow[0] = 1;
        for(int i = 1;i<n;i++){
            binpow[i]= (binpow[i-1]*2)%MOD;
        }
```

* `ans` will accumulate the final answer.
* `binpow[i]` stores `2^i % MOD`.
* Precomputing powers of two allows O(1) access during contribution computation and avoids repeated exponentiation.
* We use `int` for `binpow` because every entry is stored modulo `MOD` and fits within 32-bit signed integer range.

### Compute contributions and accumulate

```cpp
        for (int i = 0; i < n; i++) {
            int add = binpow[i];
            int subtract = binpow[n - i - 1];
            ans = (ans + (1LL*nums[i]*(add - subtract) % MOD )+ MOD) % MOD;
        }
        return ans;
```

* For each `i`:

  * `add` = `2^i % MOD` (number of subsequences where `nums[i]` is max).
  * `subtract` = `2^{n-i-1} % MOD` (number of subsequences where `nums[i]` is min).
  * Contribution = `nums[i] * (add - subtract)`.
  * We multiply by `1LL` to perform the multiplication in 64-bit to avoid overflow before taking `% MOD`.
  * `( ... % MOD ) + MOD) % MOD` ensures the value is non-negative after subtracting; standard trick to avoid negative residues.
* Finally, return `ans` which is already in the range `[0, MOD-1]`.

---

## Complexity analysis

* **Time complexity:**

  * Sorting: `O(n log n)`.
  * Precomputing powers of two: `O(n)`.
  * Summing contributions: `O(n)`.
  * Total: `O(n log n)` due to the sorting step.

* **Space complexity:**

  * `O(n)` extra for the `binpow` array (you can optimize to `O(1)` extra by computing powers on the fly, but precomputation is clearer and still linear).

---

## Correctness and subtle correctness notes

1. **Single-element subsequences:** Even though single-element subsequences have width `0`, they are included in counts `2^i` and `2^{n-i-1}` (because when the element alone is chosen, it is both min and max). Their contributions cancel out across the sum when appropriate, and including them in counts is necessary to get counting consistent.

2. **Why `2^i` and `2^{n-i-1}` are exact counts:**

   * For `nums[i]` to be max, any subset of earlier indices `[0..i-1]` may or may not be included: exactly `2^i` choices.
   * For `nums[i]` to be min, any subset of later indices `[i+1..n-1]` may or may not be included: `2^{n-i-1}` choices.

3. **Why sorting is required:** Without sorting, the notion of earlier/later elements corresponding to strictly smaller/larger values breaks down, and counting becomes more complicated because an element could be larger than some later elements. Sorting ensures that indices reflect relative order.

4. **Modular arithmetic caution:** Intermediate subtraction `(add - subtract)` can be negative. Wrapping with `+ MOD` and then `% MOD` makes it safe.

---

## Variations and small optimizations

1. **Space optimization (optional):** you can compute `2^i` on the fly while iterating `i` if you prefer `O(1)` extra space:

```cpp
long long pow2_i = 1;
for (int i = 0; i < n; ++i) {
    long long add = pow2_i;
    long long subtract = binpow[n - i - 1]; // or compute reverse powers on the fly too
    // contribution ...
    pow2_i = (pow2_i * 2) % MOD;
}
```

2. **Precompute reverse powers** if you want both `2^i` and `2^{n-i-1}` without indexing: compute `pow2[i] = 2^i` and then use `pow2[n-i-1]` as done in the current implementation.

3. **Use 64-bit for `ans` internally** if you want fewer casts. The current code carefully uses `1LL * nums[i] * (...)` which is sufficient, and the final `ans` fits in int modulo `MOD`.

---

## Example walk-through (small array)

`nums = [2, 1, 3]`

* Sorted: `[1, 2, 3]`, `n = 3`.
* `binpow = [1, 2, 4]`.

Loop:

* `i = 0`: add = 1, subtract = 4, contribution = `1 * (1 - 4) = -3` → mod = `MOD - 3`.
* `i = 1`: add = 2, subtract = 2, contribution = `2 * 0 = 0`.
* `i = 2`: add = 4, subtract = 1, contribution = `3 * (4 - 1) = 9`.
* Sum = `-3 + 0 + 9 = 6` → final result `6`.

Matches the sample.

---

## Edge cases & tests to try

* Smallest `n = 1` (e.g., `[x]`) → result `0`.
* All equal elements (e.g., `[5,5,5]`) → result `0` because max == min in every subsequence.
* Already sorted ascending / descending — algorithm should handle both after sorting.
* Large `n` near constraint (`n = 1e5`) to validate performance and that modulus handling is correct.

---

## Notes 

* You used a clear and compact approach: sort, precompute `2^i`, iterate and accumulate. Keep those variable names and the modular arithmetic idioms (like `+ MOD`) — they are standard and readable.

* If you want the code to read more like *your personal style*, consider renaming `binpow` to `pow2`, `add` to `countMax`, and `subtract` to `countMin`. Small naming tweaks help make the code feel personally authored.

Example with renamed variables (optional):

```cpp
vector<int> pow2(n, 0);
pow2[0] = 1;
for (int i = 1; i < n; ++i) pow2[i] = (pow2[i-1] * 2) % MOD;

for (int i = 0; i < n; ++i) {
    int countMax = pow2[i];
    int countMin = pow2[n-i-1];
    ans = (ans + (1LL * nums[i] * (countMax - countMin) % MOD) + MOD) % MOD;
}
```

---

