### Day (2)
## Question (2)

It is executed from any other directory because the `/usr/local/bin` is included in the `PATH`.

---

### 1. `cat /etc/shells`

Displays the available shells on the system:
`bash`, `dash`, `rbash`, `sh`

---

### 2. `env`

Lists all the environment variables in the shell.

---

### 3. `echo $SHELL`

Displays the current shell:
`/bin/bash`

---

### 4. `\`

Allows you to continue the command on another line.

---

### 5. Aliases

**Temporary alias:**

```bash
alias PrintPath='echo $PATH'
```

**More permanent alias:**

```bash
  echo "alias PrintPath='echo $PATH'" >> ~/.bashrc
```

Puts the alias in the `.bashrc` so it gets initialized with every new shell.

