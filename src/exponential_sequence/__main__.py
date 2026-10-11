from exponential_sequence import ExponentialSequence

if __name__ == "__main__":
    seq = ExponentialSequence(45, 5, 3)
    print(f"a_5 = {seq.get_term(5)}")
    print(f"Sum for N=10 = {seq.sum_terms(10)}")
