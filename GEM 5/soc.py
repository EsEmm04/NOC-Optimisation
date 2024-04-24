import m5
from m5.objects import *

# Instantiate the system
system = System()

# Create a TimingSimpleCPU
cpu = TimingSimpleCPU()

# Create a Memory controller
mem_ctrl = DDR3_1600_8x8()

# Create a VirtioBlock device
virtio_block = VirtIOBlock()

# Create a SimpleNetwork
network = SimpleNetwork()

# Create MessageBuffers for CPU and VirtioBlock
cpu_buffer1 = MessageBuffer()
cpu_buffer2 = MessageBuffer()
virtio_buffer1 = MessageBuffer()
virtio_buffer2 = MessageBuffer()

# Create a Switch
switch = Switch(virt_nets=1)

# Connect CPU to the buffers
cpu_buffer1.out_port = switch.in_ports
cpu_buffer2.out_port = switch.in_ports

# Connect the VirtioBlock device to the buffers
virtio_buffer1.out_port = switch.in_ports
virtio_buffer2.out_port = switch.in_ports

# Connect the switch to the network
switch.out_ports = [network.in_port]

# Connect the network to the memory controller
network.out_port = mem_ctrl.port

# Set up the system ports
system.cpu = cpu
system.mem_ctrl = mem_ctrl
system.system_port = virtio_block.port

# Set up the root object
root = Root(full_system=False, system=system)

# Instantiate all objects
m5.instantiate()

# Simulate
print("Running the simulation")
exit_event = m5.simulate()

# Print simulation exit information
print("Exiting @ tick {} because {}".format(m5.curTick(), exit_event.getCause()))