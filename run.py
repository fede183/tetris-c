import subprocess, os

subprocess.run(["rm", "-rf", "build"])
subprocess.run("conan install . --output-folder=build --build=missing", shell=True)

subprocess.run("cp CMakeLists.txt build", shell=True)
subprocess.run("cp -r fonts build", shell=True)
subprocess.run("cp -r images build", shell=True)
subprocess.run("cp -r sounds build", shell=True)

path = os.getcwd()
os.chdir(path + "/build")

subprocess.run("cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release", shell=True)
subprocess.run("cmake --build build", shell=True)
subprocess.run("make", shell=True)
subprocess.run("./Tetris_C++", shell=True)

os.chdir(path)
