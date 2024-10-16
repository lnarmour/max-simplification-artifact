from matplotlib import pyplot as plt
import numpy as np
import sys

def main():
    if len(sys.argv) < 5:
        print('usage: {} results_file name baseline_complexity simplified_complexity'.format(sys.argv[0]))
        sys.exit(1)
    
    name = sys.argv[2]
    baseline_complexity = int(sys.argv[3])
    simp_complexity = int(sys.argv[4])

    with open(sys.argv[1], 'r') as f:    
        data = []
        for line in [l.replace('\n', '') for l in f.readlines() if l[0] != '#']:
            version, N, exec_time = line.split(',')
            N = int(N)
            exec_time = float(exec_time)
            if (version == 'baseline'):
                version = 0
            else:
                version = int(version[1:]) + 1
            entry = [version, N, exec_time]
            data.append(entry)
    
    data = np.array(data)

    # expected complexities
    baseline = data[data[:,0] == 0]
    first_simp = data[data[:,0] == 1]

    Ns = baseline[:,1]
    n0 = Ns[0]
    b0 = baseline[0][2]
    s0 = first_simp[0][2]

    # scaling factors to shift the expected plots (N, N^2, or N^3) down to
    # ilne up with the actual measured data
    b_scaling_factor = (n0 ** baseline_complexity) / b0 * 1.1
    s_scaling_factor = (n0 ** simp_complexity) / s0 * 1.5

    exp_baseline_perf = np.array([n**baseline_complexity for n in Ns]) / b_scaling_factor
    exp_simp_perf = np.array([n**simp_complexity for n in Ns]) / s_scaling_factor
    
    plt.plot(Ns, exp_simp_perf, linestyle='dashed', label='O(N^{})'.format(simp_complexity))
    plt.plot(Ns, exp_baseline_perf, linestyle='dashed', label='O(N^{})'.format(baseline_complexity))
    
    simplification_nums = list(set(data[data[:,0] != 0][:,0]))
    
    plt.plot(Ns, baseline[:,2], label='baseline')

    for s in simplification_nums:
        s_data = data[data[:,0] == s][:,2]
        plt.plot(Ns, s_data, label='v{}'.format(int(s+1)))

    plt.title(name)
    plt.legend()
    plt.xlabel('Problem size (N)')
    plt.ylabel('Execution time (sec)')
    plt.xscale('log')
    plt.yscale('log')

    plt.tight_layout()
    plt.savefig('plot_{}.png'.format(name), dpi=300)

    print("Saved plot to file 'plot_{}.png'".format(name))


if __name__ == '__main__':
    main()
