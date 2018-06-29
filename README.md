# Time Performance
Performance of various time functions:

```
noop ~= max(MHz)                                  2995.23
time()                                            419.123 
gettimeofday()                                    52.184 
std::chrono::steady_clock::now()                  47.1827 
std::chrono::system_clock::now()                  45.3317 
std::chrono::high_resolution_clock::now()         45.653
```