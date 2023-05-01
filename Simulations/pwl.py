PERIOD = 16
voltages = list(range(256))

outputs = {}

duty_cycle = 0
p = 0
for v in voltages:
    if p == PERIOD:
        p = 0
        duty_cycle = v * PERIOD / 256
    else:
        p += 1

    if p < duty_cycle:
        outputs[v] = 1
    else:
        outputs[v] = 0

with open("outs.pwl", "w") as of:
    out_str = ""
    for out in outputs:
        out_str += f'{out}: {outputs[out]}\n'
    of.write(out_str)
