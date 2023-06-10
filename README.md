# RSmlHT
Fast key value store

Currently only functional for testing and designed to map uint64_t to uint64_t

Uses a hierarchical, variable width hashtable design to reduce copying.

Currently it is able to index 1 million large integers (uint64_t) in 7260958 nanoseconds (7.26 milliseconds) on a M1 Pro mac book pro. Further benchmarks will prove more accuriate and provide comparison between different hash table implementations. 
