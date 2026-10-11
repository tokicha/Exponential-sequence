class ExponentialSequence:
    def __init__(self, base: int, multiplier: int, columns: int):
        assert columns > 0, "Columns must be greater than zero"
        self.base = base
        self.multiplier = multiplier
        self.columns = columns

    def _geometric_sum(self, s: int, count: int) -> int:
        if count == 0:
            return 0
        if s == 1:
            return count
        return s * (pow(s, count) - 1) // (s - 1)

    def get_term(self, k: int) -> int:
        """Calculate the k-th term in O(1) time."""
        assert k >= 1, "k must be >= 1"
        q = (k - 1) // self.columns
        r = (k - 1) % self.columns
        
        term_b = pow(self.base, q + 1)
        term_s = pow(self.multiplier, r + 1)
        return term_b * term_s

    def sum_terms(self, N: int) -> int:
        """Calculate the prefix sum S_N in O(1) time."""
        if N == 0:
            return 0
        q = N // self.columns
        r = N % self.columns

        block_sum = self._geometric_sum(self.multiplier, self.columns)
        row_sum = q if self.base == 1 else (pow(self.base, q) - 1) * self.base // (self.base - 1)

        sum_full_blocks = block_sum * row_sum
        sum_remaining = pow(self.base, q + 1) * self._geometric_sum(self.multiplier, r) if r > 0 else 0

        return sum_full_blocks + sum_remaining
