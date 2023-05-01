PERIOD = 16

LOOP_LEN = 512
voltages = list(range(LOOP_LEN))

outputs = {}

duty_cycle = 0
p = 0
for v in voltages:
    if p == PERIOD:
        p = 0
        duty_cycle = v * PERIOD / LOOP_LEN
    else:
        p += 1

    if p < duty_cycle:
        outputs[v] = 1
    else:
        outputs[v] = 0

with open("outs.pwl", "w") as of:
    out_str = ""
    for i in range(5):
        for out in outputs:
            out_str += f'{out*50 + 50*LOOP_LEN*i}n {outputs[out]}\n'
    of.write(out_str)
