import os

def set_params(params):
    global control_params
    control_params = params

def get_params():
    dicts = {}
    with open("./m5out/stats.txt", "r") as fd:
        for line in fd:
            line_ele = line.split(" ")
            if len(line_ele) > 3:
                my_line = line_ele
                key = my_line[0]
                val = my_line[2]
                dicts[key].append(val)
    return dicts

def run_simulation(control_params=None):
    os_command = "./build/X86/gem5.opt configs/user/soc.py"
    if control_params:
        for param, value in control_params.items():
            os_command += " --{}={}".format(param, value)
    os.system(os_command)
