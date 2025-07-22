# 🔗 pipex

Recreating the Unix shell’s power… one pipe at a time.

Welcome to **pipex** — a 42 project where you dive into how Unix pipelines work under the hood. You’ll be handling pipes, forks, file descriptors, and executing commands just like a mini-shell. Spoiler: it’s all about mastering input/output redirection and process control.

---

## 🚀 Project Overview

**pipex** is a foundational systems programming project from the 42 curriculum.
Goal: replicate the behavior of shell piping, like this:

```bash
< infile cmd1 | cmd2 > outfile
```

🔁 Redirect input & output
🔗 Connect multiple commands using pipes
🧠 Manage child processes & execve

---

## 📚 How It Works

Imagine this shell command:

```bash
< infile grep hello | wc -l > outfile
```

With **pipex**, your program mimics that logic:

```bash
./pipex infile "grep hello" "wc -l" outfile
```

What happens behind the scenes:

1. Open `infile` for reading.
2. Execute `grep hello`, with `infile` as input.
3. Pipe the output of `grep` to `wc -l`.
4. Write the final output to `outfile`.

---

## 🧠 Key Concepts Covered

* File descriptors & redirection
* Creating and handling pipes
* `fork()` and `execve()`
* Parsing and splitting shell-like command strings
* Environment path resolution
* Error handling (permission denied, file not found, etc.)
* Manual memory management (no leaks allowed!)

---

## 🛠️ Technologies

* **Language:** C
* **System Calls:** `fork`, `pipe`, `dup2`, `execve`, `access`, `waitpid`, `open`, `close`
* **OS:** Linux
* **Tools:** Makefile, Valgrind

---

## 📦 How to Use

Clone the repository:

```bash
git clone https://github.com/your-username/pipex.git
cd pipex
```

Build the project:

```bash
make
```

Run it:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

✅ Example:

```bash
./pipex infile "cat" "wc -l" outfile
```

This mimics:

```bash
cat < infile | wc -l > outfile
```

---

## ✨ Bonus Features 

* 📜 Support for **multiple pipes**:

  ```bash
  ./pipex infile "grep a" "sort" "uniq" outfile
  ```
* 🧪 Handle shell-like parsing (quotes, escapes)
* 🔄 Support for here\_doc (like `<<`)
* 🧼 Cleanup everything like a pro (even zombies)

---

## 🧪 Example Workflow

```bash
$ echo -e "apple\nbanana\napple" > input.txt
$ ./pipex input.txt "grep apple" "wc -l" output.txt
$ cat output.txt
2
```

---

## 💡 Lessons Learned

* Processes are tricky — especially with forking and waiting.
* Pipes are simple… until you're chaining 4+ commands.
* Error messages matter more than you think.
* Shell does a *lot* for you — now you appreciate it.
* Handling execve paths manually really teaches you about `envp`.
