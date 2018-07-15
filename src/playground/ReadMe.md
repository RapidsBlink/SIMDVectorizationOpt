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
21:35:46 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
21:36:01 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 14.792393s
21:36:01 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 515.764736 MB/s
21:36:01 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
21:36:16 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 14.808870s
21:36:16 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 515.190853 MB/s
21:36:16 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
21:36:31 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 14.768680s
21:36:31 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 516.592866 MB/s
21:36:31 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
21:36:47 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 15.659643s
21:36:47 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 182.700392 MB/s

```
### Normal

```
21:37:29 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
21:37:51 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 21.757704s
21:37:51 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 350.652560 MB/s
21:37:51 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
21:38:13 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 21.562340s
21:38:13 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 353.829622 MB/s
21:38:13 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
21:38:35 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 21.378904s
21:38:35 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 356.865553 MB/s
21:38:35 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
21:38:53 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 18.007008s
21:38:53 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 158.883864 MB/s

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

### Normal

```
21:44:04 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:58: finish init
21:44:20 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:87: elapsed time: 16.709606s
21:44:20 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:90: TPS: 331.025817 MB/s
21:44:21 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:115: finish init
21:44:37 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:144: elapsed time: 16.660173s
21:44:37 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:147: TPS: 332.008011 MB/s
21:44:38 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:172: finish init
21:44:54 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:201: elapsed time: 16.539164s
21:44:54 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:204: TPS: 334.437168 MB/s
21:44:54 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:229: finish init
21:45:13 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:258: elapsed time: 18.106968s
21:45:13 INFO  /homes/ywangby/workspace/yche/GitRepos/SIMDVectorizationOpt/src/playground/test_serialization.cpp:261: TPS: 200.141869 MB/s

```
