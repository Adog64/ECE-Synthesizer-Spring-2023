PERIOD = 16

LOOP_LEN = 512
voltages = list(range(LOOP_LEN//2))
voltages.extend(voltages[::-1])

time_steps = list(range(LOOP_LEN))
outputs = {}

duty_cycle = 0
p = 0
for t in time_steps:
    if p == PERIOD:
        p = 0
        duty_cycle = 2 * voltages[t] * PERIOD / LOOP_LEN
    else:
        p += 1

    if p < duty_cycle:
        outputs[t] = 3.3
    else:
        outputs[t] = 0

with open("tri_outs.pwl", "w") as of:
    print(voltages)
    out_str = ""
    for i in range(15):
        for out in outputs:
            out_str += f'{out*100 + 100*LOOP_LEN*i}n {outputs[out]}\n'
    of.write(out_str)
