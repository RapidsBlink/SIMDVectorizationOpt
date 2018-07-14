## Bidirectional Speed

(compression + decompression) on base64 chars

### LCCPU 

* 5.4 avg compression

```
16:27:34 INFO  /homes/ywangby/workspace/yche/git-repos/queuerace/src/playground/test_serialization.cpp:102: elapsed time: 43.940151s
16:27:34 INFO  /homes/ywangby/workspace/yche/git-repos/queuerace/src/playground/test_serialization.cpp:106: TPS: 125.882840 MB/s
```

* chromium

```
16:25:15 INFO  /homes/ywangby/workspace/yche/git-repos/queuerace/src/playground/test_serialization.cpp:102: elapsed time: 16.576887s
16:25:15 INFO  /homes/ywangby/workspace/yche/git-repos/queuerace/src/playground/test_serialization.cpp:106: TPS: 333.676099 MB/s
```

* klompa

```
16:18:31 INFO  /homes/ywangby/workspace/yche/git-repos/queuerace/src/playground/test_serialization.cpp:102: elapsed time: 15.188027s
16:18:31 INFO  /homes/ywangby/workspace/yche/git-repos/queuerace/src/playground/test_serialization.cpp:106: TPS: 364.188903 MB/s
```

* lemire-fast

```
16:22:19 INFO  /homes/ywangby/workspace/yche/git-repos/queuerace/src/playground/test_serialization.cpp:102: elapsed time: 13.891104s
16:22:19 INFO  /homes/ywangby/workspace/yche/git-repos/queuerace/src/playground/test_serialization.cpp:106: TPS: 398.190895 MB/s
```