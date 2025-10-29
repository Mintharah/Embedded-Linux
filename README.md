# Embedded-Linux
## Day (1) Questions

1. Ubuntu, Debian, Arch

2. It is a full manual for some commands

3. ```bash
   rm [OPTION]... [FILE]...
   ````
   Removes files or directories (all of them if `-r` aka recursive is added), while:

   ```bash
   rmdir [OPTION]... DIRECTORY...
   ```

   Removes empty directories.

a. Couldn't remove directory because it isn’t empty → overcome it by using `-rf` (force) with `rm`

b. It wouldn’t get removed because it’s not a directory (OldFiles)


5. Absolute path: `/home/user/docs/mycv`
   Relative path: `~/docs/mycv`


6. ```bash
   cd ~
   cd /home
   cd ../../home

   ````

9. `type` tells you what kind of command something is and how the shell interprets it.

10. Cancel is `/usr/bin/cancel` and cat is `/usr/bin/cat`.

11. ```bash
      man -k '^read'
      ````
Lists all commands whose description starts with "read".

12. `apropos` command is similar to `man -k [keyword]`; it searches the man page descriptions for a given keyword.

Bash Script:

```bash
#!/bin/bash
mkdir -p myDirectory/secondDirectory
cd myDirectory/secondDirectory
touch myNotePaper
cp myNotePaper /home/myDirectory
cd ..
mv myNotePaper myOldNotePaper
```
