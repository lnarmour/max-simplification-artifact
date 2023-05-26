from matplotlib import pyplot as plt
import numpy as np
import sys

def main():
    if len(sys.argv) < 2:
        print('usage: {} results_file'.format(sys.argv[0]))
        sys.exit(1)

    with open(sys.argv[1], 'r') as f:
        data = [[int(v) for v in line.split(',')] for line in f.readlines() if line[0] != '#']

    data = np.array(data)

    f, axs = plt.subplots(1, 3, figsize=(15,5))

    # create plots
    for i,ex_num in enumerate([1, 2, 3]):
        ex_data = data[data[:,0]==ex_num, 1:]
        Ns = ex_data[:,0]
        input_ops = ex_data[:,1]
        simplified_ops = ex_data[:,2]
    
        axs[i].plot(Ns, input_ops, '.-', label='input reduction')
        axs[i].plot(Ns, simplified_ops, '.-', label='simplified reduction')

        linear = [N for N in Ns]
        quadratic = [N**2 for N in Ns]
        cubic = [N**3 for N in Ns]
        quartic = [N**4 for N in Ns]
        if ex_num < 3:    
            axs[i].plot(Ns, linear, '--', label='O(N)', alpha=0.5)
        axs[i].plot(Ns, quadratic, '--', label='O(N^2)', alpha=0.5)
        if ex_num == 3:
            axs[i].plot(Ns, cubic, '--', label='O(N^3)', alpha=0.5)
            axs[i].plot(Ns, quartic, '--', label='O(N^4)', alpha=0.5)
        axs[i].legend()
        axs[i].set_title('Exercise {}'.format(ex_num))
        axs[i].set_xlabel('Problem size (N)')
        axs[i].set_ylabel('Number of reduction operations')
        axs[i].set_xscale('log')
        axs[i].set_yscale('log')

    plt.tight_layout()
    plt.savefig('plot.png', dpi=300)


if __name__ == '__main__':
    main()
