# Exponential Sequence Engine

A high-performance $O(1)$ time complexity mathematical sequence engine that computes arbitrary-scale terms and prefix sums efficiently across multiple programming languages.

## Features
* **Constant Time Performance ($O(1)$):** Direct formula-based calculation for both individual terms and range prefix sums without iteration.
* **Multi-Language Support:** Native implementations available in **C++**, **Python**, and **Java**.
* **Arbitrary Precision:** Built-in safeguards or big integer utilities to handle rapid exponential growth without integer overflow.

---

## Project Structure

```text
exponential-sequence/
├── CMakeLists.txt
├── Dockerfile
├── LICENSE
├── README.md
├── pyproject.toml
├── src/
│   ├── exponential_sequence.cpp
│   └── exponential_sequence/
│       ├── __init__.py
│       └── __main__.py
└── java/
    └── ExponentialSequence.java

mkdir -p build && cd build
cmake ..
make
./exponential_sequence

python -m exponential_sequence

javac java/ExponentialSequence.java
java -cp java ExponentialSequence


---

### 2. Push the Updated README to GitHub

Once the file is written, commit and push the changes to sync your live repository:

```bash
git add README.md
git commit -m "Add comprehensive multi-language README documentation"
git push origin main
git add README.md
git commit -m "Add comprehensive multi-language README documentation"
git push origin main

cargo new rust --bin

struct ExponentialSequence {
    base: u64,
    multiplier: u64,
    columns: u32,
}

impl ExponentialSequence {
    pub fn new(base: u64, multiplier: u64, columns: u32) -> Self {
        assert!(columns > 0, "Columns must be greater than zero");
        Self { base, multiplier, columns }
    }

    fn geometric_sum(&self, s: u64, count: u32) -> u64 {
        if count == 0 {
            return 0;
        }
        if s == 1 {
            return count as u64;
        }
        let pow_val = s.pow(count);
        s * (pow_val - 1) / (s - 1)
    }

    pub fn get_term(&self, k: u64) -> u64 {
        assert!(k >= 1, "k must be >= 1");
        let k_minus_1 = k - 1;
        let q = k_minus_1 / self.columns as u64;
        let r = k_minus_1 % self.columns as u64;

        let term_b = self.base.pow((q + 1) as u32);
        let term_s = self.multiplier.pow((r + 1) as u32);
        term_b * term_s
    }

    pub fn sum_terms(&self, n: u64) -> u64 {
        if n == 0 {
            return 0;
        }
        let q = n / self.columns as u64;
        let r = n % self.columns as u64;

        let block_sum = self.geometric_sum(self.multiplier, self.columns);
        
        let row_sum = if self.base == 1 {
            q
        } else {
            (self.base.pow(q as u32) - 1) * self.base / (self.base - 1)
        };

        let sum_full_blocks = block_sum * row_sum;
        let sum_remaining = if r > 0 {
            self.base.pow((q + 1) as u32) * self.geometric_sum(self.multiplier, r as u32)
        } else {
            0
        };

        sum_full_blocks + sum_remaining
    }
}

fn main() {
    let seq = ExponentialSequence::new(45, 5, 3);
    println!("a_5 = {}", seq.get_term(5));
    println!("Sum for N=10 = {}", seq.sum_terms(10));
}

cat << 'EOF' > rust/src/main.rs
struct ExponentialSequence {
    base: u64,
    multiplier: u64,
    columns: u32,
}

impl ExponentialSequence {
    pub fn new(base: u64, multiplier: u64, columns: u32) -> Self {
        assert!(columns > 0, "Columns must be greater than zero");
        Self { base, multiplier, columns }
    }

    fn geometric_sum(&self, s: u64, count: u32) -> u64 {
        if count == 0 {
            return 0;
        }
        if s == 1 {
            return count as u64;
        }
        let pow_val = s.pow(count);
        s * (pow_val - 1) / (s - 1)
    }

    pub fn get_term(&self, k: u64) -> u64 {
        assert!(k >= 1, "k must be >= 1");
        let k_minus_1 = k - 1;
        let q = k_minus_1 / self.columns as u64;
        let r = k_minus_1 % self.columns as u64;

        let term_b = self.base.pow((q + 1) as u32);
        let term_s = self.multiplier.pow((r + 1) as u32);
        term_b * term_s
    }

    pub fn sum_terms(&self, n: u64) -> u64 {
        if n == 0 {
            return 0;
        }
        let q = n / self.columns as u64;
        let r = n % self.columns as u64;

        let block_sum = self.geometric_sum(self.multiplier, self.columns);
        
        let row_sum = if self.base == 1 {
            q
        } else {
            (self.base.pow(q as u32) - 1) * self.base / (self.base - 1)
        };

        let sum_full_blocks = block_sum * row_sum;
        let sum_remaining = if r > 0 {
            self.base.pow((q + 1) as u32) * self.geometric_sum(self.multiplier, r as u32)
        } else {
            0
        };

        sum_full_blocks + sum_remaining
    }
}

fn main() {
    let seq = ExponentialSequence::new(45, 5, 3);
    println!("a_5 = {}", seq.get_term(5));
    println!("Sum for N=10 = {}", seq.sum_terms(10));
}
