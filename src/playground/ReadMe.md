## SIMD FormBody Parsing and Dubbo Generation

labtop with avx2 support

```
-------------------
total hard code transform time: 31 ms

total serial transform time: 294 ms

total sse4 transform time: 182 ms

total avx2 transform time: 101 ms

-------------------
```

## Base64 Operations

labtop with avx2 support

### AVX2

base64, base64, base36, small-padding-base36

```
22:39:45 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
22:40:00 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 14.872578s
22:40:00 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 371.913407 MB/s
22:40:01 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
22:40:16 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 14.637860s
22:40:16 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 377.877020 MB/s
22:40:18 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
22:40:32 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 14.408320s
22:40:32 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 383.897003 MB/s
22:40:34 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
22:40:50 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 16.029329s
22:40:50 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 226.083221 MB/s

```

### Normal

```
22:41:52 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
22:42:09 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 16.707750s
22:42:09 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 331.062586 MB/s
22:42:11 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
22:42:27 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 16.824451s
22:42:27 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 328.766204 MB/s
22:42:29 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
22:42:46 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 16.677740s
22:42:46 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 331.658306 MB/s
22:42:48 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
22:43:05 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 17.551231s
22:43:05 INFO  /home/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 206.479097 MB/s

```