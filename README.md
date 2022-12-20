# scriptRunner

It is a utility build to run shell scripts in Linux systems. It adds few additional features like -
- timely executiong of a command, i.e a command can be executed with certain ammount of delay. Example 
  `command ---set-time #`
- Add background process. It is similar to running commands in daemon. Example 
  `command ---background`
- Allow cd in shell scripting. Initial cwd is considered as the directory where the script is located.

### Installation guide:

```bash
$ git clone git@github.com:abhinaba-fbr/scriptRunner.git
$ cd /path/to/scriptRunner
$ make install
```
### Runing experiments:

```bash
$ scriptRunner /path/to/sctipt.sh
```

### Uninstall Guide:

```bash
$ cd /path/to/scriptRunner
$ make uninstall
```

*NOTE: incase make install does not work, make with sudo.*
