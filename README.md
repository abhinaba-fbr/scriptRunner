# ScriptRunner

It is a utility build to run shell scripts in Linux systems with few additional features listed below -
- Timely executiong of a command, i.e a command can be executed with certain ammount of delay in background (interpretation continues). Example 
  `command ---set-time #`
- Timely executiong of a command, i.e a command can be executed with certain ammount of delay in forground (interpretation moves ahead only after the current process execution completes). Example 
  `command ---set-time-wait #`
- Add background process. It is similar to running commands in daemon. Example 
  `command ---background`
- Allow cd in shell scripting. Initial cwd is considered as the directory where the script is located.

### Installation guide:

Build process follows a usual CMake project build as follows -

```bash
$ git clone git@github.com:abhinaba-fbr/scriptRunner.git
$ cd /path/to/scriptRunner
$ mkdir build
$ cd build && cmake .. && make
```
The above steps will only create a local binary to run

To install the ScriptRunner as an executable system-wide use -
```bash
$ make install
```
### Runing scripts:

```bash
$ scriptRunner /path/to/script.sh
```

### Logging in ScriptRunner

ScriptRunner also allows logging the commands along with the time taken to run each command in the script.

To use logging follow the below command.
```bash
$ scriptRunner /path/to/script.sh ---logging
or
$ scriptRunner ---logging /path/to/script.sh
```
The output logfile generated is ```scriptRunner.log```  by default and is generated in the current working directory

If you want to change the name of the output log file, use -
```bash
$ scriptRunner /path/to/scriptRunner.sh ---logging=my_log.log
```

### Uninstall Guide:

```bash
$ cd /path/to/scriptRunner
$ cd build/
$ make uninstall
```

*NOTE: incase make install or uninstall does not work, make with sudo.*
