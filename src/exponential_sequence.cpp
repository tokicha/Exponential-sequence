#include <iostream>
#include <cassert>

class ExponentialSequence {
private:
    unsigned long long base;
    unsigned long long multiplier;
    unsigned long long columns;

    // Fast modular/standard exponentiation helper
    unsigned long long power(unsigned __int128 b, unsigned long long exp) const {
        unsigned __int128 res = 1;
        while (exp > 0) {
            if (exp % 2 == 1) res *= b;
            b *= b;
            exp /= 2;
        }
        return (unsigned long long)res;
    }

    // Closed-form geometric sum for terms
    unsigned long long geometric_sum(unsigned long long s, unsigned long long count) const {
        if (count == 0) return 0;
        if (s == 1) return count;
        unsigned __int128 num = (unsigned __int128)s * (power(s, count) - 1);
        return (unsigned long long)(num / (s - 1));
    }

public:
    ExponentialSequence(unsigned long long b, unsigned long long s, unsigned long long m) 
        : base(b), multiplier(s), columns(m) {
        assert(m > 0 && "Columns must be greater than zero");
    }

    // Calculate k-th term in O(1) time
    unsigned long long get_term(unsigned long long k) const {
        assert(k >= 1 && "k must be >= 1");
        unsigned long long q = (k - 1) / columns;
        unsigned long long r = (k - 1) % columns;
        
        unsigned __int128 term_b = power(base, q + 1);
        unsigned __int128 term_s = power(multiplier, r + 1);
        
        return (unsigned long long)(term_b * term_s);
    }

    // Calculate prefix sum S_N in O(1) time
    unsigned long long sum_terms(unsigned long long N) const {
        if (N == 0) return 0;
        unsigned long long q = N / columns;
        unsigned long long r = N % columns;

        unsigned long long block_sum = geometric_sum(multiplier, columns);
        unsigned long long row_sum = (base == 1) ? q : (unsigned long long)((power(base, q) - 1) * base / (base - 1));

        unsigned __int128 sum_full_blocks = (unsigned __int128)block_sum * row_sum;
        unsigned __int128 sum_remaining = (r > 0) ? (unsigned __int128)power(base, q + 1) * geometric_sum(multiplier, r) : 0;

        return (unsigned long long)(sum_full_blocks + sum_remaining);
    }
};

int main() {
    // Test the engine locally
    ExponentialSequence seq(45, 5, 3);
    std::cout << "a_5 = " << seq.get_term(5) << std::endl;
    std::cout << "Sum for N=10 = " << seq.sum_terms(10) << std::endl;
    return 0;
}
