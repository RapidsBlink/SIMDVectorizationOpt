## CPU

```
Architecture:          x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                56
On-line CPU(s) list:   0-55
Thread(s) per core:    2
Core(s) per socket:    14
Socket(s):             2
NUMA node(s):          2
Vendor ID:             GenuineIntel
CPU family:            6
Model:                 79
Model name:            Intel(R) Xeon(R) CPU E5-2680 v4 @ 2.40GHz
Stepping:              1
CPU MHz:               1200.000
CPU max MHz:           3300.0000
CPU min MHz:           1200.0000
BogoMIPS:              4800.24
Virtualization:        VT-x
L1d cache:             32K
L1i cache:             32K
L2 cache:              256K
L3 cache:              35840K
NUMA node0 CPU(s):     0-13,28-41
NUMA node1 CPU(s):     14-27,42-55
Flags:                 fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch epb cat_l3 cdp_l3 intel_ppin intel_pt tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm cqm rdt_a rdseed adx smap xsaveopt cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local dtherm ida arat pln pts
```

## SIMD FormBody Parsing and Dubbo Generation

server supporting avx2

```
total serial transform time: 380 ms

total sse4 transform time: 240 ms

total avx2 transform time: 90 ms
```

## Base64 Operations, msg len 80

server supporting avx2

### AVX2

base64, base64, base36, small-padding-base36

```
11:01:19 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
11:01:34 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 14.722702s
11:01:34 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 570.026750 MB/s
11:01:34 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
11:01:49 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 14.721010s
11:01:49 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 570.092260 MB/s
11:01:49 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
11:02:04 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 14.753758s
11:02:04 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 568.826853 MB/s
11:02:04 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
11:02:20 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 15.614043s
11:02:20 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 232.096347 MB/s
```

### Chromium

```
11:03:24 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
11:03:45 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 20.643003s
11:03:45 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 406.546169 MB/s
11:03:45 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
11:04:06 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 20.614565s
11:04:06 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 407.107015 MB/s
11:04:06 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
11:04:27 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 20.679508s
11:04:27 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 405.828509 MB/s
11:04:27 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
11:04:44 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 17.294928s
11:04:44 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 209.539033 MB/s
```

### Naive-Lookup-Table

```
10:58:25 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
10:58:46 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 20.664047s
10:58:46 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 406.132152 MB/s
10:58:46 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
10:59:07 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 20.773008s
10:59:07 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 404.001859 MB/s
10:59:07 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
10:59:28 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 20.758757s
10:59:28 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 404.279222 MB/s
10:59:28 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
10:59:46 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 17.479488s
10:59:46 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 207.326572 MB/s
```

### Naive-Translation-Comp (Branching)

```
12:34:57 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
12:35:53 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 55.522484s
12:35:53 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 151.151991 MB/s
12:35:53 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
12:36:49 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 55.496086s
12:36:49 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 151.223889 MB/s
12:36:49 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
12:37:32 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 42.851158s
12:37:32 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 195.848475 MB/s
12:37:32 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
12:38:05 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 33.424431s
12:38:05 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 108.422561 MB/s
```

## Base64 Operations, msg len 50

### AVX2

base64, base64, base36, small-padding-base36

```
21:47:32 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
21:47:47 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 14.136199s
21:47:47 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 391.287010 MB/s
21:47:47 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
21:48:01 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 14.381686s
21:48:01 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 384.607963 MB/s
21:48:02 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
21:48:16 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 14.274146s
21:48:16 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 387.505565 MB/s
21:48:16 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
21:48:32 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 15.685737s
21:48:32 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 231.035525 MB/s
```

### Chromium

```
11:05:27 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
11:05:44 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 16.674145s
11:05:44 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 331.729820 MB/s
11:05:44 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
11:06:01 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 16.584595s
11:06:01 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 333.521025 MB/s
11:06:01 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
11:06:18 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 16.483555s
11:06:18 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 335.565422 MB/s
11:06:18 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
11:06:36 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 17.454824s
11:06:36 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 207.619527 MB/s
```

### Naive-LookUp-Table

```
10:56:12 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
10:56:29 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 16.974983s
10:56:29 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 325.850751 MB/s
10:56:29 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
10:56:47 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 17.453079s
10:56:47 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 316.924651 MB/s
10:56:47 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
10:57:04 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 17.070135s
10:57:04 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 324.034403 MB/s
10:57:04 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
10:57:22 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 18.099405s
10:57:22 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 200.225496 MB/s
```

### Naive-Translation-Comp (Branching)

```
12:30:52 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
12:31:39 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 47.092278s
12:31:39 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 117.456860 MB/s
12:31:40 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
12:32:27 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 47.286400s
12:32:27 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 116.974670 MB/s
12:32:27 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
12:33:03 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 35.618355s
12:33:03 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 155.293838 MB/s
12:33:03 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
12:33:37 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 33.415916s
12:33:37 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 108.450187 MB/s

```