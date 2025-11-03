# DAY 3

## Section (1)

I overwrote my `.bashrc` on the first attempt by using `>` instead of `>>`, then recovered it from `/etc/skel/.bashrc`. After running the script, a new terminal opens up and if I `echo "$HELLO"` or `"$LOCAL"`, the `HOSTNAME` and `whoami` are replaced with my username.

### Steps:

```bash
touch check_bashrc.sh
vim check_bashrc.sh
```

Add the following content:

```bash
#!/bin/bash
BASHRC="$HOME/.bashrc"

if [ -f "$BASHRC" ]; then
    echo "HELLO=$(hostname) LOCAL=$(whoami)" >> ~/.bashrc
    echo "variables added(:"
    gnome-terminal
else
    echo ".bashrc doesnt exist in the home directory:("
fi
```

Save and run the file:

```bash
./check_bashrc.sh
```

---

## Section (2)

1. List all commands in `/usr/bin` and save to a file:

```bash
ls /usr/bin/ > /tmp/commands.list
```

2. To display the date at login, edit the `.profile` to add `date` and edit the `PS1` line in `.bashrc` to permanently change the prompt.

3. To count the number of words in a file, use:

```bash
wc -w [file name]
```

a. Count the number of lines in `/tmp/commands.list`:

```bash
wc -l /tmp/commands.list
# Output: 1467 commands in /tmp/commands.list
```

4. Examples:

   a. The output of `cat filename1 | cat filename2` is the content of `filename2`.

   b. `rm` without arguments:

```
rm: missing operand
Try 'rm --help' for more information.
```

c. `ls /etc/passwd | wc -l` outputs `1` because `ls /etc/passwd` outputs the filename (`passwd`) and `|` sends it to `wc -l` to count lines.

5. Find `.profile` file with sudo:

```bash
sudo find / -type f -name ".profile"
```

Explanation:

* `sudo`: gives permission to look through all system files
* `/`: start looking from the root
* `-type f`: look for files only, not directories
* `-name ".profile"`: look for the file named exactly `.profile`

6. Inodes of some files/directories:

```
/: 2
/etc: 9699329
/etc/hosts: 9699493
```

7. Create a symbolic link:

```bash
sudo ln -s /etc/passwd /boot
```

8. Create a hard link:

```bash
sudo ln /etc/passwd /boot
```

> I could, but I’m not sure I was supposed to. I checked using `lsblk` and my root and boot aren’t on the same memory block.

9. `>` is the value of the environment variable `PS2` (the secondary prompt) when Bash expects more input.
   It can be changed in `.bashrc`:

```bash
PS1="gimme more input(: "
# or
PS1=": "
```
