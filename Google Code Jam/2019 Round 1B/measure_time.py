import sys
import time
import subprocess

def run_command(stdin, stdout):
    subprocess.run(sys.argv[1].split(), stdin=stdin, stdout=stdout)

start_time = time.time()
if len(sys.argv) > 2:
    with open(sys.argv[2], "r") as stdin:
        if len(sys.argv) > 3:
            with open(sys.argv[3], "w") as stdout:
                run_command(stdin, stdout)
        else:
            run_command(stdin, None)
else:
    run_command(None, None)
print("Time:", time.time()-start_time)