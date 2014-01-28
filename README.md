# Rehash

<p align="justify">This application changes the hash of any executable without affecting its functionality. It does this by appending a block of sixteen bytes to the end of the file. The first byte of the block is always zero, followed by eight randomized bytes and finishing off with seven zero bytes. Files must end with ".exe" in order to be processed. Multiple file support is included.</p>

### Input
```bash
$ Rehash [Filename1] [...]
```

### Output
* 0 - No errors occurred
* 1 - No filename was passed
* 2 - File is not compatible
* 3 - File could not be opened

### Author
* Email: <dave@krutsko.net>
* Home: [dave.krutsko.net](http://dave.krutsko.net)
* GitHub: [github.com/dkrutsko](https://github.com/dkrutsko)