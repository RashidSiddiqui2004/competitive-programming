import random

def generate_large_test_case(N_max=200000, M_max=200000, T=1, filepath="large_test_case.txt"):
    """
    Generates a large test case file for competitive programming problems
    with N and M near the maximum constraints.

    This test case uses a single test case (T=1) with max N and M,
    structured as a long chain with many random back edges to stress
    graph traversal algorithms.
    """
    
    # Use the maximum constraints for N and M
    N = N_max
    M = M_max
            
    print(f"Generating test case file: {filepath}")
    print(f"Total Test Cases (T): {T}")
    print(f"Nodes (N): {N:,}, Edges (M): {M:,}")

    try:
        with open(filepath, 'w') as f:
            # Write the total number of test cases (T)
            f.write(f"{T}\n")

            for _ in range(T):
                # Write N and M for the single test case
                f.write(f"{N} {M}\n")

                pairs = set()
                
                # 2. Add random, possibly duplicate, back edges to reach M_max
                while len(pairs) != M:
                    # Pick two random nodes between 1 and N
                    u = random.randint(1, N)
                    v = random.randint(1, N)
                    uv = (u, v)
                    if uv not in pairs:
                        pairs.add((u, v))
                
                # Write all the generated edges
                for u, v in pairs:
                    f.write(f"{u} {v}\n")
        
        print(f"Successfully created {filepath}.")
        
    except Exception as e:
        print(f"An error occurred while writing the file: {e}")

# Execute the function to create the file
# N=200,000, M=200,000, T=1
generate_large_test_case(N_max=100000, M_max=100000, T=100)
